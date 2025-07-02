
#include <pins.h>
#include <RadioLib.h>
#include <string>
#include <TMP1075.h>
#include <Wire.h>

using namespace pins;

uint8_t circ_mode = 0; // circuit mode status
uint8_t cmd_mode = 0; // command mode status

constexpr bool IS_SENDER = true;

enum TX_RX_MODE {
    RX,
    TX,
    SLEEP
};

int FEM(TX_RX_MODE tx_invRx, int ref);

SX1280* radio = nullptr;
//TwoWire wire = Wire;
//TMP1075::TMP1075 temp = TMP1075::TMP1075(wire);

void setup() {
    Serial.begin(9600);
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

    if (IS_SENDER) {
        FEM(TX, 500);
    } else {
        FEM(RX, 500);
    }

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
    //Serial.println("Setting up temp");
    //wire.begin();
    //temp.begin();
}


void loop() {
    while (Serial.available()) {
        Serial.read();
    }
    if (IS_SENDER) {
        unsigned long m = millis();
        radio->transmit(std::to_string(m).c_str());
        Serial.println("Sendte: " + String(m));
    } else {
        String recieved;
        radio->receive(recieved);
        Serial.println("Mottok: " + recieved);

        //Get RSSI of received packet
        float rssi = radio->getRSSI();
        Serial.print("Packet RSSI: ");
        Serial.print(rssi);
        Serial.println(" dBm");

        // Get temperature
        // static unsigned long lastTime = millis();
        // if (millis() - lastTime > 1000) {
        //     lastTime = millis();
        //     temp.setConversionTime(TMP1075::ConversionTime220ms);
        //     Serial.print("Temperature: ");
        //     Serial.print(temp.getTemperatureCelsius());
        //     Serial.println(" C");
        // }
    }

    int current_raw = analogRead(A3);
    Serial.println(current_raw);
    Serial.print("Current:");
    float current = current_raw * 0.00040283203;
    Serial.print(current);
    Serial.println(" A");

    Serial.print("Voltage:");
    float votage = current * 2;
    Serial.print(votage);
    Serial.println(" V");

    //digitalWrite(LED, 1);
    //delay(100);
    //digitalWrite(LED, 0);
    //delay(100);
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
            analogWrite(DAC0, 465); // measuring 2.3v buffered by an op amp (as in schematic) without any gain
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
