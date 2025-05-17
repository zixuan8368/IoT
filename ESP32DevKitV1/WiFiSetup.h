#ifndef WIFISETUP_H
#define WIFISETUP_H

#include <WiFi.h>
#include <DisplaySetup.h>

const char* ssid = "POCO F5 PRO";
const char* password = "12345678";

void connectToWiFi() {
  WiFi.begin(ssid, password);
  display.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
  }
}



#endif