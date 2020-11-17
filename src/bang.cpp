#include "bang.h"

BOOL TBang::Banging=FALSE;
BOOL TBang::First=TRUE;

unsigned char TBang::RedPal[257][3];
unsigned char TBang::NormPal[257][3];
//******************************************************************************
TBang::TBang():TObj( DINAMIC ),TTimer()	{
	if ( First )	{      // csak az els� alaklommal inicializ�lja a sz�npalett�t
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
		SetTimer( 1 , CALL_PROC , 100 );
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
