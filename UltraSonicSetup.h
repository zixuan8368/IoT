#ifndef ULTRASONICSETUP_H
#define ULTRASONICSETUP_H

#define TRIGPIN1 4
#define ECHOPIN1 16

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void initializeUltraSonic1()
{
  pinMode(TRIGPIN1, OUTPUT); // Sets the trigPin as an Output
  pinMode(ECHOPIN1, INPUT); // Sets the echoPin as an Input
}

bool readDistance1()
{
  // Clears the trigPin
  digitalWrite(TRIGPIN1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(TRIGPIN1, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN1, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(ECHOPIN1, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;
  
  // Convert to inches
  distanceInch = distanceCm * CM_TO_INCH;
  
  if(distanceCm < 5.00)
  {
    return true;
  }
  else
  {
    return false;
  }
  
  Serial.println(distanceCm);

}

#endif