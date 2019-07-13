#include <Arduino.h>
#include <Adafruit_PN532.h>


small apdu[32], len;
small response[32], responseLength;
bool success;

WalletInfo info[4];

void cardTap(Adafruit_PN532 &nfc){

    Serial.println("TAP A CARD ... ");
    success = nfc.inListPassiveTarget(); //Connect with card

    if(success)
    {
        Serial.println("Card Selected");
    
        len = selectAppletAPDU(apdu);
        Serial.println("Sending APDU");
        responseLength = 255;  //Just use this before exchanging data
        
        success = nfc.inDataExchange(apdu, len, response, &responseLength); //Exchange data
        printResponse(response, responseLength); //90 00 means success

        if(success)
        {
            Serial.println("Applet Selected");

            len = crtRtvNameAPDU(apdu);
            Serial.println("Sending APDU");
            responseLength = 255;
            success = nfc.inDataExchange(apdu, len, response, &responseLength);
            if(success)
            {
                Serial.println("Wallet Name Retrieved");
                uint8_t availWallet = extractNameAPDU(info, response, responseLength);

                for(uint8_t i=0; i<availWallet; i++)
                {
                    Serial.print("Name : ");
                    for(uint8_t j=0; j<info[i].nameLength; j++)
                    {
                        Serial.print("0x");
                        Serial.print(info[i].name[j], HEX);
                        Serial.print(" ");
                    }
                    Serial.println();
                }
                uint8_t pass[] = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11};
                info[0].setPassDoubleHash(pass, sizeof(pass));

                len = crtRcvWalletAPDU(info[0], apdu);
                Serial.println("Sending APDU");
                responseLength = 255;
                success = nfc.inDataExchange(apdu, len, response, &responseLength);
                if(success)
                {
                    Serial.println("Wallet Recovered");
                    printResponse(response, responseLength);

                    len = crtDelWalletAPDU(info[0], apdu);
                    printResponse(apdu, len);
                }
                else
                {
                    Serial.println("Wallet not recovered");
                }
            }
            else
            {
                Serial.println("Could not retrieve wallet name");
            }
        }
        else
        {
            Serial.println("Applet Selection failed");
        }
    }
    else
    {
        Serial.println("Card selection failed");
    }
    delay(3000);
}