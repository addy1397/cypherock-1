#include <Arduino.h>
#include "../include/sbox.h"
#include "../include/aes.h"
#include "../include/aesUtils.h"
#include "../include/constants.h"

AES::AES(small text[][4]){
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			this->text[i][j]=text[i][j];
}

void AES::fillText(small text[][4]) {
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			this->text[i][j]=text[i][j];
}

void AES::fillKey(small key[][4]){
	Serial.println("Fill Key : ");
	for(int i=0;i<8;i++)
		for(int j=0;j<4;j++){
			// cout<<"KEY : "<<i<<" "<<j<<" : ";
			// cin>>x;
			this->key[j][i]=key[j][i];
		}
	this->keyGeneration();
}


void AES::keyGeneration(){
	for(int i=8;i<56;i++)
		if(i%8==0)
		{	
			small gfunc[4];
			for(int j=0;j<4;j++)
				gfunc[(j+3)%4]=this->key[j][i-1];
			for(int j=0;j<4;j++)
				gfunc[j]=sboxEncryption[gfunc[j]];
			gfunc[0]^=(1<<((i/8)-1));
			for(int j=0;j<4;j++)
				key[j][i]=gfunc[j];
		}
		else
		{	
			for(int j=0;j<4;j++)
				key[j][i]=key[j][i-1]^key[j][i-8];
		}
}

void AES::addRoundKey(small round){
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			this->text[i][j]^=key[round*4+i][j];
}

void AES::show()
{
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			Serial.print(this->text[i][j]);
			Serial.print(" ");
		}
		Serial.println();
	}
}

void AES::encryption(){

	this->show();
	Serial.println("Starting encryption .. ");
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++){
			this->text[i][j]^=IV[i][j];
			this->text[i][j]^=key[i][j];
		}

	for(int i=1;i<=12;i++)
	{
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				this->text[i][j]=sboxEncryption[this->text[i][j]];
		this->text=(small(*)[4])shiftRowsEncrypt(this->text);
		this->text=(small(*)[4])mixColumnsEncrypt(this->text);
		this->addRoundKey(i);
	}

	for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				this->text[i][j]=sboxEncryption[this->text[i][j]];


	this->text=(small(*)[4])shiftRowsEncrypt(this->text);
	this->addRoundKey(13);
}

void AES::decryption()
{
	this->show();
	Serial.println("Starting decryption : ");

	this->addRoundKey(13);
	this->text=(small(*)[4])shiftRowsDecrypt(this->text);

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			this->text[i][j]=sboxDecryption[this->text[i][j]];

	for(int i=12;i>=1;--i)
	{
		this->addRoundKey(i);
		this->text=(small(*)[4])mixColumnsDecrypt(this->text);
		this->text=(small(*)[4])shiftRowsDecrypt(this->text);
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				this->text[i][j]=sboxDecryption[this->text[i][j]];
	}

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++){
			this->text[i][j]^=key[i][j];
			this->text[i][j]^=IV[i][j];
		}
}