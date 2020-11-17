#ifndef _CONSOL_CPP
	#define _CONSOL_CPP

#include "bmp.h"
#include "timer.h"

#define CHR_SIZE 17.5               // egy karakter sz�less�ge a f�jl ban
#define CUR_SIZE (int(CHR_SIZE-4))  // a kurzor sz�less�ge a k�perny�n

class TConsol : TTimer	{
	BOOL Protected , BlinkCurs , HCur , Visible;
	static char Chars[];
	TBmp *Pic;                   // a bet�k�szk�t k�pe
	POINT CurPoz;                // kurzor pozici� a k�perny�n
	int GetId( char );           // a bet� kezd� oszlopa a k�pben
	void DrawCurs();
	void ClearCurs();
	char *CurBack;               // a kurzor h�ttere
public:
	void TimerProc( int );
	TConsol();
	~TConsol();
	POINT GotoXY( POINT Poz )	{    // kurzor pozicion�l�s
		ClearCurs();
		Protected=TRUE ;
		POINT ret( CurPoz );
		CurPoz=Poz;
		Protected=FALSE ;
		return ret;
	};
	void HideCursor()	{
		HCur=TRUE;
		ClearCurs();
	};
	void ShowCursor()	{
		HCur=FALSE;
	};
	RECT OutText( const char * Str , BOOL DrawBack=FALSE );     // sz�veg kiirat�s a kurzor pozici�t�l
};

#endif // _CONSOL_CPP
