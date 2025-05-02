#ifndef WIFISETUP_H
#define WIFISETUP_H

#include <WiFi.h>
#include <DisplaySetup.h>

const char* WIFI_SSID = "POCO F5 PRO";
const char* WIFI_PASSWORD = "29Ncit02$";
//const char* WIFI_SSID = "Wifi@C0907_2.4G";
//const char* WIFI_PASSWORD = "qiuwola@c0907";

void connectToWiFi()
{
  display.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    display.display();
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("WiFi connected");
  String ip = WiFi.localIP().toString();
  Serial.println("IP Address: " + ip);
  display.display();
  delay(1500);
}

#endif