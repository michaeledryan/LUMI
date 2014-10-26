#define START_CMD_CHAR 'a'
#define RED 'r'
#define ORANGE 'o'
#define YELLOW 'y'
#define GREEN 'g'
#define BLUE 'b'
#define INDIGO 'i'
#define PINK 'v'
#define WHITE 'w'

#define RAINBOW_SLIDE 's'
#define RAINBOW_FADE 'f'

#define NONE 0
#define LAST_WAS_RAINBOW_SLIDE 2
#define LAST_WAS_RAINBOW_FADE 3


// ShiftPWM uses timer1 by default. To use a different timer, before '#include <ShiftPWM.h>', add
// #define SHIFTPWM_USE_TIMER2  // for Arduino Uno and earlier (Atmega328)
// #define SHIFTPWM_USE_TIMER3  // for Arduino Micro/Leonardo (Atmega32u4)

// Clock and data pins are pins from the hardware SPI, you cannot choose them yourself if you use the hardware SPI.
// Data pin is MOSI (Uno and earlier: 11, Leonardo: ICSP 4, Mega: 51, Teensy 2.0: 2, Teensy 2.0++: 22) 
// Clock pin is SCK (Uno and earlier: 13, Leonardo: ICSP 3, Mega: 52, Teensy 2.0: 1, Teensy 2.0++: 21)

// You can choose the latch pin yourself.
const int ShiftPWM_latchPin=8;

// ** uncomment this part to NOT use the SPI port and change the pin numbers. This is 2.5x slower **
// #define SHIFTPWM_NOSPI
// const int ShiftPWM_dataPin = 11;
// const int ShiftPWM_clockPin = 13;


// If your LED's turn on if the pin is low, set this to true, otherwise set it to false.
const bool ShiftPWM_invertOutputs = false; 

// You can enable the option below to shift the PWM phase of each shift register by 8 compared to the previous.
// This will slightly increase the interrupt load, but will prevent all PWM signals from becoming high at the same time.
// This will be a bit easier on your power supply, because the current peaks are distributed.
const bool ShiftPWM_balanceLoad = false;

#include <ShiftPWM.h>   // include ShiftPWM.h after setting the pins!

// Here you set the number of brightness levels, the update frequency and the number of shift registers.
// These values affect the load of ShiftPWM.
// Choose them wisely and use the PrintInterruptLoad() function to verify your load.
// There is a calculator on my website to estimate the load.

unsigned char maxBrightness = 255;
unsigned char pwmFrequency = 75;
unsigned int numOutputs = 27;
int numRegisters = 4;
int numRGBleds = 9;

int sdata;
int lastAction;


void setup(){
  Serial.begin(9600);

  // Sets the number of 8-bit registers that are used.
  ShiftPWM.SetAmountOfRegisters(numRegisters);

  // SetPinGrouping allows flexibility in LED setup. 
  // If your LED's are connected like this: RRRRGGGGBBBBRRRRGGGGBBBB, use SetPinGrouping(4).
  ShiftPWM.SetPinGrouping(1); //This is the default, but I added here to demonstrate how to use the funtion
  
  ShiftPWM.Start(pwmFrequency,maxBrightness);
}

void loop()
{

//rgbLedRainbow(numRGBleds, 5, 3, 27); // Fast, over all LED's

//  rainbowFade(30);
  Serial.flush();
  int pin_num = 0;
  int pin_val = 0;
  
  if(Serial.available()<1) { 

/*    ShiftPWM.SetAll(100);
    delay(1000);
    ShiftPWM.SetAll(0);
    delay(1000);*/
    // Have to keep the things going if they are rainbow fades / slides
    if (lastAction == LAST_WAS_RAINBOW_FADE) {
      rainbowFade(10);
    }
    else if (lastAction == LAST_WAS_RAINBOW_SLIDE) {
      rgbLedRainbow(numRGBleds, 5, 1, 27); // Fast, over all LED's
    } 
    return;
  }
  sdata = Serial.read();

  // This setup means we buffer requests instead of fulfilling them instantly.
  // Is that a problem?  
  if(sdata != START_CMD_CHAR){
    // Do last thing.
  }
  
  delay(20);

  // I want it to keep doing rainbow if 

  pin_num = Serial.read();
  switch (pin_num) {
      case RED:
        ShiftPWM.SetAllRGB(255, 0, 0);
        lastAction = NONE;
        break;
      case ORANGE:
        ShiftPWM.SetAllRGB(255, 140, 0);
        lastAction = NONE;
        break;
      case YELLOW:
        ShiftPWM.SetAllRGB(255, 255, 0);
        lastAction = NONE;
        break;
      case GREEN:
        ShiftPWM.SetAllRGB(0, 255, 0);
        lastAction = NONE;
        break;
      case BLUE:
        ShiftPWM.SetAllRGB(0, 0, 255);
        lastAction = NONE;
        break;
      case INDIGO:
        ShiftPWM.SetAllRGB(75, 0, 130);
        lastAction = NONE;
        break;
      case PINK:
        ShiftPWM.SetAllRGB(255, 0, 255);
        lastAction = NONE;
        break;
      case WHITE:
        ShiftPWM.SetAll(170);
        lastAction = NONE;
        break;
      case RAINBOW_SLIDE:
        rgbLedRainbow(numRGBleds, 5, 1, 27); // Fast, over all LED's
        lastAction = LAST_WAS_RAINBOW_SLIDE;
        break;
      case RAINBOW_FADE:
        hueShiftAll(); 
        lastAction = LAST_WAS_RAINBOW_FADE;
      default:
        rgbLedRainbow(numRGBleds, 10, 1, 27); // slow rainbow
  }

//  delay(200);
}

void rainbowFade(int wait) {
  for(int i=0; i < 360, i++;){
    ShiftPWM.SetAllHSV(i , 255, 255);
    delay(wait);
  }

  for(int i=359; i >= 0, i--;){
    ShiftPWM.SetAllHSV(0,255,255);
    delay(wait);
  }

}

  // Function library:
  // Fade in and fade out all outputs one by one fast. Usefull for testing your hardware. Use OneByOneSlow when this is going to fast.
  // ShiftPWM.OneByOneFast();

  // Set all to a certain white brightness level
  // ShiftPWM.SetAll(int brightness);  

  // Set a particular one to a white brightness
  // ShiftPWM.SetOne(int brightness);

  // Also in RGB flavors
  // ShiftPWM.SetRGB
  // ShiftPWM.SetAllRGB

  // Random LED to color:
  // ShiftPWM.SetHSV(random(numRGBleds),random(360),255,255);


  // Peak up, Christmas tree style.
 /*
  int currentLevel = 0;
  for(int i=0;i<40;i++){
    prevPeak = peak;
    while(abs(peak-prevPeak)<5){
      peak =  random(numRGBleds); // pick a new peak value that differs at least 5 from previous peak
    }
    // animate to new top
    while(currentLevel!=peak){
      if(currentLevel<peak){
        currentLevel++;
      }
      else{
        currentLevel--;
      }
      for(int led=0;led<numRGBleds;led++){
        if(led<=currentLevel){
          int hue = (numRGBleds-1-led)*120/numRGBleds; // From green to red
          ShiftPWM.SetHSV(led,hue,255,255); 
        }
        else{
          ShiftPWM.SetRGB(led,0,0,0);
        }
      }
      delay((64/numRGBleds)*(numRGBleds-currentLevel)); // go slower near the top
    }
  }*/


  // Rainbow across all of them:
  // A moving rainbow for RGB leds:
  // rgbLedRainbow(numLEDS, delayVal, numCycles, rainbowWidth); // Fast, over all LED's
  // rgbLedRainbow(numRGBleds, 5, 3, numRegisters*8/3); // Fast, over all LED's
  // rgbLedRainbow(numRGBleds, 10, 3, numRegisters*8/3*4); //slower, wider than the number of LED's


void hueShiftAll(){  // Hue shift all LED's
  for(int hue = 0; hue<360; hue++){
    ShiftPWM.SetAllHSV(hue, 255, 255); 
    delay(50);
  } 
}


void rgbLedRainbow(int numRGBLeds, int delayVal, int numCycles, int rainbowWidth){
  // Displays a rainbow spread over a few LED's (numRGBLeds), which shifts in hue. 
  // The rainbow can be wider then the real number of LED's.

  ShiftPWM.SetAll(0);
  for(int cycle=0;cycle<numCycles;cycle++){ // loop through the hue shift a number of times (numCycles)
    for(int colorshift=0;colorshift<360;colorshift++){ // Shift over full color range (like the hue slider in photoshop)
      for(int led=0;led<numRGBLeds;led++){ // loop over all LED's
        int hue = ((led)*360/(rainbowWidth-1)+colorshift)%360; // Set hue from 0 to 360 from first to last led and shift the hue
        ShiftPWM.SetHSV(led, hue, 255, 255); // write the HSV values, with saturation and value at maximum
      }
      delay(delayVal); // this delay value determines the speed of hue shift
    } 
  }  
}
