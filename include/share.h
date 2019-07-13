#ifndef SHARE_H
#define SHARE_H

#include <Arduino.h>
#include <string.h>
#include "constants.h"
#include "gf256.h"
#include "utils.h"

class WalletInfo {
public:
	uint8_t name[nameSize];
    uint8_t nameLength;
    uint8_t passHash[passSize]; //hash
    uint8_t passDoubleHash[passSize]; //double hash

    void setName(uint8_t *arr, uint8_t len);
    void setPassHash(uint8_t *arr, uint8_t len);
    void setPassDoubleHash(uint8_t *arr, uint8_t len);

    uint8_t getName(uint8_t *arr);
    uint8_t getPassDoubleHash(uint8_t *arr);

// };
// 	/*functions */
// 	void setNameLength(small nameLength);
//     void setName(small name[]);
//     void setPasswordHash(small passwordHash[]);
//     void setPassDoubleHash(small passDoubleHash[]);

//     small *getName();
// 	small getNameLength();
// 	small *getPassDoubleHash();

    void display();
};


class Packet {
/*
*Class defines a wallet/packet
*@PARAM : walletName = stores the wallet Name ; size=10
*@PARAM : walletPassword = stores the wallet Password ; size=32
*@PARAM : share = stores the shamir secret scheme generated shares ; size=33 (264 bits)
*@PARAM : xcoordinate = stores the xcoordinate 
*@PARAM : numberOfShares = stores the number of shares 
*@PARAM : totalNumberOfShares = stores the total number of shares
*@PARAM : checksum = stores the checksum; size=4
*@PARAM : coefficients = stores the coefficients; size=100;
* ---- maximum of 100 shares allowed ----
*@PARAM : shamirShare = Complete wallet; size=82
*/

public:

	/*varibles */
    WalletInfo *info;
	small share[shareSize];
	small xcoordinate;
	small numberOfShares;
	small totalNumberOfShares;
	small checksum[checksumSize];
	small coefficients[100]; 
	small equation; //stores the equation filled with the coefficients


    Packet();
	

	void setxCor(uint8_t value);
    void setNumberOfShare(uint8_t value);
    void setTotalNumberofShare(uint8_t value);
    void setShare(uint8_t *arr, uint8_t len);
    void setChecksum(uint8_t *arr, uint8_t len);

    uint8_t getxCor();
    uint8_t getNumberOfShares();
    uint8_t getTotalNumberofShares();
    uint8_t getShare(uint8_t *arr);
    uint8_t getChecksum(uint8_t *arr);


	void setShare(small share[]);
	void setXcoordinate(small xcoordinate);
	void setNumberOfShares(small numberOfShares);
	void setTotalNumberOfShares(small totalNumberOfShares);
	void setChecksum(small checksum[]);
	void setCoefficients(small *coefficients);
	small getXcoordinate();
	small *getCoefficients();
	void fillCoefficients();
	void createShamirShare();
	void convertCoefficients();
	void convertToShare();
	small power(small number,small N);

    void displayPacket();
};


#endif