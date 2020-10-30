/*******************************************************************************
					picclass.cpp
*******************************************************************************/
#ifndef _PICCLASS_CPP
	#define _PICCLASS_CPP
// a TPicClass osztály definíciója
#include "typedef.cpp"
#include "Picture.cpp"
#include "error.cpp"
class TPicClass	{
public:
	int Layers;              // képek száma az objektumban
	TPicture *Pic;           // kép tömb mutatója
	TPicClass();
	~TPicClass();
	int Load( char *Fname , ... );   // betöltés listáról
	int Load( char *Arg[] );         // betöltés string tömbbõl
	BOOL GetRect( int Id , RECT &Rect  );
	BOOL Draw( int Id , int x , int y )	{
		if ( (Id < Layers) && (Id>=0) )	{
			Pic[Id].Draw(x,y);
			return TRUE;
		} else 	{
				Perror( "wrong PicClass Id");
				return FALSE;
			}
	}
};
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
int TPicClass::Load( char *Arg[] )	{
	if ( Pic ) return ERR_TWICE;
	Layers=0;
	while ( Arg[ Layers ] ) Layers++;
	Pic =new TPicture[ Layers ] ;
	for ( int Lyr=0; Lyr< Layers ; Lyr++ )
		Pic[Lyr].Load( Arg[Lyr] );
	return ERR_OK;
};
//*****************************************************************************}
int TPicClass::Load( char *Fname , ... )	{
	char * *Arg=&Fname;
	return Load(Arg);
};
//*****************************************************************************
// az objektum által kezelt képek egyikének méretei
BOOL TPicClass::GetRect( int Id , RECT &Rect  )	{
	if ( Id<Layers  && Id>=0 )	{
		Rect.Sx=Pic[Id].X;
		Rect.Sy=Pic[Id].Y;
		return TRUE;
	}
	return FALSE;
};
#endif // _PICCLASS_CPP
