#include <Arduino.h>
//#include <Wire.h>
#include <Adafruit_PN532.h>
#include "../include/secure.h"
#include "../include/recover.h"

Adafruit_PN532 nfc(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);

small apdu[32], len;
small response[32], responseLength;
bool success;

WalletInfo info[4];


void setup() {

	/*Initializtion for card tap */
	/*Start Serial */
	Serial.begin(115200);
  	while(!Serial);
  	Serial.println("HELLO");

	/*beign NFC*/
	nfc.begin();

	/*get version data*/
	uint32_t versiondata = nfc.getFirmwareVersion();
  	if (! versiondata) {
    	Serial.print("Didn't find PN53x board");
    	while (1); // halt
  	}

	// Set the max number of retry attempts to read from a card
  	// This prevents us from waiting forever for a card, which is
  	// the default behaviour of the PN532.
  	nfc.setPassiveActivationRetries(0xFF);
	
	// Got ok data, print it out!
  	Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  	Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  	Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

	// configure board to read RFID tags
  	nfc.SAMConfig();


	//TODO : initialization odf libraries

	//TODO : tap a card
	//while(){
	//	
	//}

	while(1){
		if(/*wallet is alloted */1){
			small encryptedMnemonics[] = {
				1,2,3,4,5,6,7,8,9,10,
				11,12,13,14,15,16,17,18,19,20,
				21,22,23,24,25,26,27,28,29,30,
				31,32
			};
			secureWallet(encryptedMnemonics,2,4);
		}
		else{
			//TODO : options 1: recover 2: delete wallet
			if(1){
				//recover the wallet
				//TODO : Enter password
				//TODO : TAP CARDS 1 & 2 AND CHECK FOR PASSWORD CORRECTNESS
				//recovery starts here

				small numberOfMnemonics = 12;
				small xcor[]={
					1,2,3,4,5,6,7,8,9,10,11,12
				};

				small ycor[]={
					1,2,3,4,5,6,7,8,9,10,11,12
				};
				recoverShares(xcor,ycor,numberOfMnemonics);
			}
			else{
				//deletion of wallet
				//TODO : input password
				//TAP CARD 1:
				//TAP CARD 2:
				//TAP CARD 3:
				//TAP CARD 4:
			}
		}
	}
}

void loop() {
	// put your main code here, to run repeatedly:
}