/******************************************************************************
												scancode.cpp
******************************************************************************/

#ifndef _SCANCODE_CPP
	#define _SCANCODE_CPP
// a billentyüzet új kezelõjét definiáló program blokk
#include "typedef.cpp"
#include "error.cpp"

#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define INTR 0x09             // a bill megszakítás kódja

#ifdef __cplusplus            // c vagy c++ esetén más az interrupt argumentum
	 #define __CPPARGS ...
#else
	 #define __CPPARGS
#endif

//****************GLOBAL :
BOOL _ScanOn=FALSE;          // globális jelzõ bájt, hogy a bill. kezelõ be lett
									  // kapcsolva

// néhány hasznos makró a gyakram használt billetyükre
#define ESC  	KTB[ 1]
#define TAB  	KTB[15]
#define CTRL 	KTB[29]
#define ENTER  KTB[28]
#define BCKSPC KTB[14]
#define SHFT 	KTB[54]
#define ALT  	KTB[56]
#define SPC  	KTB[57]
#define UP   	KTB[72]
#define DOWN 	KTB[80]
#define LEFT 	KTB[75]
#define RIGHT 	KTB[77]
#define PLUS   KTB[78]
#define MINUS  KTB[74]
#define F1   	KTB[59]
#define F2   	KTB[60]
#define F3   	KTB[61]
#define F4   	KTB[62]
#define F5   	KTB[63]
#define F6   	KTB[64]
#define F7   	KTB[65]
#define F8   	KTB[66]
#define F9   	KTB[67]
#define F10   	KTB[68]

// egy scan-kódhoz tartozó név string alakban
class KSTRN	{
public:
	int Key;
	char *Name;
	KSTRN(char*,int);
};
// konstruktor:
KSTRN::KSTRN( char *iName , int iKey )	{
	Key=iKey;
	Name=iName;
}
// scan-kódok neveinek adat táblája
KSTRN KeyNameStr[]={
	KSTRN( "LEFT"  , 75 ),
	KSTRN( "RIGHT" , 77 ),
	KSTRN( "UP"    , 72 ),
	KSTRN( "DOWN"  , 80 ),
	KSTRN( "CTRL"  , 29 ),
	KSTRN( "ALT"   , 56 ),
	KSTRN( "ENTER" , 28 ),
	KSTRN( "CAPS LOCK" , 58 ),
	KSTRN( "R SHIFT" , 54 ),
	KSTRN( "INSERT" , 82  ),
	KSTRN( "HOME" , 71  ),
	KSTRN( "PG UP" , 73  ),
	KSTRN( "PG DOWN" , 81  ),
	KSTRN( "END" , 79  ),
	KSTRN( "DELETE" , 83 ),
	KSTRN( "ESC" , 1 ),
	KSTRN( "SPACE" , 57 ),
	KSTRN( "TAB" , 15 ),
	KSTRN( "BACK SPC" , 14 ),
	KSTRN( "/" , 53 ),
	KSTRN( "*" , 55 ),
	KSTRN( "-" , 74 ),
	KSTRN( "+" , 78 ),
	KSTRN( "." , 83 ),
	KSTRN( "NUM LOCK" , 69 ),
	KSTRN( "SCRL LOCK" , 70 ),
	KSTRN( "" , 0 )
};
// a keresést egyszerüsítõ segédtábla:
char KeyNameChr[]= "QWERTZUIOP....ASDFGHJKL..0..YXCVBNM,.-.";
// hasznos függvény egy scan-kód nevének meghatározására
char *GetKeyName( int K , char *name )	{
	int z=0;
	while ( KeyNameStr[z].Key ) 	{         // keresés a string táblázatban
		if ( KeyNameStr[z].Key == K )	{
			return KeyNameStr[z].Name;
		}
		z++;
	}
	char num[6];                            // keresés a karakter táblázatban
	if ( (K>=16) && (K<=(16+strlen(KeyNameChr))) )	{
		name[0]=KeyNameChr[K-16];            // 16 == Q bill. scan kódja
		name[1]=0;                           // ami a tömb elsõ eleme
		return name;
	}
	if ( (K>=2) && (K<=10) )	{       // ha a scan-kód egy számjegyhez tartozik
		name[0]='1'+(K-2);
		name[1]=0;
		return name;
	}
		if ( (K>=59) && (K<=68) )	{    // a scan kód funkcióû billentyû
		strcpy(name,"FIX");
		itoa ( K-58 , num , 10 );
		strcat( name , num );
		return name;
	}
	strcpy( name , "CODE ");           // a kód nem ismert, return "CODE XY"
	itoa( K , num ,10 );
	strcat( name , num );
	return name;
}

char CodeToCh( int K )	{             // ha a kerestt kód biztosan egy karakter
	char name=0;                       // akkor ez a függvény is elegendõ
	if ( (K>=16) && (K<=(16+strlen(KeyNameChr))) )	{
		name=KeyNameChr[K-16];          // jellemzõen zöveg beolvasáshoz szükséges
	}                                  // függvény
	if ( (K>=2) && (K<=10) )	{
		name='1'+(K-2);
	}
	if ( K==57 )	{                   // és ismeri a ' ' karaktert is
		name=' ';
	}
	return name;
}

static char KTB[129];                 // a GLOBÁLIS SCAN kód tömb  !!!
void interrupt ( *oldhandler)(__CPPARGS);  // az eredeti megszakítási vektor
														 // mutatója
void interrupt KEYIRQ(__CPPARGS)           // az új megszakítás kódja:
{
asm {
		  PUSH DS
		  PUSH AX
		  PUSH BX
		  PUSH CX
		  MOV  AX,SEG KTB
		  MOV  DS,AX
		  XOR  BH,BH
		  MOV  CL,BH
		  IN   AL,0x60
		  MOV  BL,AL
		  AND  BL,0x7F
		  SHL  AL,0x01
		  CMC
		  ADC  CL,0x00
		  MOV  [BX+OFFSET KTB],CL
		  IN   AL,0x61
		  MOV  AH,AL
		  OR   AL,0x80
		  OUT  0x61,AL
		  MOV  AL,AH
		  NOP
		  NOP
		  NOP
		  OUT  0x61,AL
		  CLI
		  MOV  AL,0x20
		  OUT  0x20,AL
		  STI
		  POP CX
		  POP BX
		  POP AX
		  POP DS
// 	     IRET             //  <- nem kell mert interrupt tárolási osztályba
									 //			tartozik a függvény
	};
}

BOOL KbHit()	{    			 // primitív figyelõ függvény bill. lenyomásra
	for ( int blk=0 ; blk<(128/sizeof( long )) ; blk++)	{
		if ( *(long *)&KTB[ blk*sizeof( long ) ] ) return TRUE;
	}
	return FALSE;
}

/* hasonló az elõzõhöz csak a CTRL bill.-t nem
	veszi figyelemze és a lenyomott bill. scan
	kódjával tér vissza */
int GetCh()	{
	for ( int key=0; key<128 ; (key==41)?(key+=2):(key++) )	{
		if ( KTB[key] )	{
			return( key );
		}
	}
	return 0 ;
}

void InitScan()	{         // lecseréli az eredeti megszakítást az újra
	if ( !_ScanOn )	{
		oldhandler = getvect(INTR);
		setvect(INTR, KEYIRQ);
		_ScanOn=TRUE;
	}
};

void DoneScan()	{         // vissza állítja az eredeti állapotot
	if ( _ScanOn )	{
		setvect(INTR, oldhandler);
		_ScanOn=FALSE;
	}
};


#endif // _SCANCODE_CPP
