#include <Adafruit_NeoPixel.h>

#define START_CMD_CHAR 'a'
#define RED 'r'
#define ORANGE 'o'
#define YELLOW 'y'
#define GREEN 'g'
#define BLUE 'b'
#define INDIGO 'i'
#define PINK 'v'
#define WHITE 'w'

#define RAINBOW 's'
#define TWINKLE 't'

#define LAST_WAS_RAINBOW 2
#define LAST_WAS_TWINKLE 3
#define NONE 0

#define PIN 10

int sdata;
int lastAction = 0;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(56, PIN, NEO_GRB + NEO_KHZ800);

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
  
  rainbowCycle(5);
  return;

  if(Serial.available()<1) { 

    if (lastAction == LAST_WAS_RAINBOW) {
      rainbowCycle(5);
    } else if (lastAction == LAST_WAS_TWINKLE) {
      theaterChase(strip.Color(127, 127, 127), 50);
    }
    return;
  }

  sdata = Serial.read();

  // This setup means we buffer requests instead of fulfilling them instantly.
  // Is that a problem?  
  if(sdata != START_CMD_CHAR){
    return;
  }
  
  delay(20);

  pin_num = Serial.read();

  switch (pin_num) {
      case RED:
        colorWipe(strip.Color(255, 0, 0), 30);
        lastAction = NONE;
        break;
      case ORANGE:
        colorWipe(strip.Color(255, 140, 0), 30);
        lastAction = NONE;
        break;
      case YELLOW:
        colorWipe(strip.Color(255, 255, 0), 30);
        lastAction = NONE;
        break;
      case GREEN:
        colorWipe(strip.Color(0, 255, 0), 30);
        lastAction = NONE;
        break;
      case BLUE:
        colorWipe(strip.Color(0, 0, 255), 30);
        lastAction = NONE;
        break;
      case INDIGO:
        colorWipe(strip.Color(75, 0, 130), 30);
        lastAction = NONE;
        break;
      case PINK:
        colorWipe(strip.Color(255, 0, 255), 30);
        lastAction = NONE;
        break;
      case WHITE:
        colorWipe(strip.Color(255, 255, 255), 30);
        lastAction = NONE;
        break;
      case RAINBOW:
        rainbowCycle(5);
        lastAction = LAST_WAS_RAINBOW;
        break;
      case TWINKLE:
        theaterChase(strip.Color(127, 127, 127), 60);
        lastAction = LAST_WAS_TWINKLE;
        break;
      default:
        rainbowCycle(5);
  }

} 

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*2; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j+= 4) {     // cycle all 256 colors in the wheel
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

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

