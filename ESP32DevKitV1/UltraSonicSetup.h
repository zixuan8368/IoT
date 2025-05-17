#ifndef ULTRASONICSETUP_H
#define ULTRASONICSETUP_H

#define TRIGPIN1 32
#define ECHOPIN1 36
#define TRIGPIN2 33
#define ECHOPIN2 39
#define TRIGPIN3 25
#define ECHOPIN3 34

#define SOUND_SPEED 0.034

// The distance where the ultrasonic sensor start to return 1 when distance < TRIGGER_DISTANCE
const float TRIGGER_DISTANCE = 4.00;


void initializeUltraSonic1()
{
  pinMode(TRIGPIN1, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHOPIN1, INPUT); // Sets the echoPin as an Input
}

void initializeUltraSonic2()
{
  pinMode(TRIGPIN2, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHOPIN2, INPUT); // Sets the echoPin as an Input
}

void initializeUltraSonic3()
{
  pinMode(TRIGPIN3, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHOPIN3, INPUT); // Sets the echoPin as an Input
}

void initializeUltraSonics()
{
  initializeUltraSonic1();
  initializeUltraSonic2();
  initializeUltraSonic3();
}

uint8_t readUltra1()
{
  // Clears the trigPin
  digitalWrite(TRIGPIN1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIGPIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN1, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn(ECHOPIN1, HIGH);
  
  // Calculate the distance
  float distanceCm = duration * SOUND_SPEED/2;
  
  if(distanceCm < TRIGGER_DISTANCE)
    return 1;
  else
    return 0;
}

uint8_t readUltra2()
{
  digitalWrite(TRIGPIN2, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN2, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN2, LOW);
  
  long duration = pulseIn(ECHOPIN2, HIGH);
  
  float distanceCm = duration * SOUND_SPEED/2;
  
  if(distanceCm < TRIGGER_DISTANCE)
    return 1;
  else
    return 0;
}

uint8_t readUltra3()
{
  digitalWrite(TRIGPIN3, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN3, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN3, LOW);
  
  long duration = pulseIn(ECHOPIN3, HIGH);
  
  float distanceCm = duration * SOUND_SPEED/2;

  if(distanceCm < TRIGGER_DISTANCE)
    return 1;
  else
    return 0;
}

#endif