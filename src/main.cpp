
#include <pins.h>
#include <RadioLib.h>
#include <string>
#include <TMP1075.h>
#include <Wire.h>
#include "../lib/thermal_control.cpp"

using namespace pins;

uint8_t circ_mode = 0; // circuit mode status
uint8_t cmd_mode = 0; // command mode status

// !!!!!!!!!!!!!!!!!!!! DO NOT GO HIGHER THAN 465
constexpr int DAC_POWER = 465;

#define SENDER

enum TX_RX_MODE {
    RX,
    TX,
    SLEEP
};

int FEM(TX_RX_MODE tx_invRx, int ref);
void getTemperature(float &currentTemp);
void printMetrics(float currentTemp, bool thermalThrottling);

SX1280* radio = nullptr;
TMP1075::TMP1075 temp = TMP1075::TMP1075(Wire);

[[noreturn]] void setup() {
    Serial.begin(115200);
    delay(200);

    analogWriteResolution(10); // => 0-1023
    analogReadResolution(12);

    pinMode(LED, OUTPUT);
    pinMode(DAC0, OUTPUT);

    pinMode(CSD, OUTPUT);
    pinMode(CTX, OUTPUT);
    pinMode(CRX, OUTPUT);

    pinMode(A3, INPUT);

    FEM(SLEEP, 0);

    radio = new SX1280(new Module(CS, DIO1, RST, BUSY));

#ifdef SENDER
    FEM(TX, 500);
#else
    FEM(RX, 500);
#endif

    int state = radio->begin(
        // 2.4 GHz
        2400.0,
        812.5,
        9,
        7,
        18,
        6
    );
    // VELDIG VIKTIG! SKAL IKKE HØYERE ENN 6 dBm

    Serial.println("Setting up radio");
    if (state != RADIOLIB_ERR_NONE) {
        // Handle initialization error - maybe blink LED in a pattern
        while(true) {
            digitalWrite(LED, 1);
            delay(100);
            digitalWrite(LED, 0);
            delay(100);
        }
    }
    // Temperature initialization
    Serial.println("Setting up temp");
    Wire.begin();
    temp.begin();
}

void loop() {
    static float currentTemp = 0;
    static bool thermalThrottling = false;

    getTemperature(currentTemp);
    checkThermalStatus(currentTemp, thermalThrottling);

#ifdef SENDER

    static unsigned long count = 0;
    if (!thermalThrottling) {
        const std::string message =
            std::string("HRZN range test: ")
            + std::to_string(count) + " | "
            + std::to_string(DAC_POWER % 466);
        radio->transmit(message.c_str());
        Serial.println("Sendte: " + String(count));
        count++;
    }

#else


    String received;
    radio->receive(received);
    Serial.println("Mottok: " + received);

    //Get RSSI of received packet
    float rssi = radio->getRSSI();
    Serial.print("Packet RSSI: ");
    Serial.print(rssi);
    Serial.println(" dBm");

#endif

    printMetrics(currentTemp, thermalThrottling);

    digitalWrite(LED, 1);
    //delay(250);
    digitalWrite(LED, 0);
    //delay(250);
}

void getTemperature(float &currentTemp) {
    // Get temperature
    static unsigned long lastTime = millis();
    if (millis() - lastTime > 1000) {
        lastTime = millis();
        temp.setConversionTime(TMP1075::ConversionTime220ms);
        currentTemp = temp.getTemperatureCelsius();
    }
}


void printMetrics(const float currentTemp, const bool thermalThrottling) {
    Serial.println(millis());

    const int current_raw = analogRead(A3);
    //Serial.println(current_raw);
    Serial.print("Current:");
    const double current = current_raw * 0.00040283203;
    Serial.print(current);
    Serial.print(" A | ");

    Serial.print("Voltage:");
    const float voltage = current * 2;
    Serial.print(voltage);
    Serial.println(" V");

    Serial.print("Temperature: ");
    Serial.print(currentTemp);
    Serial.println(" C");

    Serial.print("Is thermally throttling: ");
    Serial.println(thermalThrottling ? "YES" : "NO");

}

/**
 * Front End Module
 * @param tx_invRx front end module tx_invRx = 1 for sending, 0 for receiving, 2 for sleep.
 * @param ref ref = voltage*1e3
 * @return
 */
int FEM(const TX_RX_MODE tx_invRx, int ref) {
    switch (tx_invRx) {
        case RX: // receive mode
            analogWrite(DAC0, 0);
            delayMicroseconds(500); // not an optimised value
            digitalWrite(CSD, 1);
            digitalWrite(CTX, 0);
            digitalWrite(CRX, 1);
            break;
        case TX: // transmit mode
            if(ref > 2850){ref = 2850;} // we want dac values from 0 to 1.425 as we have a gain of two externaly
            //float U = ref;
            //U = U*0.156f; // values found experimentaly as dac range is not specified. this will give aproximate (conservative) values. (it will not exeed 2.85v)
            //int bitVal = int(U);
            //Serial.print(ref); Serial.print(" - "); Serial.println(bitVal);
            //ref = ref * 155; // 1023/3.3 *1/2
            // !!!!!!!!!!!!!!!!!!!! DO NOT GO HIGHER THAN 465
            analogWrite(DAC0, DAC_POWER % 466); // measuring 2.3v buffered by an op amp (as in schematic) without any gain
            // 2000 % 1023 = 977 ??
            digitalWrite(CSD, 1);
            digitalWrite(CTX, 1);
            digitalWrite(CRX, 0);
            break;
        default: // sleep
            analogWrite(DAC0, 0);
            delayMicroseconds(500); // not an optimized value
            digitalWrite(CSD, 0);
            digitalWrite(CTX, 0);
            digitalWrite(CRX, 0);
            break;
    }
    return 0;
}
