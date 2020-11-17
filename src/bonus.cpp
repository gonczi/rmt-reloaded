#include "bonus.h"
#include "graph13.h"

//******************************************************************************
TBonus::TBonus():TObj( DINAMIC ),TTimer()	{
	Register();
	Pic=new TScrObj( 1 , TSC_BONUS );
	Pic->Poz=POINT( 160-( Pic->Pic->X/2 ), 80 );
	Pic->Show();
	Count=0;
	SetTimer( 1 , INC_COUNT , 300 );
}
//******************************************************************************
void TBonus::Proc()	{
	if ( Count<6 )	{
		if ( Count%2 )	{
			Pic->Show();
		}	else	{
				Pic->Hide();
			}
	}	else	{
			Pic->Hide();
			KillMe();
		}
};

