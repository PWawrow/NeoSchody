#include <FastLED.h>





// Wire Master Reader
#include <Wire.h>
int buff[6];

#define NUM_LEDS 30

CRGB leds[NUM_LEDS];
#define PIN 11

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause);
void FadeInOut(byte red, byte green, byte blue);
void Knight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);
void rainbowCycle(int SpeedDelay);
void onoffon(byte red, byte green, byte blue, int SpeedDelay);
void puls();
void nightMode();
void colorWipe(byte red, byte green, byte blue, int del);
void KnightBCK(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay);


void setup()
{
  Wire.begin();        // join i2c bus (address optional for master)
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
}

void loop()
{
  Wire.requestFrom(0x04, 6);    // request 3 bytes from slave device #2
  for (int i = 0; i < 6; i++) {
    buff[i] = Wire.read();
  }
  FastLED.setBrightness(buff[4]);
  switch (buff[0]) {
    case 0:
      setAll(0,0,0);
      break;
    case 1:
      FadeInOut(buff[1], buff[2], buff[3]);
      break;
    case 2:
      Strobe(buff[1], buff[2], buff[3], 10, 50, 1000);
      break;
    case 3:
      Knight(buff[1], buff[2], buff[3], 3, 30, 80);
      break;
    
    case 4:
      rainbowCycle(20);
      break;
    case 5:
      onoffon(buff[1], buff[2], buff[3], 70);
      break;
    case 6:
      puls();
      break;
    case 7:
      nightMode();
      break;
    case 8:
      setAll(buff[1], buff[2], buff[3]);
      break;
    case 9:
      colorWipe(buff[1], buff[2], buff[3], 25);
      break;
    case 10:
      KnightBCK(buff[1], buff[2], buff[3], 3, 30, 80);
      break;
    
      
      
      
  }


}
void showStrip() {
  FastLED.show();

}

void setPixel(int Pixel, byte red, byte green, byte blue) {

  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;

}

void setAll(byte red, byte green, byte blue) {
  for (int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}
void FadeInOut(byte red, byte green, byte blue) {
  float r, g, b;

  for (int k = 0; k < 256; k = k + 1) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    showStrip();
  }

  for (int k = 255; k >= 0; k = k - 2) {
    r = (k / 256.0) * red;
    g = (k / 256.0) * green;
    b = (k / 256.0) * blue;
    setAll(r, g, b);
    showStrip();
  }
}

void Strobe(byte red, byte green, byte blue, int StrobeCount, int FlashDelay, int EndPause) {
  for (int j = 0; j < StrobeCount; j++) {
    setAll(red, green, blue);
    showStrip();
    delay(FlashDelay);
    setAll(0, 0, 0);
    showStrip();
    delay(FlashDelay);
  }

  delay(EndPause);
}
void Knight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue); 
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  
  delay(ReturnDelay);
}
void KnightBCK(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){

  for(int i = 0; i < NUM_LEDS-EyeSize-2; i++) {
    setAll(red/15,green/15,blue/15);
    setPixel(i, red/9, green/9, blue/9);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red/9, green/9, blue/9); 
    }
    setPixel(i+EyeSize+1,red/9, green/9, blue/9);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);
  
  for(int i = NUM_LEDS-EyeSize-2; i > 0; i--) {
    setAll(red/15,green/15,blue/15);
    setPixel(i, red/9, green/9, blue/9);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red/9, green/9, blue/9); 
    }
    setPixel(i+EyeSize+1, red/9, green/9, blue/9);
    showStrip();
    delay(SpeedDelay);
  }
  
  delay(ReturnDelay);
}
void rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUM_LEDS; i++) {
      c=Wheel(((i * 256 / NUM_LEDS) + j) & 255);
      setPixel(i, *c, *(c+1), *(c+2));
    }
    showStrip();
    delay(SpeedDelay);
  }
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}
void onoffon(byte red, byte green, byte blue, int SpeedDelay) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUM_LEDS; i=i+3) {
        setPixel(i+q, red, green, blue);    
      }
      showStrip();
     
      delay(SpeedDelay);
     
      for (int i=0; i < NUM_LEDS; i=i+3) {
        setPixel(i+q, 0,0,0);        
      }
    }
  }
}
void puls(){

for (int i = 0; i < NUM_LEDS; i++ ) {
    setAll(15,15,15);    
    setPixel(i,25,25,25);
    setPixel(i+1,30,30,30);
    setPixel(i+2,35,35,35);
    setPixel(i+3,35,35,35);
    setPixel(i+4,35,35,35);
    setPixel(i+5,30,30,30);
    setPixel(i+6,25,25,25);
    showStrip();
    delay(15);
  }
  delay(1000);
}
void nightMode(){
  if(leds[15].r != 0 && leds[15].g != 0 && leds[15].b != 0)setAll(0,0,0);
  setPixel(1,100,100,100);
  setPixel(3,100,100,100);
  setPixel(NUM_LEDS,100,100,100);
  setPixel(NUM_LEDS-3,100,100,100);
  showStrip();
}
void colorWipe(byte red, byte green, byte blue, int del) {
  for(uint16_t i=0; i<NUM_LEDS; i++) {
      setAll(red/15,green/15,blue/15);
      setPixel(i, red/5, green/5, blue/5);
      setPixel(i+1,red/4,green/4,blue/4);
      setPixel(i+2, red/5, green/5, blue/5);
      showStrip();
      delay(del);
  }
}

