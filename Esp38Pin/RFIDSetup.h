#ifndef RFIDSETUP_H
#define RFIDSETUP_H

#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <LED.h>

// Define the SS (SDA) pin for SPI
#define RFID_SS_PIN 5

// SPI Driver with custom SS pin
MFRC522DriverPinSimple ss_pin(RFID_SS_PIN);
MFRC522DriverSPI driver(ss_pin);
MFRC522 mfrc522(driver);

MFRC522::MIFARE_Key key;

const uint8_t BALANCE_BLOCK = 2; // 🟨 Block where balance is stored

void initializeRFID();
void displayBalance();
float readBalance();
void addBalance(float);
void setBalance(float);

// Function to initialize the RFID reader
void initializeRFID() {
  SPI.begin(18, 19, 23);
  if (!mfrc522.PCD_Init()) 
  {
    Serial.println("ERROR: RFID initialization failed. Check wiring or power.");
    while (true); // Stop program here
  } 
  else 
  {
    Serial.println("RFID initialized successfully.");
  }

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
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

void displayBalance()
{
  Serial.printf("Your balance: %.2f\n",  readBalance());
}


void addBalance(float value) 
{
  byte block = 2;
  byte buffer[16] = {0};

  float currentBalance = readBalance();
  float total = currentBalance + value;

  memcpy(buffer, &total, sizeof(float));

  // Authenticate
  if (mfrc522.PCD_Authenticate(0x60, block, &key, &(mfrc522.uid)) != 0) {
    Serial.println("Authentication failed (addBalance).");
    return;
  }

  // Write to block
  if (mfrc522.MIFARE_Write(block, buffer, 16) != 0) {
    Serial.println("Write failed.");
  } else {
    Serial.printf("New balance: %.2f\n", total);
  }

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