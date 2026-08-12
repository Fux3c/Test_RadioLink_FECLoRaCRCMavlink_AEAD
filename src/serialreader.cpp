#include "serialreader.h"
#include <QDebug>
#include <QTimer>
#include <QSettings>

// Arduino Nano 33 IoT: VID 0x2341, PID 0x8057
namespace {
constexpr quint16 ARDUINO_VID = 0x2341;
constexpr quint16 NANO_33_IOT_PID = 0x8057;
constexpr auto AUTO_RECONNECT_SETTINGS_KEY = "SerialReader/autoReconnectEnabled";
}

SerialReader::SerialReader(QObject *parent)
    : QObject(parent)
    , serialPort(new QSerialPort(this))
{
    QSettings settings;
    m_autoReconnectEnabled = settings.value(AUTO_RECONNECT_SETTINGS_KEY, true).toBool();

    connect(serialPort, &QSerialPort::readyRead,
            this, &SerialReader::handleReadyRead);
    connect(serialPort, &QSerialPort::errorOccurred,
            this, &SerialReader::handleError);

    // Poll for disconnection every 2 seconds
    QTimer* watchdog = new QTimer(this);
    connect(watchdog, &QTimer::timeout, this, [this]() {
        if (!serialPort->isOpen()) {
            if (!m_autoReconnectEnabled)
                return; // user chose to stay disconnected
            // Try to reconnect
            QString port = findHorizonPort();
            if (!port.isEmpty()) {
                qDebug() << "Watchdog reconnecting on" << port;
                openPort(port, 115200);
            }
        } else if (serialPort->error() == QSerialPort::ResourceError
                   || serialPort->error() == QSerialPort::DeviceNotFoundError) {
            qDebug() << "Watchdog detected fatal error, closing";
            closePort();
        }
    });
    watchdog->start(2000);
}

SerialReader::~SerialReader()
{
    closePort();
}

bool SerialReader::openPort(const QString &portName, qint32 baudRate)
{
    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    if (serialPort->open(QIODevice::ReadWrite)) {
        serialPort->setDataTerminalReady(false);
        qDebug() << "Serial port opened:" << portName << "at" << baudRate << "baud";
        setAutoReconnectEnabled(true); // re-arm on successful connect
        emit isOpenChanged();
        return true;
    } else {
        emit errorOccurred("Failed to open port: " + serialPort->errorString());
        return false;
    }
}

void SerialReader::closePort()
{
    if (serialPort->isOpen()) {
        serialPort->close();
        emit isOpenChanged();
        qDebug() << "Serial port closed";
    }
}

bool SerialReader::isOpen() const
{
    return serialPort->isOpen();
}

QStringList SerialReader::availablePorts()
{
    QStringList ports;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        ports << info.portName() + " (" + info.description() + ")";
    }
    return ports;
}

QString SerialReader::findHorizonPort()
{
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        if (info.hasVendorIdentifier() && info.hasProductIdentifier()
            && info.vendorIdentifier() == ARDUINO_VID
            && info.productIdentifier() == NANO_33_IOT_PID) {
            qDebug() << "Found Horizon module on" << info.portName()
            << "(" << info.description() << ")";
            return info.portName();
        }
    }
    return {};
}

bool SerialReader::autoReconnectEnabled() const
{
    return m_autoReconnectEnabled;
}

void SerialReader::setAutoReconnectEnabled(bool enabled)
{
    if (m_autoReconnectEnabled != enabled) {
        m_autoReconnectEnabled = enabled;
        QSettings settings;
        settings.setValue(AUTO_RECONNECT_SETTINGS_KEY, enabled);
        emit autoReconnectEnabledChanged();
    }
}

void SerialReader::disconnectPort()
{
    // Deliberate user action: stop the watchdog from fighting them
    setAutoReconnectEnabled(false);
    closePort();
}

void SerialReader::handleReadyRead()
{
    emit rawPacketReceived(serialPort->readAll());
}

void SerialReader::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError ||
        error == QSerialPort::DeviceNotFoundError) {
        qDebug() << "Fatal serial error, closing port:" << serialPort->errorString();
        closePort();
    } else if (error != QSerialPort::NoError && error != QSerialPort::TimeoutError) {
        emit errorOccurred(serialPort->errorString());
        qDebug() << "Serial error:" << serialPort->errorString();
    }
}
