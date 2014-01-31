#define START_CMD_CHAR 'a'

int sdata;

int redPin = 3;
int greenPin = 5;
int bluePin = 6;

int redTwo = 11;
int greenTwo = 9;
int blueTwo = 10;



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
  
  if(sdata != START_CMD_CHAR){
    writeColor(255, 0, 255);// Invalid command
  return;}
  
  delay(20);
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
}