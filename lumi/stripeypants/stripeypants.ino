#include <Adafruit_NeoPixel.h>

#define START_CMD_CHAR 'a'
#define PIN_HIGH 'b'
#define PIN_LOW 'c'
#define P1 'd'
#define P2 'e'
#define P3 'f'

#define PIN 6

int sdata;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup(){
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  strip.begin();
  strip.show();
}
void loop(){
  Serial.flush();
  int pin_num = 0;
  int pin_val = 0;
  
  if(Serial.available()<1){ return;}
  sdata = Serial.read();

  // This setup means we buffer requests instead of fulfilling them instantly.
  // Is that a problem?  
  if(sdata != START_CMD_CHAR){
    theaterChase(strip.Color(127, 127, 127), 50); // White
    return;
  }
  
  delay(20);

  pin_num = Serial.read();
  if(pin_num == 'r'){
    colorWipe(strip.Color(255, 0, 0), 50); // Red
  }
  else if(pin_num == 'b'){
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
  }
  else if(pin_num == 'g'){
    colorWipe(strip.Color(0, 255, 0), 50); // Green
  }
  else if (pin_num == 'z') {
    theaterChaseRainbow(100);
  }
  
} 

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

