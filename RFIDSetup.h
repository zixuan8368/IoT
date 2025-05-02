#ifndef RFIDSETUP_H
#define RFIDSETUP_H

#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>
#include <DisplaySetup.h>

// Define the SS (SDA) pin for SPI
#define RFID_SS_PIN 5

// SPI Driver with custom SS pin
MFRC522DriverPinSimple ss_pin(RFID_SS_PIN);
MFRC522DriverSPI driver(ss_pin);
MFRC522 mfrc522(driver);


// Function to initialize the RFID reader
void initializeRFID() {
  SPI.begin(18, 19, 23);
  mfrc522.PCD_Init();  
  Serial.println(F("Scan your RFID card here......"));
}

String checkForID(){
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if (!mfrc522.PICC_IsNewCardPresent()) {
		return "";
	}

	// Select one of the cards.
	if (!mfrc522.PICC_ReadCardSerial()) {
		return "";
	}

  // Save the UID on a String variable
  String uidString = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      uidString += "0"; 
    }
    uidString += String(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println(uidString);
  return uidString;
}



#endif