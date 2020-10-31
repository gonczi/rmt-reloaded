/*******************************************************************************
				consol.cpp
*******************************************************************************/
#ifndef _CONSOL_CPP
	#define _CONSOL_CPP
// saj�t bet�k�szlet haszn�lat�val t�rt�n� sz�vekiirat�s kezel�
#include "pic_serv.cpp"
#include "timer.cpp"
#include "string.h"
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
	RECT OutText( char * Str , BOOL DrawBack );     // sz�veg kiirat�s a kurzor pozici�t�l
};
// teljes b�k�szlet:
char TConsol::Chars[]="QWERTZUIOPASDFGHJKLYXCVBNM,.-0123456789/*-+" ;
//*******************************************************************************
TConsol::TConsol()	{
	Protected=BlinkCurs=FALSE ;
	Pic=*((TBmp **)PicServer::GetPic( CHARS ));
	HCur=TRUE;
	Visible=FALSE;
	SetTimer( 1 , CALL_PROC , 2 );
	CurBack=(char *)malloc( 2 * int(CUR_SIZE-4) );
}
//*******************************************************************************
TConsol::~TConsol()	{
	free( CurBack );
	DelTimer( 1 );
	ClearCurs();
	PicServer::Free( CHARS );
}
//*******************************************************************************
int TConsol::GetId( char Chr )	{
	int ch=0;
	while ( (Chars[ch]!=0) & (Chars[ch]!=Chr) )  ch++;
	return ch;
};
//*******************************************************************************
RECT TConsol::OutText( char * Str , BOOL DrawBack=FALSE )	{
	int ch=0;
	int Sx=0;
	Str=strupr(Str);
	ClearCurs();
	Protected=TRUE ;
	while ( Str[ch] )	{
		int Offset=GetId( Str[ch] );
		for ( int x=6 ; x<18 /*int(CHR_SIZE)*/ ; x++ )	{
			for ( int y=0 ; y< Pic->Y ; y++ )	{
				register char C=Pic->Pic[ int(Offset*CHR_SIZE)+x + (y * Pic->X) ];
				if ( (C!=Pic->DeadColor) || DrawBack )
				PutPixel( CurPoz.x+x , CurPoz.y+y , C );
			}
		}
		CurPoz.x+=int(CHR_SIZE)-6;
		Sx+=int(CHR_SIZE)-6;
		ch++;
	}
	Protected=FALSE ;
	return RECT( Sx , Pic->Y );
};
//*******************************************************************************
void TConsol::TimerProc( int )	{
	if ( !Protected && !HCur )
		if ( (BlinkCurs=BOOL(!BlinkCurs))==TRUE )
			DrawCurs();
			else ClearCurs();
};
//*******************************************************************************
void TConsol::DrawCurs()	{
	if ( !HCur && !Visible)	{
		GetImage( 	CurPoz.x+2 , CurPoz.y+Pic->Y-2 ,
						CurBack , CUR_SIZE , 2 );
		Bar( 	CurPoz.x+2 , CurPoz.y+Pic->Y-2 ,
				CurPoz.x+2+CUR_SIZE , CurPoz.y+Pic->Y , 255 );
		Visible=TRUE;
	}
}
//*******************************************************************************
void TConsol::ClearCurs()	{
	if ( Visible )	{
		PutImage( 	CurPoz.x+2 , CurPoz.y+Pic->Y-2 ,
						CurBack , CUR_SIZE , 2 );
		Visible=FALSE;
	}
}
#endif // _CONSOL_CPP
