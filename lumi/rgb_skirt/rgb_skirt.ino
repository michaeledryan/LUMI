#define START_CMD_CHAR 'a'

int sdata;

int redPin = 3;
int greenPin = 5;
int bluePin = 6;

void setup(){
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  unsigned int rgbColour[3];
 
  // Start off with red.
  rgbColour[0] = 255;
  rgbColour[1] = 0;
  rgbColour[2] = 0;  
 
  // Choose the colours to increment and decrement.
  for (int decColour = 0; decColour < 2; decColour += 1) {
    int incColour = decColour == 1 ? 0 : decColour + 1;
 
    // cross-fade the two colours.
    for(int i = 0; i < 255; i += 1) {
      rgbColour[decColour] -= 1;
      rgbColour[incColour] += 1;
      
      setColourRgb(rgbColour[0], rgbColour[1], rgbColour[0]);
      delay(20);
    }
  }
}

 
void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
 }

/*
void setup(){
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redTwo, OUTPUT);    
  pinMode(greenTwo, OUTPUT);
  pinMode(blueTwo, OUTPUT);

}
void loop(){
  Serial.flush();
  int pin_num = 0;
  int pin_val = 0;
  

  if(Serial.available()<1){ return;}
  sdata = Serial.read();
  
  if(sdata != START_CMD_CHAR){ return;}
  
  pin_num = Serial.read();
  if(pin_num == 'r'){
    writeColor(255, 0, 0);
  }
  else if(pin_num == 'o'){
    writeColor(255, 140, 0);
  }
  else if(pin_num == 'y'){
    writeColor(255, 200, 0);
  }
  else if(pin_num == 'g'){
    writeColor(0, 128, 0);
  }
  else if(pin_num == 'b'){
    writeColor(0, 0, 255);
  }
  else if(pin_num == 'i'){
    writeColor(75, 0, 130);
  }
  else if(pin_num == 'v'){
    writeColor(255, 0, 255);
  }
  else if(pin_num == 'w'){
    writeColor(255, 255, 255);
  }
  else{
    return;
  }  
}

void writeColor(int r, int g, int b){
  analogWrite(redPin, r);
  analogWrite(redTwo, r * 3 / 5);
  analogWrite(greenPin, g);
  analogWrite(greenTwo, g);
  analogWrite(bluePin, b);
  analogWrite(blueTwo, b);
}*/