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
const int D4 = 10;
const int D5 = 11;
const int D6 = 12;
const int D7 = A0;
const int CIPO = D6;
const int COPI = D7;
const bool clockEdge = false;

void setup() {
pinMode(CLK, OUTPUT);
pinMode(RCS, OUTPUT);
pinMode(RST, OUTPUT);
pinMode(ECS, OUTPUT);
Serial.begin(115200);

// If performing a ROM read
    // digitalWrite(ECS, HIGH);
    // digitalWrite(RCS, LOW);
    // digitalWrite(RST, LOW);
    // delay(10);
    // digitalWrite(RST, HIGH);

// If performing a save read
    digitalWrite(ECS, HIGH);
    digitalWrite(RCS, HIGH);
    digitalWrite(RST, LOW);
    delay(10);
    digitalWrite(RST, HIGH);


// writeByte(123);
}

void pulseClock() {
  digitalWrite(CLK, HIGH);
  delayMicroseconds(1);
  digitalWrite(CLK, LOW);
  delayMicroseconds(1);
}

void send8Command(long long int data){
    
  uint8_t use = data;

  uint8_t d7 = use-((use/2)*2);
  use /= 2;

  uint8_t d6 = use-((use/2)*2);
  use /= 2;

  uint8_t d5 = use-((use/2)*2);
  use /= 2;

  uint8_t d4 = use-((use/2)*2);
  use /= 2;

  uint8_t d3 = use-((use/2)*2);
  use /= 2;

  uint8_t d2 = use-((use/2)*2);
  use /= 2;

  uint8_t d1 = use-((use/2)*2);
  use /= 2;

  uint8_t d0 = use-((use/2)*2);
  use /= 2;




  Serial.print(d0);
  Serial.print(d1);
  Serial.print(d2);
  Serial.print(d3);
  Serial.print(d4);
  Serial.print(d5);
  Serial.print(d6);
  Serial.print(d7);

}

void setOut(){
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D7, OUTPUT);
}

void setIn(){
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
}


void writeByte(uint8_t data){
    
  uint8_t use = data;

  uint8_t d7 = use-((use/2)*2);
  use /= 2;

  uint8_t d6 = use-((use/2)*2);
  use /= 2;

  uint8_t d5 = use-((use/2)*2);
  use /= 2;

  uint8_t d4 = use-((use/2)*2);
  use /= 2;

  uint8_t d3 = use-((use/2)*2);
  use /= 2;

  uint8_t d2 = use-((use/2)*2);
  use /= 2;

  uint8_t d1 = use-((use/2)*2);
  use /= 2;

  uint8_t d0 = use-((use/2)*2);
  use /= 2;

  digitalWrite(D0, d0==1?HIGH:LOW);
  digitalWrite(D1, d1==1?HIGH:LOW);
  digitalWrite(D2, d2==1?HIGH:LOW);
  digitalWrite(D3, d3==1?HIGH:LOW);
  digitalWrite(D4, d4==1?HIGH:LOW);
  digitalWrite(D5, d5==1?HIGH:LOW);
  digitalWrite(D6, d6==1?HIGH:LOW);
  digitalWrite(D7, d7==1?HIGH:LOW);
  pulseClock();





  Serial.print(d0);
  Serial.print(d1);
  Serial.print(d2);
  Serial.print(d3);
  Serial.print(d4);
  Serial.print(d5);
  Serial.print(d6);
  Serial.println(d7);

}

const byte numChars = 33;
char receivedChars[numChars];  

boolean newData = false;

void loop() {
    recvWithEndMarker();
    showNewData();
}

void recvWithEndMarker() {
    static byte ndx = 0;
    char endMarker = '\n';
    char rc;
    
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (rc != endMarker) {
            receivedChars[ndx] = rc;
            ndx++;
            if (ndx >= numChars) {
                ndx = numChars - 1;
            }
        }
        else {
            receivedChars[ndx] = '\0';
            ndx = 0;
            newData = true;
        }
    }
}

void sendHex8(String use){
  unsigned long long int result = 0;
  uint8_t prelim = 0;
  int input[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for(int i = 0;i<16;i++){
    char inputc = use[i];
    if(inputc == '1') input[i] = 1;
    if(inputc == '2') input[i] = 2;
    if(inputc == '3') input[i] = 3;
    if(inputc == '4') input[i] = 4;
    if(inputc == '5') input[i] = 5;
    if(inputc == '6') input[i] = 6;
    if(inputc == '7') input[i] = 7;
    if(inputc == '8') input[i] = 8;
    if(inputc == '9') input[i] = 9;
    if(inputc == 'A' || inputc == 'a' ) input[i] = 10;
    if(inputc == 'B' || inputc == 'b' ) input[i] = 11;
    if(inputc == 'C' || inputc == 'c' ) input[i] = 12;
    if(inputc == 'D' || inputc == 'd' ) input[i] = 13;
    if(inputc == 'E' || inputc == 'e' ) input[i] = 14;
    if(inputc == 'F' || inputc == 'f' ) input[i] = 15;

  }

    // Serial.println();
    // Serial.println("--------------");
    // Serial.println("Digits: ");
    // Serial.println(input[0]);
    // Serial.println(input[1]);
    // Serial.println(input[2]);
    // Serial.println(input[3]);
    // Serial.println(input[4]);
    // Serial.println(input[5]);
    // Serial.println(input[6]);
    // Serial.println(input[7]);
    // Serial.println("--------------");
    // Serial.println();

    uint8_t toSend[8];
    for(int i = 0;i<8;i++){
      toSend[i] = (input[i*2]*16)+input[(i*2)+1];
    }

    setOut();
    for(int i = 0;i<8;i++){
      writeByte(toSend[i]);
    }




    return;
}

void sendHex1(String use){
  unsigned long long int result = 0;
  uint8_t prelim = 0;
  int input[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for(int i = 0;i<2;i++){
    char inputc = use[i];
    if(inputc == '1') input[i] = 1;
    if(inputc == '2') input[i] = 2;
    if(inputc == '3') input[i] = 3;
    if(inputc == '4') input[i] = 4;
    if(inputc == '5') input[i] = 5;
    if(inputc == '6') input[i] = 6;
    if(inputc == '7') input[i] = 7;
    if(inputc == '8') input[i] = 8;
    if(inputc == '9') input[i] = 9;
    if(inputc == 'A' || inputc == 'a' ) input[i] = 10;
    if(inputc == 'B' || inputc == 'b' ) input[i] = 11;
    if(inputc == 'C' || inputc == 'c' ) input[i] = 12;
    if(inputc == 'D' || inputc == 'd' ) input[i] = 13;
    if(inputc == 'E' || inputc == 'e' ) input[i] = 14;
    if(inputc == 'F' || inputc == 'f' ) input[i] = 15;

  }

    // Serial.println();
    // Serial.println("--------------");
    // Serial.println("Digits: ");
    // Serial.println(input[0]);
    // Serial.println(input[1]);
    // Serial.println(input[2]);
    // Serial.println(input[3]);
    // Serial.println(input[4]);
    // Serial.println(input[5]);
    // Serial.println(input[6]);
    // Serial.println(input[7]);
    // Serial.println("--------------");
    // Serial.println();

    uint8_t toSend[1];
    for(int i = 0;i<1;i++){
      toSend[i] = (input[i*2]*16)+input[(i*2)+1];
    }

    setOut();
    for(int i = 0;i<1;i++){
      writeByte(toSend[i]);
    }




    return;
}

String performRead(int len){
  setIn();
  String output = "\n";
  if(len<100){
    for(int i = 0;i<len;i++){
      output.concat(digitalRead(D0));
      output.concat(digitalRead(D1));
      output.concat(digitalRead(D2));
      output.concat(digitalRead(D3));
      output.concat(digitalRead(D4));
      output.concat(digitalRead(D5));
      output.concat(digitalRead(D6));
      output.concat(digitalRead(D7));
      output.concat("\n");
      pulseClock();
    }
    }else{
      for(int i = 0;i<50;i++){
      output.concat(digitalRead(D0));
      output.concat(digitalRead(D1));
      output.concat(digitalRead(D2));
      output.concat(digitalRead(D3));
      output.concat(digitalRead(D4));
      output.concat(digitalRead(D5));
      output.concat(digitalRead(D6));
      output.concat(digitalRead(D7));
      output.concat("\n");
      pulseClock();
      }

      for(int i = 0;i<len-100;i++){
      digitalRead(D0);
      digitalRead(D1);
      digitalRead(D2);
      digitalRead(D3);
      digitalRead(D4);
      digitalRead(D5);
      digitalRead(D6);
      digitalRead(D7);
      pulseClock();
      }

      output.concat("...\n");

      for(int i = 0;i<50;i++){
      output.concat(digitalRead(D0));
      output.concat(digitalRead(D1));
      output.concat(digitalRead(D2));
      output.concat(digitalRead(D3));
      output.concat(digitalRead(D4));
      output.concat(digitalRead(D5));
      output.concat(digitalRead(D6));
      output.concat(digitalRead(D7));
      output.concat("\n");
      pulseClock();
      }
    }
  return output;
}

void sendHex16(String use){
  sendHex8(use.substring(0, 15));
  sendHex8(use.substring(16, 31));
}

void setSPI(){
  pinMode(D5, OUTPUT);
  pinMode(D6, INPUT);
  pinMode(D7, OUTPUT);
}

void sendSPI(uint8_t byte){    
  uint8_t use = byte;

  uint8_t d7 = use-((use/2)*2);
  use /= 2;

  uint8_t d6 = use-((use/2)*2);
  use /= 2;

  uint8_t d5 = use-((use/2)*2);
  use /= 2;

  uint8_t d4 = use-((use/2)*2);
  use /= 2;

  uint8_t d3 = use-((use/2)*2);
  use /= 2;

  uint8_t d2 = use-((use/2)*2);
  use /= 2;

  uint8_t d1 = use-((use/2)*2);
  use /= 2;

  uint8_t d0 = use-((use/2)*2);
  use /= 2;

  bool send[] = {d7, d6, d5, d4, d3, d2, d1, d0};


  for(int i = 0;i<8;i++){
  digitalWrite(CLK, LOW);
  digitalWrite(COPI, send[i]);
  digitalWrite(CLK, HIGH);
  } 
  
}

uint8_t readSPI(){
  uint8_t output = 0;
  int multiplier = 128;
  for(int i = 0;i<8;i++){
    digitalWrite(CLK, HIGH);
    output += digitalRead(CIPO)*multiplier;
    digitalWrite(CLK, LOW);
    multiplier /= 2;
  }

  return output;
}

void saveRead(){
  String output = "\n";
  
  // Send the 0x03000000 command
  digitalWrite(ECS, LOW);
  sendSPI(0x03);
  sendSPI(0x00);
  sendSPI(0x00);
  sendSPI(0x00);
  Serial.println(readSPI());
  Serial.println(readSPI());
  Serial.println(readSPI());
  digitalWrite(ECS, HIGH);

  



}



int readHex(String inp){
  int output = 0;
  int input[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for(int i = 0;i<4;i++){
    char inputc = inp[i];
    if(inputc == '1') input[i] = 1;
    if(inputc == '2') input[i] = 2;
    if(inputc == '3') input[i] = 3;
    if(inputc == '4') input[i] = 4;
    if(inputc == '5') input[i] = 5;
    if(inputc == '6') input[i] = 6;
    if(inputc == '7') input[i] = 7;
    if(inputc == '8') input[i] = 8;
    if(inputc == '9') input[i] = 9;
    if(inputc == 'A' || inputc == 'a' ) input[i] = 10;
    if(inputc == 'B' || inputc == 'b' ) input[i] = 11;
    if(inputc == 'C' || inputc == 'c' ) input[i] = 12;
    if(inputc == 'D' || inputc == 'd' ) input[i] = 13;
    if(inputc == 'E' || inputc == 'e' ) input[i] = 14;
    if(inputc == 'F' || inputc == 'f' ) input[i] = 15;

  }

  output = (input[0]*16*16*16)+(input[1]*16*16)+(input[2]*16)+(input[3]);

  return output;

}

void showNewData() {
    if (newData == true) {
      // Serial.print("Recieved data: ");
      String str;
      str = receivedChars;
      if(str.length() == 16){
      Serial.println("Sending command...");
      sendHex8(str);
      Serial.println("done");
      }else if(str.length() == 32){
      Serial.println("Sending command...");
      sendHex16(str);
      Serial.println("done");
      }else if(str.length() == 4){
      Serial.print("Performing read of length ");
      Serial.println(readHex(str));
      Serial.println(performRead(readHex(str)));
      Serial.println("done");
      }else if(str.length() == 2){
      Serial.println("Sending command...");
      sendHex1(str);
      Serial.println("done");
      }else if(str == "LOVEYOU"){
        simple();
      }else if(str == "ONRCS"){
        digitalWrite(RCS, HIGH);
      }else if(str == "OFRCS"){
        digitalWrite(RCS, LOW);
      }else if(str == "ONECS"){
        digitalWrite(ECS, HIGH);
      }else if(str == "OFECS"){
        digitalWrite(ECS, LOW);
      }else if(str == "ONRES"){
        digitalWrite(RST, HIGH);
      }else if(str == "OFRES"){
        digitalWrite(RST, LOW);
      }else if(str == "s"){
        setSPI();
      }else{
        Serial.println("Error: command length is not a power of 2");
      }
        newData = false;
    }
}

uint8_t readByte(){
      String output = "\n";
      uint8_t outint = 0;
      digitalWrite(CLK, HIGH);
      delayMicroseconds(1);
      if(digitalRead(D0)) outint += 128;
      if(digitalRead(D1)) outint += 64;
      if(digitalRead(D2)) outint += 32;
      if(digitalRead(D3)) outint += 16;
      if(digitalRead(D4)) outint += 8;
      if(digitalRead(D5)) outint += 4;
      if(digitalRead(D6)) outint += 2;
      if(digitalRead(D7)) outint += 1;
      digitalWrite(CLK, LOW);
      delayMicroseconds(1);
      return outint;
}

void simple(){
  // ---- READ ROM command (0xB7) ----
  sendHex1("B7");

  // Address = 0x000000
  sendHex1("00");
  sendHex1("00");
  sendHex1("00");

  // Dummy bytes (required)
  sendHex1("00");
  sendHex1("00");
  sendHex1("00");

  // CRC / padding (ignored by most carts)
  sendHex1("00");

  // Small wait before data phase
  delayMicroseconds(20);

  // Read ID1 (first 4 bytes)
  uint8_t id[4];
  for (int i = 0; i < 4; i++) {
    id[i] = readByte();
  }

  Serial.print("ID1: ");
  for (int i = 0; i < 4; i++) {
    if (id[i] < 0x10) Serial.print("0");
    Serial.print(id[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void printLong(unsigned long long int input){
  long long unsigned int part1 = input/10000000000LLU;
  long long unsigned int part2 = input-(part1*10000000000LLU);
  Serial.print(static_cast<long unsigned int>(part1));
  Serial.println(static_cast<long unsigned int>(part2));

}



