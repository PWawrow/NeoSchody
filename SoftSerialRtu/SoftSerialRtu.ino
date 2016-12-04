#include <ModbusRtu.h>
#include <SoftwareSerial.h>

const byte rxPin = 10;
const byte txPin = 11;

uint16_t data[5]={0,0,0,0,0};


Modbus slave(15,0,0);
SoftwareSerial serial2 (rxPin, txPin);

void setup() {
  slave.begin(115200, SERIAL_8N1);
  serial2.begin(115200);

}

void loop() {
  slave.poll(data, 5);
  serial2.println(data[0]+','+data[1]+','+data[2]+','+data[3]+','+data[4]);

}
