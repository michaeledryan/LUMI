// PWM pins
int pin1 = 3;
int pin2 = 5;
int pin3 = 6;
int pin4 = 9;
int pin5 = 10;
int pin6 = 11;

// Digital pins
int pin7 = 12;
int pin8 = 13;

int buttonPin = 2;
int buttonState;
int lastButtonState = LOW;

long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

bool twinkle = true;

int pins[8] = {3,5,6,9,10,11,12,13};
unsigned long idleTime[8];

void setup(){
  Serial.begin(9600);
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop(){
  
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        twinkle = !twinkle;
      }
    }
  }

  if (!twinkle) {
    writeSolid();
    delay(1000);

  } else {

    digitalWrite(pins[random(0,8)], HIGH);   // sets a random LED on
    delay(200);
                  // wait for some time (between 0.1 and 3 seconds)
    if (random(2) == 0){

    digitalWrite(pins[random(0,8)], LOW);    // sets a random LED off
    delay(100);              // wait for some time (between 0.1 and 3 seconds)
    }                  

  }
}



void writeSolid(){
  analogWrite(pin1, 255);
  analogWrite(pin2, 255);
  analogWrite(pin3, 255);
  analogWrite(pin4, 255);
  analogWrite(pin5, 255);
  analogWrite(pin6, 255);
  digitalWrite(pin7, HIGH);
  digitalWrite(pin8, HIGH);
}