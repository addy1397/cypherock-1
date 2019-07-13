#ifndef constants_h
#define constants_h

typedef uint8_t small;
typedef uint16_t large;

#define MAX_SHARES 100
#define MAX 255


//from wallet Info
#define nameSize 16 //In bytes
#define passSize 32
#define shareSize 33
#define checksumSize 4

#define PN532_SCK  (7)
#define PN532_MOSI (9)
#define PN532_SS   (10)
#define PN532_MISO (8)



static small IV[4][4]={
	{1,2,3,4},
	{5,6,7,8},
	{9,0,1,2},
	{3,4,5,6}
};


#endif