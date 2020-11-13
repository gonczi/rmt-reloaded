#include "scancode.h"
#include "error.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Using SDL and standard IO
#include <SDL.h>

#include <thread>
#include <unistd.h>

using namespace std;

char KTB[129] = {0};                 // a GLOB�LIS SCAN k�d t�mb  !!!

bool scancodeTaskRun = true;
thread *scancodeTaskThread = NULL;

// egy scan-k�dhoz tartoz� n�v string alakban
class KSTRN	{
public:
	int Key;
	const char *Name;
	KSTRN(const char*,int);
};
// konstruktor:
KSTRN::KSTRN( const char *iName , int iKey )	{
	Key=iKey;
	Name=iName;
}
// scan-k�dok neveinek adat t�bl�ja
KSTRN KeyNameStr[]={
	KSTRN( "LEFT"  , 	0x50 ),
	KSTRN( "RIGHT" , 	0x4F ),
	KSTRN( "UP"    , 	0x52 ),
	KSTRN( "DOWN"  , 	0x51 ),
	KSTRN( "CTRL"  , 	0xE0 ), // R-CRTL: 0xE4 
	KSTRN( "ALT"   , 	0xE2 ), // R-ALT: 0xE6 
	KSTRN( "ENTER" , 	0x28 ),
	KSTRN( "R SHIFT" , 	0xE5 ),
	KSTRN( "INSERT" , 	0x49 ),
	KSTRN( "HOME" , 	0x4A ),
	KSTRN( "PG UP" , 	0x4B ),
	KSTRN( "PG DOWN" , 	0x4E ),
	KSTRN( "END" , 		0x4D ),
	KSTRN( "DELETE" , 	0x4C ),
	KSTRN( "ESC" , 		0x29 ),
	KSTRN( "SPACE" , 	0x2C ),
	KSTRN( "TAB" , 		0x2B ),
	KSTRN( "BACK SPC" , 0x2A ),
	KSTRN( "," , 		0x36 ),
	KSTRN( "." , 		0x37 ),
	KSTRN( "-" , 		0x38 ),
	KSTRN( "" , 0 )
};

// a keres�st egyszer�s�t� seg�dt�bla:
// char KeyNameChr[]= "QWERTZUIOP....ASDFGHJKL..0..YXCVBNM,.-.";

// hasznos f�ggv�ny egy scan-k�d nev�nek meghat�roz�s�ra
const char *GetKeyName( int K , char *name )	
{
	int z=0;
	while ( KeyNameStr[z].Key ) 	{         // keres�s a string t�bl�zatban
		if ( KeyNameStr[z].Key == K )	{
			return KeyNameStr[z].Name;
		}
		z++;
	}
	
	// char num[6];                            // keres�s a karakter t�bl�zatban
	// if ( (K>=16) && (K<=(16+strlen(KeyNameChr))) )	{
	// 	name[0]=KeyNameChr[K-16];            // 16 == Q bill. scan k�dja
	// 	name[1]=0;                           // ami a t�mb els� eleme
	// 	return name;
	// }

	// if ( (K>=2) && (K<=10) )	{       // ha a scan-k�d egy sz�mjegyhez tartozik
	// 	name[0]='1'+(K-2);
	// 	name[1]=0;
	// 	return name;
	// }
	
	// if ( (K>=59) && (K<=68) )	{    // a scan k�d funkci�� billenty�
	// 	sprintf(name, "FIX%d", K-58);
	// 	return name;
	// }

	sprintf(name, "CODE %d", K);
	return name;
}

char CodeToCh( int K )	
{             // ha a kerestt k�d biztosan egy karakter
	char name=0;                       // akkor ez a f�ggv�ny is elegend�
// 	if ( (K>=16) && (K<=(16+strlen(KeyNameChr))) )	{
// 		name=KeyNameChr[K-16];          // jellemz�en z�veg beolvas�shoz sz�ks�ges
// 	}                                  // f�ggv�ny
// 	if ( (K>=2) && (K<=10) )	{
// 		name='1'+(K-2);
// 	}
// 	if ( K==57 )	{                   // �s ismeri a ' ' karaktert is
// 		name=' ';
// 	}
	return name;
}

BOOL KbHit()	
{    			 // primit�v figyel� f�ggv�ny bill. lenyom�sra
	for ( int blk=0 ; blk<(128/sizeof( long )) ; blk++)	{
		if ( *(long *)&KTB[ blk*sizeof( long ) ] ) return TRUE;
	}
	return FALSE;
}

/* hasonl� az el�z�h�z csak a CTRL bill.-t nem
	veszi figyelemze �s a lenyomott bill. scan
	k�dj�val t�r vissza */
int GetCh()	
{
	for ( int key=0; key<128 ; (key==41)?(key+=2):(key++) )	{
		if ( KTB[key] )	{
			return( key );
		}
	}
	return 0 ;
}

void updateKTB( SDL_KeyboardEvent *key )
{
	/* Is it a release or a press? */
	KTB[key->keysym.scancode & 0x7F] = !(key->type == SDL_KEYUP);

	printf("KTB[%d]: %s\n", key->keysym.scancode, SDL_GetKeyName(key->keysym.sym));

	// Uint16 mod =  key->keysym.mod;
	// printf( "Modifers: " );
	// /* If there are none then say so and return */
	// if( mod == KMOD_NONE ){
	// 	printf( "None\n" );
	// 	return;
	// }

	// if( mod & KMOD_NUM ) printf( "NUMLOCK " );
	// if( mod & KMOD_CAPS ) printf( "CAPSLOCK " );
	// if( mod & KMOD_LCTRL ) printf( "LCTRL " );
	// if( mod & KMOD_RCTRL ) printf( "RCTRL " );
	// if( mod & KMOD_RSHIFT ) printf( "RSHIFT " );
	// if( mod & KMOD_LSHIFT ) printf( "LSHIFT " );
	// if( mod & KMOD_RALT ) printf( "RALT " );
	// if( mod & KMOD_LALT ) printf( "LALT " );
	// if( mod & KMOD_CTRL ) printf( "CTRL " );
	// if( mod & KMOD_SHIFT ) printf( "SHIFT " );
	// if( mod & KMOD_ALT ) printf( "ALT " );
	// printf( "\n" );
}

void scancodeTask(string msg)
{
	SDL_Event event;        /* Initialise SDL */

	// printf("scancodeTask - START %d\n", scancodeTaskRun);
	/* Poll for events */
	while( scancodeTaskRun && SDL_WaitEvent( &event ) ){
		
		switch( event.type ) {
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				updateKTB( &event.key );
				break;

			/* SDL_QUIT event (window close) */
			case SDL_QUIT:
				printf("SDL_QUIT\n");
				exit(0);
				break;

			default:
				break;
		}

	}
	// printf("scancodeTask - STOP\n");
}

void InitScan()	
{
	scancodeTaskThread = new thread(scancodeTask, "");
};

void DoneScan()	
{
	scancodeTaskRun = FALSE;
	scancodeTaskThread->join();
};
