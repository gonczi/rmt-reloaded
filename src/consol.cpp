#include "consol.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "graph13.h"
#include "pic_serv.h"

char* strupr(char* s)
{
	char* p = s;
	while(*p) {
		*p = toupper((int)*p);
		p++;
	}
	return s;
}

// teljes b�k�szlet:
char TConsol::Chars[]="QWERTZUIOPASDFGHJKLYXCVBNM,.-0123456789/*-+" ;
//*******************************************************************************
TConsol::TConsol()	{
	Protected=BlinkCurs=FALSE ;
	Pic=*((TBmp **)PicServer::GetPic( CHARS ));
	HCur=TRUE;
	Visible=FALSE;
	SetTimer( 1 , CALL_PROC , 200 );
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
RECT TConsol::OutText( const char * _Str , BOOL DrawBack )	{
	int ch=0;
	int Sx=0;
	char *Str = (char*)malloc(strlen(_Str) + 1);
	strcpy(Str, _Str);
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
	free(Str);
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
