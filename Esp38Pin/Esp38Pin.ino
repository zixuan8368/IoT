#include <RFIDSetup.h>
#include <LED.h>

unsigned long lastCheckTime = 0;

void setup() {
    Serial.begin(115200);
    initializeRFID();
    setupLED();
}

void loop() {
    checkButtons();

    if(millis() - lastCheckTime > 1000)
    {
        if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) 
        {
            Serial.print("Card UID: ");
            MFRC522Debug::PrintUID(Serial, (mfrc522.uid));
            Serial.println();
            
            if(activeLED == -1)
                displayBalance();
            else if(activeLED == 0)
                addBalance(5.00);
            else if(activeLED == 1)
                addBalance(10.00);

            //setBalance(0.00);

            mfrc522.PICC_HaltA();
            mfrc522.PCD_StopCrypto1();
            delay(3000);
        }

        lastCheckTime = millis();
    }
}
