/*******************************************************************************
				me.cpp
*******************************************************************************/
#ifndef _TME_CPP
	#define _TME_CPP
// a j�t�kost reprezent�l� objektum defin�ci�ja
#include <math.h>
#include <time.h>
#include "globals.cpp"
#include "scancode.cpp"
#include "obj.cpp"
#include "Grobj.cpp"
#include "timer.cpp"
#include "pic_serv.cpp"
#include "ScrObj.CPP"
#include "energy.cpp"
#include "bang.cpp"
#include "bonus.cpp"
#include "Map.Cpp"
// billenyt� k�dok
typedef enum CKeyNum{ 	C_FORW , C_BACKW  , C_TLEFT ,
								C_TRIGHT , C_LEFT , C_RIGHT , C_FIRE };
// alap�rtelmez�s szerinti billenty� be�ll�t�sok a scan k�d alapj�n:
int CKey[7]={ 72 , 80 , 75 , 77 , 30 , 31 ,  29 };
#define  NMAX  10         // az orr mozg�s�nak maxim�lis �rt�ke
#include "counter.cpp"
int  K		=20;		// fordul�si sz�g   (166 MHz)
int  STEP  =50;		// l�p�s t�vols�g
long Rsize	=0;		//(SCR/10);
int  MIN=	143; 		// minim�lis falmegk�zel�t�si t�vols�g
#define MAXFLOWERS 7 // az �sszegy�jtend� vir�gok sz�ma
#include "Tomato.cpp"
#define GUN_Tomato 0  // l�ved�k t�pus t�mb azonos�t�ja
#define GUN_NUM 1     // l�ved�k t�pusok sz�ma
class TMotor;
class	TMe: TObj , TTimer ,public TPozition
{
	TMap * Map;                   // t�rk�p mutat�
	TMotor *Motor;                // motor  mutat�ja
	TScrObj * Head;               // a fej Screen obj. mutat�ja
	TScrObj * Nozi;               // az orr Screen obj. mutat�ja
	TScrObj * FlowPic;            // a vir�gok sz�m�t jelz� Screen obj.-ok mutat�ja
	TScrObj * Mission;            // a k�ldet�s teljes�t�s�t jelz� Screen obj. mutat�ja
	TCounter *Counter;            // a l�ved�k sz�m kijelz� mutat�ja
	TEnergy * Energy;             // az energia kijelz� muta�ja
	void Left()		;              // fordul balra
	void Right()	;              // fordul jobbra
	void Forward() ;              // egy l�p�s el�re
	void Backward();              // egy l�p�s h�tra
	POINT HeadPoz;                // a fej pozici�ja a k�perny�n
	int HeadTop;                  // a fej aktu�lis emel�se
	POINT NoziPoz;                // az orr pozici�ja a k�perny�n
	int NoziTop,NoziShift;        // az orr eltol�sai vizszintes ill. f�gg. ir�nyban
	BOOL Shuting;                 // l�v�s folyamatban jelz�
	long LastTime;                // a legut�bbi l�ved�k indu�sakor m�rt id�
	int Gun[ GUN_NUM ];           // a fegyverek t�pusai
	int GunNow;                   // a jelenlegi fegyver azonos�t�
	int Flowers;                  // az �sszegy�jt�tt vir�gok sz�ma
	int MissionCounter;           // sz�ml�l� a p�lya befelyez�s�t�l az j�t�k v�g�ig
	BOOL TimeSet;                 // seg�d v�ltoz� az id�z�t� megsz�ntet�s�hez
	BOOL Protection;              // v�delem a p�lya teljes�t�sekor
	int Level;                    // az aktu�lis p�lya sz�ma
	int ShutCount;                // a legut�bbi l�ved�k indu�s�t�l m�rt id�
	long Time; // :)              // a j�t�k kezdetekort m�rt id�
public:
	static char UserName[];       // a j�t�kos megadott neve
	static long UserTime;         // a j�t�kos �lltal teljes�tett id�
	int Trapp;                    //
	virtual void Proc();
	virtual void MsgProc ( void * , unsigned Msg , unsigned long, unsigned long );
	TMe( int );
	~TMe();
	virtual void TimerProc( int );
};
char TMe::UserName[30]="";
long TMe::UserTime=0;
#include "motor.cpp"
#include "menu.cpp"
//*****************************************************************************
TMe::TMe( int iLevel ):TObj( STATIC )
{
	STEP = int( 600000L / _SpeedNum );
	K = int ( _SpeedNum / 700L );
	if ( iLevel==1 )	{
		UserTime=0;
	}
	Time=time(NULL);
	TimeSet=FALSE;
	Level=iLevel;
	Head=new TScrObj( 1 , TSC_HEAD );
	Nozi=new TScrObj( 2 , TSC_NOZI );
	FlowPic=new TScrObj( 2 , TSC_FLOW );
	FlowPic->Pic->X=0;
	Energy=new TEnergy( POINT(1,1) );
	SectorX=3; SectorY=3;
	Fx=Fy=(MRECT/4.0);
	Alfa=1.1;
	Trapp=0;
	Register();
	Min= MIN;
	Name=GR_ME;
	Head->Poz.x= HeadPoz.x= (160-(Head->Pic->X/2));
	Head->Poz.y= HeadPoz.y= (200-(Head->Pic->Y));
	Head->Show();
	NoziShift=(NMAX-1);
	Nozi->Poz.x= NoziPoz.x= (160-(Nozi->Pic->X/2))  +2/* :) */ ;
	Nozi->Poz.y= NoziPoz.y= HeadPoz.y+(Nozi->Pic->Y/2);
	Nozi->Show();
	FlowPic->Poz.x=6;
	FlowPic->Poz.y=36;
	FlowPic->Show();
	Mission=NULL;
	MissionCounter=0;
	Protection=Shuting=FALSE;
	for ( int mzperx=0 ; mzperx<GUN_NUM ; mzperx++ )
		Gun[mzperx]=0;
	GunNow = GUN_Tomato;
	Flowers=0;
	ShutCount=0;
	SetTimer( 2 , CALL_PROC , 2 );
	Map=new TMap();
	Motor=new TMotor( this );
	Counter=new TCounter( TSC_POT );
};
//*****************************************************************************
TMe::~TMe()	{
	DelTimer( 2 );
	if ( TimeSet )	DelTimer( 3 );
	Head->Hide();
	Nozi->Hide();
	FlowPic->Hide();
	delete FlowPic;
	delete Head;
	delete Nozi;
	delete Energy;
	delete Counter;
	delete Motor;
	delete Map;
};
//*****************************************************************************
void TMe::TimerProc( int Id )	{
	switch ( Id )	{
		case 2:	{
			ShutCount++;
		}	break;
		case 3:	{
			if ( MissionCounter++ %2 ) Mission->Hide();
				else Mission->Show();
		}	break;
	}
}
//*****************************************************************************
void TMe::Proc()	{
	if ( MissionCounter>40 )	{
		DelTimer( 3 );
		TimeSet=FALSE;
		Mission->Hide();
		delete Mission;
		ExitLoop( Level+1 );
	}
	if ( KTB[CKey[C_TLEFT]] 	) 	{
		Left();
		if ( NoziShift < NMAX  ) NoziShift+=(( NMAX -labs(NoziShift))*0.8 );
	}
	if ( KTB[CKey[C_TRIGHT]] )	{
		Right();
		if ( NoziShift >-NMAX  ) NoziShift-=(( NMAX -labs(NoziShift))*0.8 );
	}
	if ( KTB[CKey[C_FORW]] ) Forward();
	if ( KTB[CKey[C_BACKW]] ) Backward();
	if ( KTB[CKey[C_LEFT]] ) 	{
		Alfa-=(M_PI/2.0);
		Forward();
		Alfa+=(M_PI/2.0);
	}
	if ( KTB[CKey[C_RIGHT]] )	{
		Alfa-=(M_PI/2.0);
		Backward();
		Alfa+=(M_PI/2.0);
	}
	if ( ESC 	) 	{
		DelTimer( 1 );
		TMenu *Menu=new TMenu( Level );
		delete  Menu;
		sound( 1000 );
		delay( 200 );
		nosound();
	};
	if ( TAB )	{
		Map->Show( POINT(SectorX , SectorY ), Alfa );
	}
	if ( !Shuting && KTB[CKey[C_FIRE]] && Gun[GunNow] ) {
		Shuting=TRUE;
		new TTomato( 	TMe::SectorX 	, TMe::SectorY ,
							TMe::Fx 			, TMe::Fy ,
							TMe::Alfa );
		if ( Gun[GunNow]>0 ) Gun[GunNow]--;
	}
	if ( Shuting ) {
		if ( !Gun[GunNow] )
			Counter->Hide();
			else Counter->Set( Gun[GunNow]);
	};
	if ( !KTB[CKey[C_FIRE]] || LastTime!=ShutCount )	{
		Shuting=FALSE;
		LastTime=ShutCount;
	}
	(HeadTop+=(KTB[CKey[C_FORW]] || KTB[CKey[C_BACKW]])?2:1)%=20;
	Head->Poz.y=20+HeadPoz.y+( 1.0 + sin( HeadTop*(M_PI/10.0) ))*((KTB[CKey[C_FORW]] || KTB[CKey[C_BACKW]])?6:4);
	Nozi->Poz.y=NoziPoz.y+( 1.0 + sin( ((HeadTop+17)%20) * (M_PI/10.0) ))*((KTB[CKey[C_FORW]] || KTB[CKey[C_BACKW]])?6:4);
	Nozi->Poz.x=NoziPoz.x+( NoziShift-=(NoziShift*0.2) );
};
//*****************************************************************************
void TMe::MsgProc ( void * , unsigned Msg , unsigned long Lparam , unsigned long Wparam )	{
	switch ( Msg )	{
		case MSG_EXIT:	{
			}	break;
		case MSG_BONUS:
			switch ( Wparam )	{
				case NEW_BASKET: {
					Gun[GunNow=GUN_Tomato]+=int(Lparam);
					Shuting=TRUE;
					Counter->Show( Gun[GunNow] );
					new TBonus();
				}	break;
				case NEW_FLOWER: {
					FlowPic->Pic->X=(++Flowers * 14);
					if ( Flowers==MAXFLOWERS )	{
						Mission=new TScrObj( 1 , TSC_MISSION );
						Mission->Poz=POINT( 8 , 70 );
						Mission->Show();
						MissionCounter=0;
						Protection=TimeSet=TRUE;
						SetTimer( 3 , CALL_PROC , 3 );
						UserTime=(time(NULL)-Time);
					}
				}	break;
				case NEW_CHEESE: {
					Energy->Add(int(Lparam));
					new TBonus();
				}	break;
			}	break;
		case MSG_CRASH:	{
			switch ( Wparam )	{
				case GR_CAT:	{
					if ( !Protection )	{
						new TBang();
						Energy->Add(-1);
						if ( !Energy->GetNum() ) ExitLoop( -1 );
					}
				}	break;
				default :
					break;
			}
		}
	};
};
//*****************************************************************************
void TMe::Right()
{
	Fx+=(cos(Alfa)*Rsize);
	Fy+=(sin(Alfa)*Rsize);
	if ( (Alfa+=(M_PI/ K ))>(2*M_PI)) Alfa-=(2*M_PI);
	Fx-=(cos(Alfa)*Rsize);
	Fy-=(sin(Alfa)*Rsize);
};
//*****************************************************************************
void TMe::Left()
{
	Fx+=(cos(Alfa)*Rsize);
	Fy+=(sin(Alfa)*Rsize);
	if ( (Alfa-=(M_PI/ K )) <0 ) Alfa+=(2*M_PI);
	Fx-=(cos(Alfa)*Rsize);
	Fy-=(sin(Alfa)*Rsize);
};
//*****************************************************************************
void TMe::Forward()	{
	Step=STEP;
	StepOne();
};
//*****************************************************************************
void TMe::Backward()	{
	Step=-STEP;
	StepOne();
};
//*****************************************************************************
#endif // _TME_CPP
