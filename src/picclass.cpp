#include "picclass.h"
#include "error.h"
#include "bmp.h"

BOOL TPicClass::Draw( int Id , int x , int y )	{
	if ( (Id < Layers) && (Id>=0) )	{
		Pic[Id].Draw(x,y);
		return TRUE;
	} else 	{
			Perror( "wrong PicClass Id");
			return FALSE;
		}
}
//*****************************************************************************
TPicClass::TPicClass()	{
	Layers=0;
	Pic = NULL;
}
//*****************************************************************************
TPicClass::~TPicClass()	{
	if ( Pic )	{
		delete []Pic;
		Pic=NULL;
	};
};
//*****************************************************************************}
int TPicClass::Load( const char *Arg[], int len )	{
	if ( Pic ) return ERR_TWICE;
	Layers = len;
	Pic =new TPicture[ Layers ] ;
	for ( int Lyr=0; Lyr< Layers ; Lyr++ )
		Pic[Lyr].Load( Arg[Lyr] );
	return ERR_OK;
};
//*****************************************************************************}
int TPicClass::Load( const char *Fname )	{
	const char * *Arg = &Fname;
	return Load(Arg, 1);
};
//*****************************************************************************
// az objektum �ltal kezelt k�pek egyik�nek m�retei
BOOL TPicClass::GetRect( int Id , RECT &Rect  )	{
	if ( Id<Layers  && Id>=0 )	{
		Rect.Sx=Pic[Id].X;
		Rect.Sy=Pic[Id].Y;
		return TRUE;
	}
	return FALSE;
};

