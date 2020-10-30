#ifndef _POTATO_CPP
	#define _POTATO_CPP
//
#include "pic_serv.cpp"
#include "grobj.cpp"
#include "timer.cpp"


class TPotato: public TGrObj 	{
	long StepD;
	BOOL Kill;
	TPicClass * PicClass;
public:
	TPotato(int , int , int , int , float);
	virtual ~TPotato();
	virtual void TimerProc();
	void Proc () ;
	void MsgProc ( void * Adr , unsigned Msg , unsigned long Lparam , unsigned long Wparam );
};

//******************************************************************************

TPotato::TPotato(	int iSx , int iSy , int iFx , int iFy , float iAlfa ):
		TGrObj( iSx , iSy , iFx , iFy  )	{
	High=0;
	Size=1.0;
	Kill=FALSE;
	StepD=0;
	Min=30;//int(Pic->X);
	Step=STEP*2;
	Register();

	Name=GR_POTATO;
	Cast=FRIEND;
	MapColor=PC_NOCOLOR;
	PicClass=*((TPicClass **)PicServer::GetPic( POTATO ));
	Pic=&(PicClass->Pic[0]);
	Alfa=iAlfa;
	for ( int Z=0 ; Z<4 ; Z++ ) StepOne();
}

//******************************************************************************

TPotato::~TPotato()	{
	PicServer::Free( POTATO );
};

//******************************************************************************

void TPotato::Proc ()	{

	if ( StepD<60 ) 	{
		High=sin((M_PI/60.0)*StepD++)*150;
		if ( !Kill ) 	{
			Kill=!StepOne();
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

void TPotato::TimerProc()	{
//	Ok=TRUE;
};

void TPotato::MsgProc ( void * , unsigned Msg ,
								unsigned long  , unsigned long Wparam )	{
	if ( (Msg==MSG_CRASH) & (!Kill) & ( Wparam != TOWp(GR_ME)) ) 	{
		Kill=TRUE;
		Cast=NOBODY;
		sound( 1000 );
		delay( 30 );
		nosound();
	}
};


//******************************************************************************
//*****************************************************************************

#endif // _POTATO_CPP
