
#define ARDBUFFER 16
#include <stdarg.h>
#include <Arduino.h>

#include <SoftwareSerial.h>
#include <ModbusRtu.h>
#include <stdio.h>

int i = 0;
uint16_t dataChunk[6] =   {1, 50, 50, 50, 255, 0};//Dane Z Modbusa
SoftwareSerial mySerial(11, 12); // RX, TX

Modbus slave(15,0,0); //ID:15

void setup() {
  mySerial.begin(115200);
  slave.begin(57600, SERIAL_8N1); //DataB:8 Parity:None StopB:1
  pinMode(8, OUTPUT);
}

void loop() {
  //slave.poll( dataChunk, 6 ); 
  
  
  
    mySerial.print(dataChunk[0]);
    mySerial.print('-');
    mySerial.print(dataChunk[1]);
    mySerial.print('-');
    mySerial.print(dataChunk[2]);
    mySerial.print('-');
    mySerial.print(dataChunk[3]);
    mySerial.print('-');
    mySerial.print(dataChunk[4]);
    mySerial.print('-');
    mySerial.print(dataChunk[5]);
    mySerial.println();
  
  
  
}


















