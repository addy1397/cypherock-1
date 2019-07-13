#include<Arduino.h>
#include<stdio.h>
#include"../include/share.h"
#include"../include/apdu.h"

/**************************************************************************
 *  @brief  Creates APDU to select 
 *  @param  apdu    Array to save created APDU
 *  @returns  Length of created APDU
 **************************************************************************/
uint8_t selectAppletAPDU(uint8_t *apdu){
    //00 A4 04 00 05 01 02 03 04 05 00
    apdu[0] = 0x00; apdu[1] = 0xA4; apdu[2] = 0x04; apdu[3] = 0x00; apdu[4] = 0x05; apdu[5] = 0x01;
    apdu[6] = 0x02; apdu[7] = 0x03; apdu[8] = 0x04; apdu[9] = 0x05; apdu[10] = 0x00;

    return 11;
}

/**************************************************************************
 * @brief  Creates APDU to retrieve Name from Card
 * @param  apdu    Array to save created APDU
 * @returns        Length of created APDU
 **************************************************************************/
uint8_t crtRtvNameAPDU(uint8_t *apdu){
    //uint8_t *apdu = new uint8_t[6];

    apdu[0] = 0x00; apdu[1] = INS_RETV_NAME; apdu[2] = 0x00; apdu[3] = 0x00; apdu[4] = 0x00; apdu[5] = 0x00;
    //*returnPtr = apdu;
    return 6;
}

/**************************************************************************
 * @brief  Creates APDU to recover wallet
 * @param  wallet  Information of wallet to be deleted
 * @param  apdu    Array to save created APDU
 * @returns        Length of created APDU
**************************************************************************/
uint8_t crtRcvWalletAPDU(WalletInfo &wallet, uint8_t *apdu) {
    uint8_t ofs = 5;
    apdu[0] = 0x00; apdu[1] = INS_RECV_WALLET; apdu[2] = 0x00; apdu[3] = 0x00;
    apdu[ofs++] = INS_NAME;
    apdu[ofs++] = wallet.nameLength;
    memcpy(apdu+ofs, wallet.name, wallet.nameLength);
    ofs+=wallet.nameLength;
    apdu[ofs++]=INS_PASS;
    apdu[ofs++]=passSize;
    memcpy(apdu+ofs, wallet.passDoubleHash, 32);
    ofs+=32;
    apdu[4]=ofs-5;
    
    return ofs;
}

/**************************************************************************
 * @brief  Creates APDU to delete wallet
 * @param  wallet  Information of wallet to be deleted
 * @param  apdu    Array to save created APDU
 * @returns        Length of created APDU
 **************************************************************************/
uint8_t crtDelWalletAPDU(WalletInfo &wallet, uint8_t *apdu) {
    uint8_t ofs = 0;    
    apdu[ofs++] = 0x00; apdu[ofs++] = INS_DEL_WALLET; apdu[ofs++] = 0x00; apdu[ofs++] = 0x00;
    ofs++;
    apdu[ofs++]=INS_NAME;
    apdu[ofs] = wallet.getName(apdu+ofs+1);
    ofs+=(apdu[ofs]+1);
    apdu[ofs++] = INS_PASS;
    apdu[ofs] = wallet.getPassDoubleHash(apdu+ofs+1);
    ofs+=(apdu[ofs]+1);
    apdu[4]=ofs-5;

    return ofs;
}

/**************************************************************************
 * @brief  Creates APDU to add wallet
 * @param  Packet  Packet of wallet to be added
 * @param  apdu    Array to save created APDU
 * @returns        Length of created APDU
 **************************************************************************/
uint8_t crtAddWalletAPDU(Packet &packet, uint8_t *apdu) {
    uint8_t ofs = 0;
    //uint8_t *apdu = new uint8_t[110 + (packet.info)->nameLength];

    apdu[ofs++] = 0x00; apdu[ofs++] = INS_ADD_WALLET; apdu[ofs++] = 0x00; apdu[ofs++] = 0x00;
    ofs++;
    apdu[ofs++]=INS_NAME;
    apdu[ofs] = (packet.info)->getName(apdu+ofs+1);
    ofs+=(apdu[ofs]+1);
    apdu[ofs++] = INS_PASS;
    apdu[ofs] = (packet.info)->getPassDoubleHash(apdu+ofs+1);
    ofs+=(apdu[ofs]+1);
    apdu[ofs++] = INS_xCor;
    apdu[ofs++] = packet.getxCor();
    apdu[ofs++] = INS_NO_OF_SHARES;
    apdu[ofs++] = packet.getNumberOfShares();
    apdu[ofs++] = INS_TOTAL_NO_OF_SHARES;
    apdu[ofs++] = packet.getTotalNumberofShares();
    apdu[ofs++] = INS_SHARE;
    apdu[ofs] = packet.getShare(apdu+ofs+1);
    ofs+=(apdu[ofs]+1);
    apdu[ofs++] = INS_CHECKSUM;
    apdu[ofs] = packet.getChecksum(apdu+ofs+1);
    ofs+=(apdu[ofs]+1);
    apdu[4]=ofs-5;

    //*returnPtr = apdu;
    return ofs;
}

/********************************************************************
 * @brief Extract name from byte array that is APDU and save it in object of WalletInfo
 * @param  info  Array of WalletInfo object
 * @param  apdu  Array of input APDU
 * @param  len   Length of incoming APDU
 * @returns      Number of names extracted from APDU
 ********************************************************************/
uint8_t extractNameAPDU(WalletInfo *info, uint8_t *apdu, uint8_t len)
{
    //Sample APDU
    //E003112233E0031A2B3CE003A2A2A2E003A3A3A39000
    if(len <= 2) {
        //something wrong, analyse SW
    }
    uint8_t ofs = 0, read=0;

    while(ofs < (len-2)) {
        switch(apdu[ofs++]) {
            case INS_NAME:
                info[read].setName(apdu+ofs+1, apdu[ofs]);
                ofs+=(apdu[ofs]+1);
                read++;
                break;
            default :
                //this shouldn't happen
                break;
        }
    }
    return read;
}

/********************************************************************
 * @brief Extract wallet details from byte array that is APDU and save it in object of Packet
 * @param  packet  Object of Packet Class
 * @param  apdu    Array of input APDU
 * @param  len     Length of incoming APDU
 ********************************************************************/
void extractPacketAPDU(Packet &packet, uint8_t *apdu, uint8_t len) {
    //Sample APDU
    //E201CC9000
    if(len <= 2){
        //something wrong, analyse SW
    }

    if(packet.info == NULL){
        //wrongs
    }
    
    uint8_t ofs = 0;

    while(ofs < (len-2)) {
        switch(apdu[ofs++]) {
            case INS_NAME:
                (packet.info)->setName(apdu+ofs+1, apdu[ofs]);
                ofs+=(apdu[ofs]+1);
                break;
            case INS_xCor:
                packet.setxCor(*(apdu+ofs));
                ofs++;
                break;
            case INS_NO_OF_SHARES:
                packet.setNumberOfShare(*(apdu+ofs));
                ofs++;
                break;
            case INS_TOTAL_NO_OF_SHARES:
                packet.setTotalNumberofShare(*(apdu+ofs));
                ofs++;
                break;
            case INS_SHARE:
                packet.setShare(apdu+ofs+1, apdu[ofs]);
                ofs+=(apdu[ofs]+1);
                break;
            case INS_CHECKSUM:
                packet.setChecksum(apdu+ofs+1, apdu[ofs]);
                ofs+=(apdu[ofs]+1);
                break;
            default :
                //this shouldn't happen
                break;
        }
    }
}