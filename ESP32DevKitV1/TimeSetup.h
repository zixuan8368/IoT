#ifndef TIMES_SETUP_H
#define TIMES_SETUP_H

#include "time.h"
#include "DisplaySetup.h"  // Include DisplaySetup.h to access the display object

const char* ntpServer = "time.google.com";
const long gmtOffset_sec = 8 * 3600;  // GMT+8 for Malaysia
const int daylightOffset_sec = 0;

// Setup NTP time
void setupTime() {
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
}

// Display local time on OLED
void displayLocalTime() {
  struct tm timeinfo;
  char timeStr[9] = "--:--:--";  // Default time in case of failure

  if (getLocalTime(&timeinfo)) {
    // If successful, format the time as HH:MM:SS
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);
  }

  display.print("Time: ");
  display.println(timeStr);
  display.display();
}

String getCurrentTime()
{
  struct tm timeinfo;
  char timeStr[9] = "--:--:--";  // Default time in case of failure

  if (getLocalTime(&timeinfo)) {
    // If successful, format the time as HH:MM:SS
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);
  }
  return timeStr;
}

#endif
