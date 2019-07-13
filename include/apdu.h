#ifndef APDU_H
#define APDU_H

#include<Arduino.h>
#include"share.h"

/**************** MACROS *******************/
#define INS_ADD_WALLET 0xC1
#define INS_CHOOSE_WALLET 0x0C
#define INS_DEL_WALLET 0xC3
#define INS_RECV_WALLET 0xC2
#define INS_RETV_NAME 0xC4

#define INS_NAME 0xE0
#define INS_PASS 0xE1
#define INS_xCor 0xE2 //TODO : Macros to be added
#define INS_NO_OF_SHARES 0xE3
#define INS_TOTAL_NO_OF_SHARES 0xE4
#define INS_SHARE 0XE5
#define INS_CHECKSUM 0XE6

#define OFFSET_CLA 0
#define OFFSET_INS 1
#define OFFSET_P1 2
#define OFFSET_P2 3
#define OFFSET_LC 4
#define OFFSET_CDATA 5
/*******************************************/

/********* FUNCTIONS TO CREATE APDU **********/
uint8_t selectAppletAPDU(uint8_t *apdu);
uint8_t crtRtvNameAPDU(uint8_t *apdu);
uint8_t crtRcvWalletAPDU(WalletInfo &wallet, uint8_t *apdu);
uint8_t crtAddWalletAPDU(Packet &packet, uint8_t *apdu);
uint8_t crtDelWalletAPDU(WalletInfo &wallet, uint8_t *apdu);


/******** FUNCTIONS TO EXTRACT FROM APDU AND SAVE IN RESPECTIVE CLASS *******/
uint8_t extractNameAPDU(WalletInfo *info, uint8_t *apdu, uint8_t len);
void extractPacketAPDU(Packet &packet, uint8_t *apdu, uint8_t len);

#endif