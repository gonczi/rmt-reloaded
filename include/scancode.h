#ifndef _SCANCODE_CPP
# define _SCANCODE_CPP

#include "typedef.h"

extern char KTB[129];


// n�h�ny hasznos makr� a gyakram haszn�lt billety�kre
#define ESC  	KTB[0x29]
#define TAB  	KTB[0x2B]
#define CTRL 	KTB[0xE0]
#define ENTER   KTB[0x28]
#define BCKSPC  KTB[0x2A]
#define SHFT 	KTB[0xE5]
#define ALT  	KTB[0xE2]
#define SPC  	KTB[0x2C]
#define UP   	KTB[0x52]
#define DOWN 	KTB[0x51]
#define LEFT 	KTB[0x50]
#define RIGHT 	KTB[0x4F]
#define F1   	KTB[0x3A]
#define F2   	KTB[0x3B]
#define F3   	KTB[0x3C]
#define F4   	KTB[0x3D]
#define F5   	KTB[0x3E]
#define F6   	KTB[0x3F]
#define F7   	KTB[0x40]
#define F8   	KTB[0x41]
#define F9   	KTB[0x42]
#define F10   	KTB[0x43]

const char *GetKeyName(int K, char *name);
char CodeToCh(int K);	
BOOL KbHit();
int GetCh();
void InitScan();	
void DoneScan();	


#endif // _SCANCODE_CPP
