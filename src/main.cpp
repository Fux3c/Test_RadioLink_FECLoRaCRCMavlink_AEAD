
#include <pins.h>
#include <RadioLib.h>

using namespace pins;

uint8_t circ_mode = 0; // circuit mode status
uint8_t cmd_mode = 0; // command mode status

enum TX_RX_MODE {
    RX,
    TX,
    SLEEP
};

int FEM(TX_RX_MODE tx_invRx, int ref);

[[noreturn]] int main() {

    analogWriteResolution(10); // => 0-1023

    pinMode(LED, OUTPUT);
    pinMode(DAC0, OUTPUT);

    pinMode(CSD, OUTPUT);
    pinMode(CTX, OUTPUT);
    pinMode(CRX, OUTPUT);

    FEM(SLEEP, 0);

    SX1280 radio = new Module(CS, DIO1, RST, BUSY);

    FEM(TX, 500);
    radio.begin(2400.0);  // 2.4 GHz
    radio.setOutputPower(6);  // 6 dBm

    while (true) {

        radio.transmit("Hello World");

        digitalWrite(LED, 1);
        delay(500);
        digitalWrite(LED, 0);
        delay(500);
    }
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
            analogWrite(DAC0, 2000); // measuring 2.3v buffered by an op amp (as in schematic) without any gain
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
