/*
Name:		UMFRC522 SoftUART.ino
Created:	09/09/2017 00:36:20
Author:	DRantet
Example with software serial interface

On RF522 I2C=0  EA = 0
https://forum.arduino.cc/index.php?topic=442750.0

arduino    RFID-RC522
Connect Tx pin  on SDA pin(Rx)
Connect Rx pin  on MISO pin(Tx)


*/


#include <arduino.h>

#include "MFRC522.h"

#include <SoftwareSerial.h>

#define rx 3 //choose receive pin
#define tx 4  //choose transmit. pin

SoftwareSerial softUart(rx, tx, false, 64);  //create a software UART on chosen pin, bufer=64bytes
MFRC522 nfc1(&softUart); //load MFRC522 "code" with serial interface 

						 // the setup function runs once when you press reset or power the board
void setup() {
	//softUart.enableRx(rx);
	Serial.begin(115200); // To display the data on monitor 

	softUart.begin(9600); // serial to the NFC reader	

	nfc1.PCD_Init();

	Serial.println("hello");
	nfc1.PCD_DumpVersionToSerial(); // display MFRC522 firmware data
	Serial.println(F("Scan PICC to see UID, type, and data blocks..."));


}

// the loop function runs over and over again until power down or reset
void loop() {


	// Attente d'une carte NFC 
	//  Wait for an NFC device
	if (!nfc1.PICC_IsNewCardPresent()) {
		return;
	}
	// Récupération du n° (uid) de la carte RFID  
	// uid read of the device(PICC) 
	if (!nfc1.PICC_ReadCardSerial()) {
		return;
	}

	// Lecture des informations de la carte RFID
	// read of the NFC device data
	nfc1.PICC_DumpToSerial(&(nfc1.uid));



}//loop