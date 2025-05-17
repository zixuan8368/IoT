#ifndef RFIDSETUP_H
#define RFIDSETUP_H

#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>

// Define the SS (SDA) pin for SPI
#define RFID_SS_PIN 5

// SPI Driver with custom SS pin
MFRC522DriverPinSimple ss_pin(RFID_SS_PIN);
MFRC522DriverSPI driver(ss_pin);
MFRC522 mfrc522(driver);

MFRC522::MIFARE_Key key;

const uint8_t BALANCE_BLOCK = 2; // 🟨 Block where balance is stored


// Function to initialize the RFID reader
void initializeRFID() {
  SPI.begin(18, 19, 23);
  if (!mfrc522.PCD_Init()) {
    Serial.println("ERROR: RFID initialization failed. Check wiring or power.");
    while (true); // Stop program here
  } 
  else {
    Serial.println("RFID initialized successfully.");
  }
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

String checkForID() {
  // Return empty if no new card is present or if card cannot be read
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return "";
  }

  // Save the UID to a string
  String uidString = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      uidString += "0";  // add leading zero for single-digit values
    }
    uidString += String(mfrc522.uid.uidByte[i], HEX);
  }
  uidString.toUpperCase();
  return uidString;
}

float readBalance() {
  byte block = 2;
  byte buffer[18];
  byte size = sizeof(buffer);

  // Authenticate
  if (mfrc522.PCD_Authenticate(0x60, block, &key, &(mfrc522.uid)) != 0) {
    Serial.println("Authentication failed (readBalance).");
    return NAN;
  }

  // Read block
  if (mfrc522.MIFARE_Read(block, buffer, &size) != 0) {
    Serial.println("Read failed.");
    return NAN;
  }

  float value;
  memcpy(&value, buffer, sizeof(float));

  return value;
}

void setBalance(float value)
{
  byte block = 2;
  byte buffer[16] = {0};

  memcpy(buffer, &value, sizeof(float));

  // Authenticate
  if (mfrc522.PCD_Authenticate(0x60, block, &key, &(mfrc522.uid)) != 0) {
    Serial.println("Authentication failed (setBalance).");
    return;
  }

  // Write to block
  if (mfrc522.MIFARE_Write(block, buffer, 16) != 0) {
    Serial.println("Write failed.");
  } else {
    Serial.printf("Set balance to RM %.2f\n", value);
  }

}

#endif