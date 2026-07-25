#ifndef SERIALREADER_H
#define SERIALREADER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>

class SerialReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isOpen READ isOpen NOTIFY isOpenChanged)

public:
    explicit SerialReader(QObject *parent = nullptr);
    ~SerialReader();

    bool autoReconnectEnabled() const;
    Q_INVOKABLE void disconnectPort();

    Q_INVOKABLE bool openPort(const QString &portName, qint32 baudRate = 115200);
    Q_INVOKABLE void closePort();
    Q_INVOKABLE bool isOpen() const;

    Q_INVOKABLE static QStringList availablePorts();
    Q_INVOKABLE QString findHorizonPort();

public slots:
    void setAutoReconnectEnabled(bool enabled);
    void autoReconnectEnabledChanged();

signals:
    void rawPacketReceived(const QByteArray &packet);
    void errorOccurred(const QString &error);
    void isOpenChanged();

private slots:
    void handleReadyRead();
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort *serialPort;
    QByteArray byteBuffer;

    bool m_autoReconnectEnabled = true;
};

#endif // SERIALREADER_H
