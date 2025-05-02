#include <WiFiSetup.h>
#include <TimeSetup.h>
#include <RFIDSetup.h>
#include <DisplaySetup.h>
#include <Data.h>


void displaySSD1306();
int lastScanTime = millis();
bool showMessage = false;
String strTime = "";
String lastID = "";

vector<String> scannedIDs;


void setup()
{
  Serial.begin(115200);
  initializeDisplay();
  connectToWiFi();
  initializeRFID();
  setupTime();
}



void loop()
{
  displaySSD1306();

  delay(1000);
}

void displaySSD1306()
{
  String strID = checkForID();
  displayLocalTime();
  if(strID != "" && millis() - lastScanTime > 5000)
  {
    lastID = strID;
    lastScanTime = millis();
    showMessage = true;
    strTime = getLocalTime();
  }

  if(showMessage && millis() - lastScanTime < 5000)
  {
    display.println("Access Granted!");
    display.print("ID: ");
    display.println(lastID);
    display.print("Entry Time: ");
    display.println(strTime);
  }
  else
  {
    showMessage = false;
    display.setCursor(0, 8);
    display.println("Scan your card ...");
  }
  display.display();
}