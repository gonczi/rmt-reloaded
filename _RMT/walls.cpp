/******************************************************************************
				walls.cpp
******************************************************************************/
#ifndef _WALLS_CPP
	#define _WALLS_CPP
// a TWalls oszt�ly defin�ci�ja
#include "globals.cpp"
#include "typedef.cpp"
#include "error.cpp"
#include "Pic_serv.cpp"
#include <io.h>
#include <fcntl.h>
// a falakat taratalmaz� k�t m�trix:
static char TableH[SIZEX][SIZEY] , TableV[SIZEX][SIZEY];
// a falakhoz tartoz� k�pek t�mbje
static TBmp * *Wall[20];
#include "me.cpp"
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
char *TWalls::WallFname[]={ "bin\\first.tbl" ,"bin\\second.tbl" , NULL };
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
#endif //_WALLS_CPP
