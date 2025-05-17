#ifndef DATA_h
#define DATA_H

#include <vector>
#include <RFIDSetup.h>

const float rate[3] = {1.50, 2.50, 3.00};
const float penalty = 10.00;
std::vector <String> enteredCar = {}; // Store the ID of the cars currently in the carpark
std::vector <String> entryTime = {};  // Store the entry time of the cars

float balance;
bool isEntry(String);
void addEntry(String, String);
String getEntryTime(String);
float removeEntry(String, String);
float calculateFare(String, String);
void setFare();


bool isEntry(String strID)
{
  // Car goes out from the carpark
  for(int i = 0; i < enteredCar.size(); i++)
  {
      if(enteredCar[i] == strID)
      {  
        return false;
      }
  }
  return true;
}

// Add vehicle entered to the carpark
void addEntry(String strID, String strTime)
{
  enteredCar.push_back(strID);
  entryTime.push_back(strTime);
}

// Get the entry time of the vehicle
String getEntryTime(String strID)
{
  for(int i = 0; i < enteredCar.size(); i++)
    if(enteredCar[i] == strID)
      return entryTime[i];
}

// Remove Entry and calculate totalFare
float removeEntry(String strID, String outTime)
{
  for (int i = 0; i < enteredCar.size(); i++)
  {
    if (enteredCar[i] == strID)
    {
      String entry = entryTime[i];
      float fare = calculateFare(entry, outTime);

      enteredCar.erase(enteredCar.begin() + i);
      entryTime.erase(entryTime.begin() + i);

      return fare;
    }
  }
  return 0;
}

float calculateFare(String entryTime, String outTime)
{
  int entryHours = entryTime.substring(0, 2).toInt();   
  int entryMinutes = entryTime.substring(3, 5).toInt();
  int totalEntryMinutes = entryHours * 60 + entryMinutes;

  int outHours = outTime.substring(0, 2).toInt();   
  int outMinutes = outTime.substring(3, 5).toInt(); 
  int totalOutMinutes = outHours * 60 + outMinutes;

  int difference = totalOutMinutes - totalEntryMinutes;
  float fare = 0;
  int index = 0;

  while(difference > 0)
  {
    difference -= 1;
    fare += rate[index];
    if(index < 2)
      index++;
  }
  return fare;
}

#endif