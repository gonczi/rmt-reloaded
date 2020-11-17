#ifndef _WALLS_CPP
	#define _WALLS_CPP

#include "me.h"
#include "globals.h"
#include "bmp.h"

extern char TableH[SIZEX][SIZEY];
extern char TableV[SIZEX][SIZEY];

extern TBmp * *Wall[20];

//*****************************************************************************
class TWalls	{
	int Level;
	BOOL LoadLevel( char * );
	TMe *Me;
public:
	static char *WallFname[];
	TWalls( int Lev );
	~TWalls();
};
//*****************************************************************************
#endif //_WALLS_CPP
