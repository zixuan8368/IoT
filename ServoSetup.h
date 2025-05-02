#ifndef SERVOSETUP_H
#define SERVOSETUP_H

#include <ESP32Servo.h>
#define POLE1PIN 4

Servo pole1;
int pole1Degree = 0;


void setDegreePole1(int degrees)
{
  pole1.write(degrees);  
  Serial.print(degrees);
}


void liftPole1()
{
  for(int posDegrees = 90; posDegrees < 180; posDegrees++) {
    pole1.write(posDegrees);
    delay(50);
  }
}

void initializeServo(int degrees)
{
  pole1.attach(POLE1PIN);
  setDegreePole1(degrees);
}

void closePole1()
{
  for(int posDegrees = 180; posDegrees > 90; posDegrees--) {
    pole1.write(posDegrees);
    delay(50);
  }
}


#endif