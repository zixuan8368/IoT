#ifndef SERVOSETUP_H
#define SERVOSETUP_H

#include <ESP32Servo.h>

#define SERVO1 26
#define SERVO2 27

Servo servo1;
Servo servo2;

const int defaultDegree = 90;
int servo1Degrees;
int servo2Degrees;

void initializeServos()
{
  servo1.attach(SERVO1);
  servo2.attach(SERVO2);
  servo1.write(defaultDegree);
  servo2.write(defaultDegree);
  servo1Degrees = defaultDegree;
  servo2Degrees = defaultDegree;
}

void raiseServo1()
{
  for (int i = servo1Degrees; i > 0; i -= 2)
  {
    servo1.write(i);
    delay(20);
  }
  servo1Degrees = 0;
}

void raiseServo2()
{
  for (int i = servo2Degrees; i > 0; i -= 2)
  {
    servo2.write(i);
    delay(20);
  }
  servo2Degrees = 0;
}

void lowerServo1()
{
  for (int i = servo1Degrees; i < 90; i += 2)
  {
    servo1.write(i);
    delay(20);
  }
  servo1Degrees = 90;
}

void lowerServo2()
{
  for (int i = servo2Degrees; i < 90; i += 2)
  {
    servo2.write(i);
    delay(20);
  }
  servo2Degrees = 90;
}

#endif