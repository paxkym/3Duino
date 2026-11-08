#include "stdio.h"
using namespace std;
#include "string.h"

const int CLK = 2;
const int RCS = 3;
const int RST = 4;
const int ECS = 5;
const int D0 = 6;
const int D1 = A5;
const int D2 = 8;
const int D3 = 9;
const int D4 = 10;  // HOLD
const int D5 = 11;  // WP
const int D6 = 12;  // SO
const int D7 = 13;  // SI
const byte resetcomm[] = {0x9F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const byte identcomm[] = {0x71, 0xC9, 0x3F, 0xE9, 0xBB, 0x0A, 0x3B, 0x18};
const byte idonecomm[] = {0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const byte idtwocomm[] = {0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const byte switccomm[] = {0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const byte headrcomm[] = {0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void setup() {
  pinMode(CLK, OUTPUT);
  pinMode(RCS, OUTPUT);
  digitalWrite(RCS, HIGH);
  pinMode(RST, OUTPUT);
  digitalWrite(RST, LOW);
  pinMode(ECS, OUTPUT);
  Serial.begin(250000);


  digitalWrite(CLK, LOW);
  digitalWrite(ECS, HIGH);
  // setByte(0xFF);
  digitalWrite(RST, LOW);
  delay(10);
  digitalWrite(RST, HIGH);

   Serial.println("Reset: ");
  writeCycle8(resetcomm, 0x2000);
  writeCycle8(identcomm, 0x0000);
    Serial.println("\nID1: ");
  writeCycle8(idonecomm, 0x0004);
    Serial.println("\nID1: ");
  writeCycle8(idonecomm, 0x0004);
    Serial.println("\nID2: ");
  writeCycle8(idtwocomm, 0x0004);
  writeCycle8(switccomm, 0x0000);
    Serial.println("\nHeader: ");
  writeCycle16(headrcomm, 0x0200);

  const byte encrekeycomm[] = {0x32, 0xC8, 0x5E, 0x27, 0xDD, 0x9B, 0x2A, 0xF1, 0x18, 0x41, 0x6F, 0x53, 0xED, 0x2C, 0xE1, 0x56};
  const byte encid1comm[] = {0xF8, 0x1C, 0x18, 0x84, 0x1A, 0x3A, 0x75, 0xB2, 0x08, 0x8C, 0x5F, 0xEA, 0xBD, 0xA4, 0x83, 0x0E};

  writeCycle16(encrekeycomm, 0x0000);

    Serial.println("\nID1 Enc: ");
    setByte(0);
    byte buf[512];
    printBytes(buf, 100);

}

void writeCycle8(byte value[8], int length){
  setOut();
  digitalWrite(RCS, LOW);  // 04 06 07 0F 1F
  sendByte(value[0]);
  sendByte(value[1]);
  sendByte(value[2]);
  sendByte(value[3]);
  sendByte(value[4]);
  sendByte(value[5]);
  sendByte(value[6]);
  sendByte(value[7]);

  if(length != 0){
  setIn();
  // digitalWrite(CLK, HIGH);
    byte buf[512];
    printBytes(buf, length);
  }
  digitalWrite(RCS, HIGH);  // 04 06 07 0F 1F

}
void writeCycle16(byte value[16], int length){
  setOut();
  digitalWrite(RCS, LOW);  // 04 06 07 0F 1F
  sendByte(value[0]);
  sendByte(value[1]);
  sendByte(value[2]);
  sendByte(value[3]);
  sendByte(value[4]);
  sendByte(value[5]);
  sendByte(value[6]);
  sendByte(value[7]);
  sendByte(value[8]);
  sendByte(value[9]);
  sendByte(value[10]);
  sendByte(value[11]);
  sendByte(value[12]);
  sendByte(value[13]);
  sendByte(value[14]);
  sendByte(value[15]);

  if(length != 0){
  setIn();
    byte buf[512];
    printBytes(buf, length);
  // digitalWrite(CLK, HIGH);
  }
  digitalWrite(RCS, HIGH);  // 04 06 07 0F 1F

}

void setOut() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}

void setIn() {
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
}

void setInUp() {
  pinMode(D0, INPUT_PULLUP);
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(D4, INPUT_PULLUP);
  pinMode(D5, INPUT_PULLUP);
  pinMode(D6, INPUT_PULLUP);
  pinMode(D7, INPUT_PULLUP);
}


void sendByte(byte inp) {
    digitalWrite(CLK, LOW);

    digitalWrite(D0, (inp >> 0) & 1);
    digitalWrite(D1, (inp >> 1) & 1);
    digitalWrite(D2, (inp >> 2) & 1);
    digitalWrite(D3, (inp >> 3) & 1);
    digitalWrite(D4, (inp >> 4) & 1);
    digitalWrite(D5, (inp >> 5) & 1);
    digitalWrite(D6, (inp >> 6) & 1);
    digitalWrite(D7, (inp >> 7) & 1);

    delayMicroseconds(10);

    digitalWrite(CLK, HIGH);
    delayMicroseconds(10);
}

void setByte(byte inp) {
  digitalWrite(D0, bitRead(inp, 0));
  digitalWrite(D1, bitRead(inp, 1));
  digitalWrite(D2, bitRead(inp, 2));
  digitalWrite(D3, bitRead(inp, 3));
  digitalWrite(D4, bitRead(inp, 4));
  digitalWrite(D5, bitRead(inp, 5));
  digitalWrite(D6, bitRead(inp, 6));
  digitalWrite(D7, bitRead(inp, 7));
}

void readBytes(byte *buffer, uint16_t length) {
    setIn();

    for (uint16_t i = 0; i < length; i++) {
        digitalWrite(CLK, LOW);
        delayMicroseconds(10);

        byte val = 0;

        val |= digitalRead(D0) << 0;
        val |= digitalRead(D1) << 1;
        val |= digitalRead(D2) << 2;
        val |= digitalRead(D3) << 3;
        val |= digitalRead(D4) << 4;
        val |= digitalRead(D5) << 5;
        val |= digitalRead(D6) << 6;
        val |= digitalRead(D7) << 7;

        buffer[i] = val;

        digitalWrite(CLK, HIGH);
        delayMicroseconds(10);
    }
}

void printBytes(byte *buffer, int length){
  byte response[512];

  readBytes(response, 512);

  for (int i = 0; i < length; i++) {
      p(response[i]);
      Serial.print(" ");
  }
}

void loop() {
  
}








void p(byte X) {

   if (X < 16) {Serial.print("0");}

   Serial.print(X, HEX);

}





