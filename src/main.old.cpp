
#include <pins.h>
#include <RadioLib.h>

using namespace pins;

void spiWrite(uint8_t data);
int FEM(int tx_invRx, int ref);
int8_t setTxgain(int8_t P);
float setRfFrequency(float f);
uint8_t ReadBuffer(uint8_t offset);
uint8_t WriteBuffer(uint8_t offset, uint8_t data);

uint8_t circ_mode = 0; // circuit mode status
uint8_t cmd_mode = 0; // comand mode status

[[noreturn]] int main() {
    Serial.begin(9600);
    delay(200);
    //Serial.println(digitalRead(BUSY));

    analogWriteResolution(10);
    pinMode(miso, INPUT);
    pinMode(mosi, OUTPUT);
    pinMode(sck, OUTPUT);
    //pinMode(SDA, OUTPUT);
    //pinMode(SCL, OUTPUT);

    pinMode(LED, OUTPUT);
    pinMode(DAC0, OUTPUT);
    pinMode(RST, OUTPUT);
    pinMode(BUSY, INPUT);
    pinMode(CSD, OUTPUT);
    pinMode(CTX, OUTPUT);
    //pinMode(DIO2, );
    //pinMode(DIO1, );
    pinMode(CRX, OUTPUT);
    pinMode(CS, OUTPUT);

    FEM(2, 0); // set PA to sleep
    digitalWrite(CS, 1);
    digitalWrite(sck, 0);

    digitalWrite(RST, 0); // reset transceiver
    delay(5);
    digitalWrite(RST, 1);
    delay(5);
    while(digitalRead(BUSY) == 1){ // busy = 0 means tranceiver is ready for new command
        Serial.println(digitalRead(BUSY));
    }


    /*
    // entering FS mode:
    unsigned long f = 2450000000; // Hz
    int8_t P = 0; // dmb
    FEM(1, 100); // enabling front end module for tx
    setTxgain(P);
    //settx param
    digitalWrite(CS, 0);
    spiWrite(0x8E);
    spiWrite(0x12); // power = 0dbm
    spiWrite(0xE0); // ramp time = 20uS
    //SetFS(f);
    digitalWrite(CS, 0);
    spiWrite(0x86);
    spiWrite(0xB8);
    spiWrite(0x9D);
    spiWrite(0x89);
    digitalWrite(CS, 1);
    delayMicroseconds(1);
    digitalWrite(CS, 0);
    spiWrite(0xD1);
    digitalWrite(CS, 1);
    */

    while (true) {
      while(digitalRead(BUSY) != 0){
        delay(1);
        Serial.println("BUSY pin = 1");
      }


      FEM(1, 500); //set FEM into transmitt mode // the voltage value currently doesnt do anything. The dac is outputing its max voltage, about 2.3v
      setTxgain(-10); //set tranceiver output power at 0 dbm
      //setRfFrequency(2.45);

      WriteBuffer(0x00, 0x13);
      Serial.print("0x"); Serial.println(ReadBuffer(0x00), HEX);


      digitalWrite(CS, 0);
      //spiWrite(0x80); spiWrite(0x01); // turn on 52Mhz osc in standby
      spiWrite(0xD1); // setTxContinuousWave
      //spiWrite(0xC1); // setFs
      digitalWrite(CS, 1);
      delay(1); // waiting for BUSY to go low

      Serial.print("setting frequency to "); Serial.print(setRfFrequency(2.5)); Serial.println(); // the frequency setting function doesn't work right now

      Serial.print(circ_mode); Serial.print(" - "); Serial.print(cmd_mode); Serial.print(" - "); Serial.println(digitalRead(BUSY));
      //getStatus(); // prints the two status number. the correlating table is on datasheet page number 73

      // SetTx(periodBase, periodBaseCount) // sends the packet in the data buffer
      // SetTxParam(power, rampTime) //
      // SetTxContinuousWave() // emit CW
      // SetTxContinuousPreamble() // modulate an alternating series of 0 and 1
      // SetRx(periodBase, periodBaseCount) // transition to receive mode
      // SetRFFrequency() // sets PLL frequency. default should be 2.4 GHz
      // SetFS() // turns PLL on
      // SetModulationParam() // sets bandwidth and bit rate
      // GetRxBufferStatus() // tels you the location of the received packet
      // SetPacketParam() // includes payload lenght ( how many byte to send from the data buffer)
      // SetBufferBaseAddress() // sets both RX and TX addresses. the default for both is 0x00
      // WriteBuffer()
      // ReadBUffer()

      // BUSY = 0 <= means txrx is ready for new command




      /*
      setTx
      setTxgain(0); //set gain at 0 dbm, ramp at 20uS(not adjustible in this code)
      FEM(1, 500); // front end module tx_invRx = 1 for sending, 0 for receiving, 2 for sleep. ref = voltage*1e3
      delay(1);
      SetFS(2420000000.0);
      //Serial.println(digitalRead(BUSY));
      */

      /*
      Serial.println("setting buffer pointers");
      SetBufferBaseAddress(0x10, 0x10);
      Serial.println("writing to buffer");
      WriteBuffer(0x02, 0xFF);
      Serial.println("reading from buffer");
      Serial.println(ReadBuffer(0x00), BIN);
      //Serial.println();
      */

      /*
      Serial.println("filling up the buffer");
      for(uint8_t i=0;i<255;i++){
        WriteBuffer(i, 0x1F);
      }
      WriteBuffer(0xFF, 0x00);
      WriteBuffer(0x00, 0x11);
      WriteBuffer(0x01, 0x12);



      Serial.println("reading all addresses in the buffer:");
      digitalWrite(CS, 0);
      spiWrite(0x1B); // ReadBuffer opcode
      spiWrite(0x00); // offset = 0, we want to go through all the adresses
      spiWrite(0x00); // we have to give 8 clk sycles before the data is shifted out
      uint8_t data;
      for(int i=0;i<16;i++){ //16 vertical collums
        for(int ii=0;ii<16;ii++){ // 16 horizontal lines // 16**2 = 256 <= all of the addresses
          for(int iii=0;iii<8;iii++){
            digitalWrite(sck, 1);
            delayMicroseconds(1);
            bitWrite(data, 7-iii, digitalRead(miso)); // MSB comes in first
            //Serial.print(digitalRead(miso));
            digitalWrite(sck, 0);
            delayMicroseconds(1);
          }
          Serial.print("0x");
          Serial.print(data, HEX);
          Serial.print(" ");
        }
        Serial.println();
      }
      digitalWrite(CS, 1);

      Serial.println();
      Serial.println();
     */


      digitalWrite(LED, 1);
      delay(500);
      digitalWrite(LED, 0);
      delay(500);



      //Serial.println(digitalRead(BUSY));
    }

    return 0;
}


float setRfFrequency(float f){ // f in GHz. the value will be rounded and the actual frequency set returned
  float f_par_float = 5041230.769230769 * f;
  uint32_t f_par = (uint32_t)f_par_float; // trunctuating the value
  float f_actual = f_par*198.3642578125; // in HZ // not sure if this is acurate, as there are still some rounding

  uint8_t f_lsd;
  uint8_t f_mid;
  uint8_t f_msd;

  for(int i=0;i<8;i++){ // splitting the f_par into 3 bytes
    bitWrite(f_lsd, i, bitRead(f_par, i));
    bitWrite(f_mid, i, bitRead(f_par, i+8));
    bitWrite(f_msd, i, bitRead(f_par, i+16));
  }


  digitalWrite(CS, 0);
  delayMicroseconds(1);
  spiWrite(0x86);
  spiWrite(f_msd);
  spiWrite(f_mid);
  spiWrite(f_lsd);
  delayMicroseconds(1);
  digitalWrite(CS, 0);

  return(f_actual);
}

void getStatus(){
  uint8_t data = 0xC0;
  uint8_t stat1 = 0x00; // bits 7 downto 5
  uint8_t stat2 = 0x00; // bits 4 downto 2
  digitalWrite(CS, 0);
  for(int i=0;i<3;i++){
    digitalWrite(mosi, bitRead(data, 7-i)); // MSB writen first
    delayMicroseconds(1);
    digitalWrite(sck, 1);
    delayMicroseconds(1);
    bitWrite(stat1, 2-i, digitalRead(miso));
    //Serial.print(digitalRead(miso));
    digitalWrite(sck, 0);
    delayMicroseconds(1);
  }
  //Serial.print(" - ");
  for(int i=3;i<6;i++){
    digitalWrite(mosi, bitRead(data, 7-i));
    delayMicroseconds(1);
    digitalWrite(sck, 1);
    delayMicroseconds(1);
    bitWrite(stat2, 2-i, digitalRead(miso));
    //Serial.print(digitalRead(miso));
    digitalWrite(sck, 0);
    delayMicroseconds(1);
  }
  for(int i=6;i<8;i++){
    digitalWrite(mosi, bitRead(data, 7-i));
    delayMicroseconds(1);
    digitalWrite(sck, 1);
    delayMicroseconds(1);
    digitalWrite(sck, 0);
    delayMicroseconds(1);
  }
  digitalWrite(CS, 1);
  while(digitalRead(BUSY) == 1){
    delayMicroseconds(1);
  }
  //Serial.println();
  Serial.print(stat1); Serial.print(" - "); Serial.println(stat2);
}

void spiWrite(uint8_t data){
  uint8_t status = 0;
  //Serial.println(data, BIN);
  for(int i=0;i<8;i++){
    digitalWrite(mosi, bitRead(data, 7-i)); // MSB writen first
    //Serial.print(bitRead(data, 7-i), BIN);
    delayMicroseconds(1);
    digitalWrite(sck, 1); // data read on rising edge
    bitWrite(status, 7-i, digitalRead(miso));
    delayMicroseconds(1);
    digitalWrite(sck, 0);
  }
  delayMicroseconds(1);
  //Serial.println(" ");

  bitWrite(circ_mode, 0, bitRead(status, 5));
  bitWrite(circ_mode, 1, bitRead(status, 6));
  bitWrite(circ_mode, 2, bitRead(status, 7));
  bitWrite(cmd_mode, 0, bitRead(status, 2));
  bitWrite(cmd_mode, 1, bitRead(status, 3));
  bitWrite(cmd_mode, 2, bitRead(status, 4));

  //while(digitalRead(BUSY) != 0){delayMicroseconds(1);}
}


uint8_t SetBufferBaseAddress(uint8_t txAddr, uint8_t rxAddr){
  digitalWrite(CS, 0);
  delayMicroseconds(1);
  spiWrite(0x8F);
  spiWrite(txAddr);
  spiWrite(rxAddr);
  delayMicroseconds(1);
  digitalWrite(CS, 1);
}
uint8_t WriteBuffer(uint8_t offset, uint8_t data){ // writes just one byte at a given offset from the tx pointer
  digitalWrite(CS, 0);
  spiWrite(0x1A);
  spiWrite(offset);
  spiWrite(data);
  digitalWrite(CS, 1);
  while(digitalRead(BUSY) == 1){
    delayMicroseconds(1);
  }
}



uint8_t ReadBuffer(uint8_t offset){
  uint8_t data;
  digitalWrite(CS, 0);
  delayMicroseconds(1);
  spiWrite(0x1B);
  spiWrite(offset);
  spiWrite(0x00); // it takes 8 empty clk cycles before the data is shifted out
  //Serial.print("inside the read buffer function:  ");
  digitalWrite(sck, 1);
  for(int i=0;i<8;i++){
    digitalWrite(sck, 1);
    delayMicroseconds(1);
    bitWrite(data, 7-i, digitalRead(miso));  // MSB comes in first
    //Serial.print(digitalRead(miso));
    digitalWrite(sck, 0);
    delayMicroseconds(1);
  }
  digitalWrite(CS, 1);
  //Serial.println("   goint out from read buffer function");
  while(digitalRead(BUSY) == 1){
    delayMicroseconds(1);
  }
  return(data);
}

int FEM(int tx_invRx, int ref){ // front end module tx_invRx = 1 for sending, 0 for receiving, 2 for sleep. ref = voltage*1e3
  if(tx_invRx == 0){ //rx mode
    analogWrite(DAC0, 0);
    delayMicroseconds(500); // not an optimised value
    digitalWrite(CSD, 1);
    digitalWrite(CTX, 0);
    digitalWrite(CRX, 1);
  }
  else if(tx_invRx == 1){ // transmit
    if(ref > 2850){ref = 2850;} // we want dac values from 0 to 1.425 as we have a gain of two externaly
    float U = ref;
    U = U*0.156; // values found experimentaly as dac range is not specified. this will give aproximate (conservative) values. (it will not exeed 2.85v)
    int bitVal = int(U);
    //Serial.print(ref); Serial.print(" - "); Serial.println(bitVal);
    //ref = ref * 155; // 1023/3.3 *1/2
    analogWrite(DAC0, 2000); // measuring 2.3v buffered by an op amp (as in schematic) without any gain
    digitalWrite(CSD, 1);
    digitalWrite(CTX, 1);
    digitalWrite(CRX, 0);
  }
  else{ // sleep
    analogWrite(DAC0, 0);
    delayMicroseconds(500); // not an optimised value
    digitalWrite(CSD, 0);
    digitalWrite(CTX, 0);
    digitalWrite(CRX, 0);
  }
}

/*
void SetFS(unsigned long f){ // syntesyser mode
  uint32_t f_int = trunc(f*0.005041230769230769); //52M/2**18 // computing the value we need to send the tranceiver
  Serial.println(f_int, BIN);
  digitalWrite(CS, 0);
  spiWrite(0x86); // opcode for frequency setting
  byte* pointer = (byte*)&f_int;
  for(int i=0;i<3;i++){
    spiWrite(pointer[2-i]); // write the 3 bytes containing which frequency we want
    Serial.print(pointer[2-i], BIN); Serial.print(" ");
    //f_int >> 8;
  }
  Serial.println();
  digitalWrite(CS, 1); // not sure if this pulse in CS is neccesary
  delayMicroseconds(1); // not optimised
  digitalWrite(CS, 0);
  spiWrite(0xC1); // setFs command. set the pll to the value we just put in to some register
  Serial.println();
  Serial.println();

  digitalWrite(CS, 1);
}
*/

int8_t setTxgain(int8_t P){ // P = power out
  if(P<-18){P=-18;}
  if(P>6){P=6;}
  uint8_t opcode = 0x8E;
  int p_int = P + 18;
  uint8_t power = p_int;
  uint8_t rampTime = 0xE0; // for 20 uS ramp (adjustible form 2uS to 20 uS)

  digitalWrite(CS, 0);
  spiWrite(opcode);
  spiWrite(power);
  spiWrite(rampTime);
  digitalWrite(CS, 1);
}
/*
busy pin = low <= tranceiver is ready for new comand



to send:

SetTx(periodBase, periodBaseCount){} tx sends the packet stored in the data buffer
SetTxParam(power, rampTime){} P_rf = -18 + power; ramp time is between 2uS and 20uS
SetTxContinuosWave(){}

SetRfFrequency(rfFrequency){} rfFrequency is 24bit, F_rf=(F_osc/2**18)*rfFrequency
SetFS(){} <= syntesyser mode


*/

