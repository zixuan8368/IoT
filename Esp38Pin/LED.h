#ifndef LED_H
#define LED_H

#define REDLED    32
#define YELLOWLED 25

#define REDBUTTON 26
#define BLUEBUTTON 27

int activeLED = -1;
unsigned long turnOffTime = 4000;
unsigned long timer = 0;

void setupLED();
void checkButtons();
void setActiveLED(int);

void setupLED()
{
    pinMode(REDBUTTON, INPUT_PULLUP);  
    pinMode(BLUEBUTTON, INPUT_PULLUP);  

    pinMode(REDLED, OUTPUT);
    pinMode(YELLOWLED, OUTPUT);
    digitalWrite(REDLED, LOW);
    digitalWrite(YELLOWLED, LOW);
}

void checkButtons() {
  if (digitalRead(REDBUTTON) == LOW) {
    if (activeLED != 0) {
      setActiveLED(0);
      timer = millis();
    }
    delay(100); // debounce
  }
  else if (digitalRead(BLUEBUTTON) == LOW) {
    if (activeLED != 1) {
      setActiveLED(1);
      timer = millis();
    }
    delay(100); // debounce
  }
  else if(millis() - timer > turnOffTime){
    setActiveLED(-1);
    timer = millis();
    delay(100);
  }
  
}

// Turn on one LED, turn off the other
void setActiveLED(int index) {
  if (index == 0) {
    digitalWrite(REDLED, HIGH);
    digitalWrite(YELLOWLED, LOW);
  } else if (index == 1) {
    digitalWrite(REDLED, LOW);
    digitalWrite(YELLOWLED, HIGH);
  } else if (index == -1)
  {
    digitalWrite(REDLED, LOW);
    digitalWrite(YELLOWLED, LOW);
  }
  activeLED = index;
  Serial.printf("Active LED: %d\n", activeLED);
}


#endif