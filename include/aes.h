#ifndef aes_h
#define aes_h

/* 
MODE : CBC 

Key Size : 256bits 

For more Implementation Details, read PDF : 
https://engineering.purdue.edu/kak/compsec/NewLectures/Lecture8.
*/

#include <Arduino.h>
#include "constants.h"


class AES{
	small (*text)[4]=new small[4][4];
	int size();
	small key[4][56];
public:
	AES(small text[][4]);
	void fillText(small text[][4]);
	void fillKey(small key[][4]);
	void keyGeneration();
	void addRoundKey(small round);
	void encryption();
	void decryption();
	void show();
};

void *shiftRowsEncrypt(small stateArray[][4]);
void *shiftRowsDecrypt(small stateArray[][4]);


#endif