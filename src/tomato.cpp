#include "tomato.h"
#include "grobj.h"
#include "me.h"
#include "globals.h"

//******************************************************************************
TTomato::TTomato(	int iSx , int iSy , int iFx , int iFy , float iAlfa )
	: TGrObj( iSx , iSy , iFx , iFy, DINAMIC )	{
	High=0;
	Size=1.0;
	Kill=FALSE;
	StepD=0;
	Min=30;//int(Pic->X);
	Step=STEP*2;
	Register();
	Name=GR_TOMATO;
	Cast=FRIEND;
	MapColor=PC_NOCOLOR;
	PicClass=*((TPicClass **)PicServer::GetPic( TOMATO ));
	Pic=&(PicClass->Pic[0]);
	Alfa=iAlfa;
	for ( int Z=0 ; Z<4 ; Z++ ) StepOne();
}
//******************************************************************************
TTomato::~TTomato()	{
	PicServer::Free( TOMATO );
};
//******************************************************************************
void TTomato::Proc ()	{
	if ( StepD<60 ) 	{
		High=sin((M_PI/60.0)*StepD++)*150;
		if ( !Kill ) 	{
			Kill=BOOL(!StepOne());
		};
		if ( StepD==60 ) 	{
			KillMe();
		}
	}
	if ( Kill )	{
		Pic=&(PicClass->Pic[1]);
	}
};
//******************************************************************************
void TTomato::MsgProc ( void * , unsigned Msg ,
								unsigned long  , unsigned long Wparam )	{
	if ( (Msg==MSG_CRASH) & (!Kill) & ( Wparam != TOWp(GR_ME)) ) 	{
		Kill=TRUE;
		Cast=NOBODY;
		// sound( 1000 );
		// delay( 30 );
		// nosound();
	}
};
