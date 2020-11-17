#include "walls.h"
#include "globals.h"
#include "typedef.h"
#include "error.h"
#include "pic_serv.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// a falakat taratalmaz� k�t m�trix:
char TableH[SIZEX][SIZEY];
char TableV[SIZEX][SIZEY];

// a falakhoz tartoz� k�pek t�mbje
TBmp * *Wall[20];

#include "me.h"

//*****************************************************************************

char *TWalls::WallFname[] = { 
	"maze/first.tbl",
	"maze/second.tbl", 
	NULL
};

//*****************************************************************************
TWalls::TWalls( int Lev )	{
	Level=Lev;
	if ( !LoadLevel( TWalls::WallFname[Level-1] ) ) return;
		else Me=new TMe( Lev );
};
//*****************************************************************************
TWalls::~TWalls()	{
	for ( int Pic=0 ; Pic<(WallNum[Level-1]) ; Pic++ )	{
		PicServer::Free( WallOffset[Level-1]+Pic );
	}
	delete Me;
};
//*****************************************************************************
BOOL TWalls::LoadLevel( char *FileName )	{
	int F;
	if ( (F=open(FileName,O_BINARY ))==-1 ) {
		_Perror("Open Level",FileName,NULL);
		return FALSE;
	};
	if ( 	(read(F, TableH, SIZEY*SIZEX )!=SIZEY*SIZEX) ||
			(read(F, TableV, SIZEY*SIZEX)!=SIZEY*SIZEX)  ) {
		_Perror("Read Level",FileName,NULL);
		close(F);
		return FALSE;
	};
	close(F);
	for ( int Pic=0 ; Pic<(WallNum[Level-1]) ; Pic++ )	{
		Wall[Pic+1]=(TBmp * *)PicServer::GetPic( WallOffset[Level-1]+Pic );
	}
	return TRUE;
};
//*****************************************************************************
