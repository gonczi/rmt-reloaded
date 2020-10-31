/*******************************************************************************
				bonus.cpp
*******************************************************************************/
#ifndef _BONUS_CPP
	#define _BONUS_CPP
// a villogó BONUS felirat
#include "obj.cpp"
#include "scrobj.cpp"
#include "Timer.cpp"
#include "graph13.cpp"

class TBonus : TObj,public TTimer	{
	int mCount;
	BOOL TSet;
	TScrObj *Pic;
public:
	TBonus();
	~TBonus()	{
		DelTimer( 1 );
		delete Pic;
	};
	virtual void Proc();
};
//******************************************************************************
TBonus::TBonus():TObj( DINAMIC ),TTimer()	{
	Register();
	Pic=new TScrObj( 1 , TSC_BONUS );
	Pic->Poz=POINT( 160-( Pic->Pic->X/2 ), 80 );
	Pic->Show();
	Count=0;
	SetTimer( 1 , INC_COUNT , 3 );
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
#endif // class TBonus
