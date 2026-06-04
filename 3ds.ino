#include "stdio.h"
using namespace std;
#include "string.h"

const int CLK = 2;
const int RCS = 3;
const int RST = 4;
const int ECS = 5;
const int D0 = 6;
const int D1 = 7;
const int D2 = 8;
const int D3 = 9;
const int D4 = 10;  // HOLD
const int D5 = 11;  // WP
const int D6 = 12;  // SO
const int D7 = 13;  // SI

void setup() {
  pinMode(CLK, OUTPUT);
  pinMode(RCS, OUTPUT);
  digitalWrite(RCS, HIGH); 
  pinMode(RST, OUTPUT);
  pinMode(ECS, OUTPUT);
  Serial.begin(115200);
  Serial.println("Here is the data: ");


  digitalWrite(CLK, HIGH);
  digitalWrite(ECS, HIGH); // 04 06 07 0F 1F
  // setByte(0xFF);
  digitalWrite(RST, HIGH);
  digitalWrite(RCS, HIGH);

  delay(2000);

  digitalWrite(RCS, LOW); 

  setOut();
  sendByte(0x9F);
  sendByte(0x00);
  sendByte(0x00);
  sendByte(0x00);
  sendByte(0x00);
  sendByte(0x00);
  sendByte(0x00);
  sendByte(0x00);
  digitalWrite(CLK, LOW);
  digitalWrite(RCS, HIGH); 
  delay(10);

  setInUp();
  Serial.println("First line: ");
  digitalWrite(RCS, LOW); 
  for(int i = 0;i<(0x2000)/8;i++){
  performRead(8);//3B18]
  delayMicroseconds(10);
  }
  digitalWrite(RCS, HIGH); 
  delay(10);


  setOut();
  digitalWrite(RCS, LOW); 
  sendByte(0x71);
  sendByte(0xC9);
  sendByte(0x3F);
  sendByte(0xE9);
  sendByte(0xBB);
  sendByte(0x0A);
  sendByte(0x3B);
  sendByte(0x18);
  digitalWrite(RCS, HIGH); 
  delay(10);

  digitalWrite(RCS, LOW); 
  sendByte(0x90);
  sendByte(0x00);
  sendByte(0x00);
  sendByte(0x00);
  sendByte(0x00);
  sendByte(0x00);
  sendByte(0x00);
  sendByte(0x00);
    digitalWrite(RCS, HIGH); 
  delay(10);

    digitalWrite(RCS, LOW); 

  // setByte(0xC2);
  digitalWrite(CLK, LOW);

  setIn();
  Serial.println();
  performRead(0x200);

  

}

// void setup() {
//   pinMode(CLK, OUTPUT);
//   pinMode(RCS, OUTPUT);
//   digitalWrite(RCS, HIGH);
//   pinMode(RST, OUTPUT);
//   digitalWrite(RST, LOW);
//   pinMode(ECS, OUTPUT);
//   Serial.begin(115200);


//   digitalWrite(CLK, HIGH);
//   digitalWrite(ECS, HIGH);
//   // setByte(0xFF);
//   digitalWrite(RCS, LOW);  // 04 06 07 0F 1F
//   digitalWrite(RST, HIGH);

//   setOut();
//   sendByte(0x9F);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);

//   setInUp();
//   // performRead(0x2000);//3B18
//   performRead(0x2000);

//   setOut();
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);

//   setIn();
//   Serial.println();
//   performRead(0x200);

//   sendByte(0x90);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
//   sendByte(0x00);
  
//   setByte(0xC2);
//   digitalWrite(CLK, LOW);

//   setIn();
//   Serial.println();
//   performRead(0x4);

  

// }

// void setup(){
//   setOut();
//   pinMode(CLK, OUTPUT);
//   pinMode(RCS, OUTPUT);
//   pinMode(RST, OUTPUT);
//   pinMode(ECS, OUTPUT);

//   digitalWrite(CLK, HIGH);
//   delayMicroseconds(1);
//   sendByte(0x9f);
//   // digitalWrite(D5, HIGH);

// }

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
  digitalWrite(CLK, HIGH);
  digitalWrite(D0, bitRead(inp, 0));
  digitalWrite(D1, bitRead(inp, 1));
  digitalWrite(D2, bitRead(inp, 2));
  digitalWrite(D3, bitRead(inp, 3));
  digitalWrite(D4, bitRead(inp, 4));
  digitalWrite(D5, bitRead(inp, 5));
  digitalWrite(D6, bitRead(inp, 6));
  digitalWrite(D7, bitRead(inp, 7));
  digitalWrite(CLK, HIGH);
  delayMicroseconds(1);
  digitalWrite(CLK, LOW);
  delayMicroseconds(1);
  digitalWrite(CLK, HIGH);
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

void performRead(int length){
  byte val = 0;
  for(int i = 0;i<length;i++){
    digitalWrite(CLK, HIGH);
    delayMicroseconds(1);
    bitWrite(val, 0, digitalRead(D0));
    bitWrite(val, 1, digitalRead(D1));
    bitWrite(val, 2, digitalRead(D2));
    bitWrite(val, 3, digitalRead(D3));
    bitWrite(val, 4, digitalRead(D4));
    bitWrite(val, 5, digitalRead(D5));
    bitWrite(val, 6, digitalRead(D6));
    bitWrite(val, 7, digitalRead(D7));
    digitalWrite(CLK, LOW); 
    Serial.print((char)val);
    Serial.print(" ");
    delayMicroseconds(1);

  }
}

void loop() {
  
}














