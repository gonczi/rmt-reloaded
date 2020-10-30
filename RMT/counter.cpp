/******************************************************************************
	counter.cpp
*******************************************************************************/
#ifndef _COUNTER_CPP
	#define _COUNTER_CPP
// l�ved�k sz�ml�l� kijelz�je
#include "number.cpp"
#include "timer.cpp"
#include "scrobj.cpp"
class TCounter	:TTimer 	{
	int MNum;                            // a kijelz�n megjelen� sz�m
	BOOL Visible;
	int Step;                            // h�tt�r k�p be�sz�si temp�ja
	TNumber * Num_100;                   // sz�mjegyek ...
	TNumber * Num_10;
	TNumber * Num_1;
	TScrObj * BackPic;                   // h�tt�r k�p
public:
	TCounter( int iId );
	~TCounter();
	void Show( int );
	void Hide();
	void Set( int Num );                  // friss�t�s
	virtual void TimerProc( int );
};
//******************************************************************************
TCounter::TCounter( int iId )	{
	Num_100=new TNumber( 0 , 257 , 0 );
	Num_10=new TNumber( 0 , 277 , 0 );
	Num_1=new TNumber( 0 , 297 , 0 );
	BackPic=new TScrObj( 40 , iId );
	Step=0;
	BackPic->Poz = POINT ( 319,0 );      // h�tt�r k�p pozici�ja a k�perny�n
	BackPic->Show();
	Visible=FALSE;
	SetTimer( 1 , CALL_PROC, 1 );
};
//******************************************************************************
TCounter::~TCounter()	{
	BackPic->Hide();
	Hide();
	delete Num_100;
	delete Num_10;
	delete Num_1;
	delete BackPic;
	DelTimer( 1 );
};
//******************************************************************************
void TCounter::Show( int Num )	{
	if ( !Visible  )	{
		Set( Num );
		Step=-10;
		Visible=TRUE;
	}
}
//******************************************************************************
void TCounter::Hide()	{
	if ( Visible )	{
		Step=10;
		Visible=FALSE;
	}
}
//******************************************************************************
void TCounter::Set( int Num )	{
	MNum=Num;
	if ( Num>=100 )
		Num_100->Set( Num/100) ;
		else Num_100->Hide();
	if ( Num>=10 )
		Num_10->Set(  Num/10 );
		else Num_10->Hide();
	if ( Num )
		Num_1->Set( Num );
		else Num_1->Hide();
}
//******************************************************************************
void TCounter::TimerProc( int )	{
	if ( Step>0 )	{
		if (BackPic->Poz.x<320)
			BackPic->Poz.x += Step;
			else	{
				Num_100->Hide();
				Num_10->Hide();
				Num_1->Hide();
				Step=0;
			};
	 }
	 if ( Step<0 )	{
		if (BackPic->Poz.x>240)
			BackPic->Poz.x += Step;
			else	{
				Set( MNum );
				Step=0;
			}
	 }
}
#endif // _COUNTER_CPP
