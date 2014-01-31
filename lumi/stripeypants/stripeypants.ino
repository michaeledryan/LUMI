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
  
  if(sdata != START_CMD_CHAR){
  theaterChase(strip.Color(127, 127, 127), 50); // White
  return;}
  
  delay(20);
  //Serial.println("we're good");
  pin_num = Serial.read();
  //pin_val = Serial.read();
  if(pin_num == 'r'){
    colorWipe(strip.Color(255, 0, 0), 50); // Red
  }
  else if(pin_num == 'b'){
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
  }
  else if(pin_num == 'g'){
    colorWipe(strip.Color(0, 255, 0), 50); // Green
  }
  else{
    return;}
  
  /*if(pin_num == P1){
    pin_num = 10;}
  else if(pin_num == P2){
    pin_num = 9;}
  else if(pin_num == P3){
    pin_num = 11;}
  else{
    return;}
  /*
  if(pin_val == PIN_HIGH){
    pin_val = HIGH;
    colorWipe(strip.Color(0, 0, 255), 50); // Blue}
  else if(pin_val == PIN_LOW){
    pin_val = LOW;}
  else {
    return;}
  */
  //digitalWrite(pin_num, pin_val);
  
  
} 

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
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

