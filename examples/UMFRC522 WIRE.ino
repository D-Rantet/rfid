/*
Name:		UMFRC522 WIRE.ino
Created:	09/09/2017 00:36:20
Author:	DRantet
Example with TWOWIRE(I2C) interface

On RF522 I2C=1  EA = ?(see above)
https://forum.arduino.cc/index.php?topic=442750.0
arduino    RFID-RC522
Connect SDA  on SDA pin
Connect SCL  on MISO
Address:
with the RFID-RC522 board  you can :
connect pin 25,26,27,28,29 together so you get (adr5-1 = SCK pin) and we have adr0 = MOSI pin
and
EA		SCK    MOSI     adress
gnd		gnd		gnd		0x28
gnd		gnd		3v		0x29
gnd		3v		gnd		0x2E
gnd		3v		3v		0x2F
3v		gnd		gnd		0x00
3v		gnd		3v		0x01
3v		3v		gnd		0x3E
3v		3v		3v		0x3F

*/

#include <arduino.h>

#include "MFRC522.h"
#include <WIRE.h>


MFRC522 nfc1(Wire, 0x3F); //load MFRC522 "code" with 2wire interface and 0x3F as wire Address
 //MFRC522 nfc2(Wire, 0x3E); //load MFRC522 "code" with 2wire interface and 0x3E as wire Address  for any second NFC reader
 //MFRC522 nfc2(Wire, 0x01);
 //MFRC522 nfc2(Wire, 0x00);


						  // the setup function runs once when you press reset or power the board
void setup() {

	Serial.begin(115200); // To display the data on monitor
	Serial.println("hello");

	Wire.begin();  //start Wire interface
				   //Wire.begin(sdl,sda); //if wire pin may be choosen
	nfc1.PCD_Init(); //start NFC reader

	nfc1.PCD_DumpVersionToSerial(); // display MFRC522 firmware data
	Serial.println(F("Scan PICC to see UID, type, and data blocks..."));


}

// the loop function runs over and over again until power down or reset
void loop() {

	// Attente d'une carte NFC %  Wait for an NFC device
	if (!nfc1.PICC_IsNewCardPresent()) {
		return;
	}
	// Récupération du n° (uid) de la carte RFID  % uid read of the device(PICC) 
	if (!nfc1.PICC_ReadCardSerial()) {
		return;
	}

	// Lecture des informations de la carte RFID  %read of the NFC device data
	nfc1.PICC_DumpToSerial(&(nfc1.uid));



}//loop