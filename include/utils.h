#ifndef utils_h
#define utils_h

#include<Arduino.h>


static small randomNumberGenerator(){

    //TODO : generate using TRNG
    return 31;
}

//apdu

void printResponse(uint8_t *response, uint8_t responseLength) {
   String respBuffer;

    for (int i = 0; i < responseLength; i++) {
      
      if (response[i] < 0x10) 
        respBuffer = respBuffer + "0"; //Adds leading zeros if hex value is smaller than 0x10
      
      respBuffer = respBuffer + String(response[i], HEX) + " ";                        
    }

    Serial.print("response: "); Serial.println(respBuffer);
}

#endif