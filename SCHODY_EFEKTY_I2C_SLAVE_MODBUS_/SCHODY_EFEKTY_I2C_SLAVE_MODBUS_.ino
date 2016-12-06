#include <Wire.h>
#include <ModbusRtu.h>





Modbus slave(15,0,0); //ID:15
uint16_t dataChunk[6] =   {0, 0, 0, 0, 255, 0};
uint8_t data[6] =   {0, 0, 0, 0, 255, 0};
int curdata;


void setup() {
  Wire.begin(0x04);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  slave.begin(57600, SERIAL_8N1);
}

void loop() {
  slave.poll(dataChunk, 6);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
    for(int i=0; i<6;i++){
      data[i] = dataChunk[i];
    }
    Wire.write(data,6);
  
  
}


