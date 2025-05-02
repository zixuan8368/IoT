#ifndef TIMESETUP_H
#define TIMESETUP_H

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

  if (!getLocalTime(&timeinfo)) {
  Serial.println("Failed to get time from NTP!");
  }
  else if (getLocalTime(&timeinfo)) {
    // If successful, format the time as HH:MM:SS
    strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);
  }

  display.clearDisplay();  // Clear display before drawing new content
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Time:");
  display.println(timeStr);
  display.display();
}

String getLocalTime()
{
  struct tm timeinfo;
  char timeStr[9] = "--:--:--";
  strftime(timeStr, sizeof(timeStr), "%H:%M:%S", &timeinfo);
  return timeStr;
}

#endif
