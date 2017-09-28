/*
Name:		UMFRC522 UART.ino
Created:	09/09/2017 00:36:20
Author:	DRantet
Example with Hardware Serial interface


On RF522 I2C=0  EA = 0
https://forum.arduino.cc/index.php?topic=442750.0


		arduino    RFID-RC522
Connect Tx pin  on SDA pin(Rx)
Connect Rx pin  on MISO pin(Tx)

*/

#include <arduino.h>

#include "MFRC522.h"
#include <HardwareSerial.h>
//#include <softwareSerial.h>


MFRC522 nfc1(Serial1); //load MFRC522 "code" with serial interface 
// "Serial" can be use too, but it is usealy used for monitor debug. You will have to unplug the NFC to UPLOAD; 
// other way is using SoftwareSerial or  change the serial output pin at each time you acces to the NFC "Serial.pins(1, 3);" and restore after
	//MFRC522 nfc2(&Serial2); // serial interface for any second NFC reader
//OR MFRC522 nfc2(&SPI,53); // SPI interface and D53 as CS pin for a NFC reader on serial and one on SPI
    // 

// the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(115200); // To display the data on monitor :: Remove it if 
    //Serial.pins(1, 3); // use standart pin or change depending of your hardware

	Serial1.begin(9600); // serial to the NFC reader	

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