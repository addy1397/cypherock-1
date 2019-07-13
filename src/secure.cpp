#include <Arduino.h>
#include "../include/share.h"
#include "../include/constants.h"
#include "../include/gf256.h"

void secureWallet(small encryptedMnemonics[],small numberOfShares, small totalNumberOfShares){
    //TODO : input name, password, mnemonics, NEW/OLD
    
    /*
    * Input of 256 bits is received here
    * Sharing starts below
     */

    //Shares generated here
    Packet packet[totalNumberOfShares];
    //filling coefficients
    packet[0].fillCoefficients();
    for(small i=1;i<totalNumberOfShares;i++){
        packet[i].setCoefficients(packet[0].getCoefficients());
    }

    /*
    Comment this part in case TRNG is not done
    generates total number of random number 
    where no number is repeated
    */
    small findRepeatedRandomNumbers[256]={0};
    small count=totalNumberOfShares; //4
    findRepeatedRandomNumbers[43]=1; //termporary fix
    findRepeatedRandomNumbers[51]=1; //termporary fix
    findRepeatedRandomNumbers[84]=1; //termporary fix
    findRepeatedRandomNumbers[39]=1; //termporary fix
    //checks for randomness
    /*while(count){
        small number=randomNumberGenerator();
        if(findRepeatedRandomNumbers[number]==0){
            findRepeatedRandomNumbers[number]=1;
            count--;
        }
    }*/

    small index=0;
    for(small i=0;i<totalNumberOfShares;i++){
        while(findRepeatedRandomNumbers[index]==0){
            index++;
        }
        packet[i].setXcoordinate(index);
        packet[i].setNumberOfShares(numberOfShares);
        packet[i].setTotalNumberOfShares(totalNumberOfShares);
    }

    for(small i=0;i<totalNumberOfShares;i++){
        packet[i].convertCoefficients();
        packet[i].convertToShare();
    }

    for(small i=0;i<4;i++){
        packet[i].displayPacket();
    }
    //TODO : Shares shared
    //TODO : Display

}
