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

#define RAINBOW 'f'
#define TWINKLE 't'


#define NONE 0
#define LAST_WAS_RAINBOW 2
#define LAST_WAS_TWINKLE 4

#define PIN 11

int sdata;

int lastAction;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup(){
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  strip.begin();
  strip.show();
}

void loop(){

  /*colorWipe(strip.Color(255, 0, 255), 100);
  
  colorWipe(strip.Color(0, 255, 255), 100);
  rainbowCycle(30);
  theaterChaseRainbow(70);
  theaterChase(strip.Color(127, 127, 127), 70);*/

  Serial.flush();
  int pin_num = 0;
  int pin_val = 0;
  
  if(Serial.available()<1){ 
    //theaterChase(strip.Color(150, 150, 150), 70); 
    if (lastAction == LAST_WAS_RAINBOW) {
      rainbowCycle(30);
    }
    else if (lastAction == LAST_WAS_TWINKLE) {
      theaterChase(strip.Color(150, 150, 150), 70);
    }
    return;}
  sdata = Serial.read();

  // This setup means we buffer requests instead of fulfilling them instantly.
  // Is that a problem?  
  if(sdata != START_CMD_CHAR){
    // Do last thing.
    return;
  }

  delay(20);

  pin_num = Serial.read();

  switch (pin_num) {
      case RED:
        colorWipe(strip.Color(255, 0, 0), 100);
        lastAction = NONE;
        break;
      case ORANGE:
        colorWipe(strip.Color(255, 140, 0), 100);
        lastAction = NONE;
        break;
      case YELLOW:
        colorWipe(strip.Color(255, 255, 0), 100);
        lastAction = NONE;
        break;
      case GREEN:
        colorWipe(strip.Color(0, 255, 0), 100);
        lastAction = NONE;
        break;
      case BLUE:
        colorWipe(strip.Color(0, 0, 255), 100);
        lastAction = NONE;
        break;
      case INDIGO:
        colorWipe(strip.Color(75, 0, 130), 100);
        lastAction = NONE;
        break;
      case PINK:
        colorWipe(strip.Color(255, 0, 255), 100);
        lastAction = NONE;
        break;
      case WHITE:
        colorWipe(strip.Color(150, 150, 150), 100);
        lastAction = NONE;
        break;
      case TWINKLE:
        theaterChase(strip.Color(150, 150, 150), 70);
        lastAction = LAST_WAS_TWINKLE;
        break;
      case RAINBOW:
        rainbowCycle(30);
        lastAction = LAST_WAS_RAINBOW;
      //default:
        //rgbLedRainbow(numRGBleds, 10, 1, 27); // slow rainbow
  }
  
} 

// Colorwipe that works on the sleeves
void colorWipe(uint32_t c, uint8_t wait) {
  // Four distinct sleeves, really only two though.  
  for(uint16_t i=0; i<28; i++) {
    for(uint16_t j=0; j<2; j++) {
      strip.setPixelColor(i + 28*j, c);

      strip.setPixelColor(55 - 28*j - i, c);


      // 0 -> 13, 28 -> 41  Forward
      // 27 -> 14, 55 -> 42 Back

      delay(wait);
    }
      strip.show();
  }
}
  
void rainbow(uint8_t wait) {
  uint16_t i, j, k;

  for(j=0; j<256; j++) {
    for(i=0; i<14; i++) {
      for(k=0; k<2; k++) {

        strip.setPixelColor(i + 28*k, Wheel((j) % 255));
        strip.setPixelColor(55-28*k - i, Wheel((j) % 255));

      }
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j, k;

  for(j=0; j<256*1; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< 14; i++) {
      for(k=0; k<2; k++) {
        
        strip.setPixelColor(i + 28*k, Wheel(((8*i * 256) + j) % 255));        
        strip.setPixelColor(55-28*k - i, Wheel(((8*i * 256) + j) % 255));
        // 0 -> 13, 28 -> 41  Forward
        // 27 -> 14, 55 -> 42 Back
      }
    }
    strip.show();         
    delay(wait);
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



// Fix these?
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
