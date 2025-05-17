#include <RFIDSetup.h>
#include <UltraSonicSetup.h>
#include <DisplaySetup.h>
#include <TimeSetup.h>
#include <WiFiSetup.h>
#include <ServoSetup.h>
#include <Data.h>

unsigned long lastDisplayTime = 0;
unsigned long displayInterval = 1000;
unsigned long lastScanTime = 0;
unsigned long scanInterval = 5000;
bool showMessage = false;

String strID = "";
String strTime = "";
String lastID = "";
bool entry;
float fare = 0;
String Time = "";

void displaySSD1306();
void displayShowMessage();
void displayEntryMessage();
void displayExitMessage();
void reset();


void setup() {
  Serial.begin(115200);
  initializeDisplay();
  connectToWiFi();
  setupTime();
  initializeRFID();
  initializeUltraSonics();
  initializeServos();
}

void loop() {
  String currentID = checkForID();

  // If a new ID is detected and last scan was >5s ago
  if (currentID != "" && millis() - lastScanTime > scanInterval) {
    lastID = currentID;
    strTime = getCurrentTime();
    balance = readBalance();
    entry = isEntry(currentID);
    lastScanTime = millis();
    showMessage = true;
    
    if(entry)
    {
      addEntry(lastID, strTime);
    }
    else
    { 
      Time = getEntryTime(lastID);
      fare = removeEntry(lastID, strTime);
      setBalance(balance - fare);
    }

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();

  }
  // Update display every 1 second
  if (millis() - lastDisplayTime > displayInterval) {
    displaySSD1306();
    lastDisplayTime = millis();
  }
}

void displaySSD1306() {
  display.clearDisplay();
  display.setCursor(0, 0);
  displayLocalTime();

  if (!showMessage)
    displayShowMessage();

  if (showMessage && entry && millis() - lastScanTime < 5000) 
    displayEntryMessage();
  else if (showMessage && !entry && millis() - lastScanTime < 5000)
    displayExitMessage();
  else if (millis() - lastScanTime >= 5000) 
    reset();
  display.display();
}

void displayShowMessage()
{
  int slot1 = readUltra1();
  int slot2 = readUltra2();
  int slot3 = readUltra3();
  int availableSlots = 3 - slot1 - slot2 - slot3;

  display.println("Parking Status:");
  display.printf("Slot1: %d\n", slot1);
  display.printf("Slot2: %d\n", slot2);
  display.printf("Slot3: %d\n", slot3);
  display.printf("Available: %d/3\n", availableSlots);
  display.println("Please scan your card");
}

void displayEntryMessage()
{
  display.println("Access Granted!");
  display.printf("ID: %s\n", lastID);
  display.printf("Entry Time: %s\n", strTime);
  display.printf("Balance: RM %.2f\n", balance);
  raiseServo1();
}

void displayExitMessage()
{
  display.println("Have a nice day!");
  display.printf("Entry Time: %s\n", Time); // Save this before removeEntry
  display.printf("Exit Time: %s\n", strTime);
  display.printf("Fare: RM%.2f\n", fare);
  display.printf("New balance: RM %.2f\n", balance - fare);
  raiseServo2();
}

void reset()
{
  showMessage = false;
    lastID = "";
    strTime = "";
    fare = 0;
    lowerServo1();
    lowerServo2();
}


