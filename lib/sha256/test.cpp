#include "sha256.h"
#include "sha256.cpp"
#include <iostream>
#include <string.h>

using namespace std;

int * to_uint_8(string str){
  int * ascii = new int[str.length()+1];
  for(uint8_t i =0; i<str.length(); i++){
    ascii[i] = (int)str[i];
  }
  return ascii;
}

int main()
{
    string walletPassword="Hello";
    uint8_t *hash1 = new uint8_t[SHA256_BLOCK_SIZE];
    uint8_t *hash2=to_uint_8(walletPassword);
    SHA256_CTX ctx; //Calculating hash
    sha256_init(&ctx);
    sha256_update(&ctx, to_uint_8(walletPassword), 34);
    sha256_final(&ctx, hash1);

    for(int i=0; i<SHA256_BLOCK_SIZE; i++)
    {
        cout<<hash2[i];
    }
    cout<<endl;
    for(int i=0; i<SHA256_BLOCK_SIZE; i++)
    {
        cout<<hash1[i];
    }
}
