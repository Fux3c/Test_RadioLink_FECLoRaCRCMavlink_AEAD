//    _   _ ____  _   _   _   _            _                
//   | | | / ___|| \ | | | | | | ___  _ __(_)_______  _ __  
//   | | | \___ \|  \| | | |_| |/ _ \| '__| |_  / _ \| '_ \ 
//   | |_| |___) | |\  | |  _  | (_) | |  | |/ / (_) | | | |
//    \___/|____/|_| \_| |_| |_|\___/|_|  |_/___\___/|_| |_|
//                                                          
//   Not Rocket Science 2024
//   SRAD Power Distribution Unit - Software V0.1

#include <SPI.h>
#include <SD.h>
#include <Wire.h>

#define debug_mode false

// --- Pin Definitions ---
// I2C
#define I2C_SDA 18
#define I2C_SCL 19

// SPI
#define SPI_SS 10
#define SPI_MOSI 11
#define SPI_MISO 12
#define SPI_SCK 13

// UART
#define UART_TX 0
#define UART_RX 1

// DIRECT ADC INPUT
#define BAT_CS A7
#define BAT_VS A6
#define BAT_NTC A3
#define SERVO1_CS A1
#define AUX_CS A2

// OUTPUT SHIFT REGISTER 1
#define SRG1_SHCP 7
#define SRG1_STCP 6
#define SRG1_SER 5
#define SRG1_OE 4 

// ADC PARAMETERS
#define ADC_ADDR 0b1001000
const char ADC_CONF_MSB = 0b00000000;
const char ADC_CONF_LSB = 0b10000011;

// POWER CIRCUIT PARAMETERS 
#define PWR_CIRCUITS 6 // Number of Circuits
#define ADC_CHANNELS 8 // Number of Channels on the ADC
#define PWR_OCP_TIME 100 // Time(ms) between Over Current Protection Samples
#define PWR_OCP_LIMIT 10 // Number of Over Current Violations permitted before circuit shutdown.
const int PWR_OCP_THRESHOLD[PWR_CIRCUITS] = {1000, 512, 512, 512, 512, 512};

void reset() {
  // TODO
}

void adcRead(int data[ADC_CHANNELS]){ // Reads from built-in ADC and external ADC 
  // TODO
}

void registerWrite(char data){ // Shift register functionality

  const unsigned int regSize = 8; // bits
  
  for (int i = 0; i < regSize; i++){
    digitalWrite(SRG1_SER, bitRead(data, i));
    digitalWrite(SRG1_SHCP, HIGH);
    digitalWrite(SRG1_SHCP, LOW);
  }
  
  digitalWrite(SRG1_STCP, HIGH);
  digitalWrite(SRG1_STCP, LOW);
}

void sendData(){ //Function for sending data over serial to flight computer
  // TODO
}

void updateOCP(int adc_data[ADC_CHANNELS]){ // Over Current Protection
  static unsigned int OC_CONDITIONS[PWR_CIRCUITS] = {0}; // Over-Current Counter for 6 circuits.
  static unsigned long lastClock = 0;

  if (millis() - lastClock > PWR_OCP_TIME){
    for (int i = 0; i < PWR_CIRCUITS; i++){
      if (adc_data[i] > PWR_OCP_THRESHOLD[i] && OC_CONDITIONS[i] < 10){
        OC_CONDITIONS[i] += 1;
        if(OC_CONDITIONS[i] >= PWR_OCP_LIMIT){
          
          #if debug_mode //OCP warning on UART
            Serial.print("OCP: ");
            Serial.println(i);
          #endif

          // TODO: Shutdown the Circuits
        }
      } else if (OC_CONDITIONS[i] > 1){
        OC_CONDITIONS[i] -= 1;
      }
    }
    lastClock = millis();
  }
}

void setup() {

  // Setup for Shift Register 1 (set OE to High to wait for setup)
  digitalWrite(SRG1_OE, HIGH);
  registerWrite(0x00);
  digitalWrite(SRG1_OE, LOW);

  // Pin Mode Definitions
  pinMode(SRG1_SHCP,  OUTPUT);
  pinMode(SRG1_STCP,  OUTPUT);
  pinMode(SRG1_SER,   OUTPUT);
  pinMode(SRG1_OE,    OUTPUT);
  pinMode(UART_RX,    INPUT );
  pinMode(UART_TX,    OUTPUT);
  pinMode(BAT_CS,     INPUT );
  pinMode(BAT_VS,     INPUT );
  pinMode(BAT_NTC,    INPUT );
  pinMode(SERVO1_CS,  INPUT );
  pinMode(AUX_CS,     INPUT );

  // UART Initialisation 
  Serial.begin(9600);
  Serial.println();
  Serial.println("PDU BOOTING...");

  // I2C Initialisation
  Wire.begin();
  Wire.beginTransmission(ADC_ADDR);
  Wire.write(0x01); // Write to configuration register
  Wire.write(ADC_CONF_MSB);
  Wire.write(ADC_CONF_LSB);
  Wire.endTransmission();

}

void loop() {
  static unsigned long deltaTime = 0;

  deltaTime = millis();
  
  // ADC Readings
  static int ADC_DATA[ADC_CHANNELS] = {0};

  // Register for Power Circuit States (On=1/Off=0)
  static char enable_register = 0x00;

  // Serial instructions handler
  if(Serial.available()){
    int data = Serial.read();
    switch(data){
      // Enable and Disable Power Circuits
      case 0x00: //CH0 Disable
        bitWrite(enable_register, 2, 0);
        break;
      case 0x01: //CH0 Enable
        bitWrite(enable_register, 2, 1);
        break;
      case 0x10: //CH1 Disable
        bitWrite(enable_register, 3, 0);
        break;
      case 0x11: //CH1 Enable
        bitWrite(enable_register, 3, 1);
        break;
      case 0x20: //CH2 Disable
        bitWrite(enable_register, 4, 0);
        break;
      case 0x21: //CH2 Enable
        bitWrite(enable_register, 4, 1);
        break;
      case 0x30: //CH3 Disable
        bitWrite(enable_register, 5, 0);
        break;
      case 0x31: //CH3 Enable
        bitWrite(enable_register, 5, 1);
        break;
      case 0x40: //CH4 Disable
        bitWrite(enable_register, 6, 0);
        break;
      case 0x41: //CH4 Enable
        bitWrite(enable_register, 6, 1);
        break;
      case 0x50: //CH5 Disable
        bitWrite(enable_register, 7, 0);
        break;
      case 0x51: //CH5 Enable
        bitWrite(enable_register, 7, 1);
        break;
      
      // All Circuits Enable/Disable
      case 0xF0:
        enable_register = 0x00;
        break;
      case 0xF1:
        enable_register = 0xFF;
        break;

      // FC Requests
      case 0xB0: // Send PDU Telemetry
        sendData();
        break;
    }
    registerWrite(enable_register);
    updateOCP(ADC_DATA);
  }
 
  deltaTime = millis() - deltaTime;
  
  #if debug_mode
    Serial.print("dT: ");
    Serial.println(deltaTime);
  #endif
}



