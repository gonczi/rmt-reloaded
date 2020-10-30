/*******************************************************************************
				bang.cpp
*******************************************************************************/
#ifndef _BANG_CPP
	#define _BANG_CPP
// a jelzõ villogás végrehajtója
#include "obj.cpp"
#include "Timer.cpp"
#include "graph13.cpp"
class TBang : TObj,TTimer	{
	static BOOL Banging;             // ha TRUE, akkor egy villogás folyamatban van már
	static BOOL First;               // az elsõ objektumig TRUE
	static unsigned char RedPal[257][3],NormPal[257][3];   // két színpaletta: vörös,normál
	int mCount;                      // idõzítõ számlálója
	BOOL TSet;                       // ha villogás van folyamatban megszünéskor
		// akkor vissza kell állítani az eredeti színpalettát, ezt jelzi ez
public:
	TBang();
	virtual void TimerProc( int Id );
	virtual~TBang()	{
		SetPaletteRegistersNoWait(0,256,&NormPal);
		if ( TSet )DelTimer( 1 );
		Banging=FALSE;
	};
};
BOOL TBang::Banging=FALSE;
BOOL TBang::First=TRUE;
unsigned char TBang::RedPal[257][3];
unsigned char TBang::NormPal[257][3];
//******************************************************************************
TBang::TBang():TObj( DINAMIC ),TTimer()	{
	if ( First )	{      // csak az elsõ alaklommal inicializálja a színpalettát
		for ( int C=0 ; C<256 ; C++ )	{ // :)
			RedPal[C][0]=(((C%32)/4)*8);
			RedPal[C][1] = RedPal[C][2] = (BYTE)0;
		};
		GetPaletteRegisters(0,256,&NormPal);
		First=FALSE;
	}
	Register();
	TSet=FALSE;
	if ( !Banging )	{
		mCount=0;
		TSet=TRUE;
		Banging=TRUE;
		SetTimer( 1 , CALL_PROC , 1 );
	}	else	KillMe();
}
//******************************************************************************
void TBang::TimerProc( int )	{
	if ( (mCount++)<6 )	{
		if ( mCount%2 )	{
			SetPaletteRegistersNoWait(0,256,&RedPal);
		}	else	{
				SetPaletteRegistersNoWait(0,256,&NormPal);
			}
	}	else	{
			SetPaletteRegistersNoWait(0,256,&NormPal);
			KillMe();
		}
};
#endif//_BANG_CPP
