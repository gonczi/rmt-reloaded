/******************************************************************************
cat.cpp
//*****************************************************************************/
#ifndef	_CAT_CPP
	#define _CAT_CPP
// a macska objektum
#include "grobj.cpp"
#include "Timer.cpp"
#include "PicClass.cpp"
#include "Pic_serv.cpp"
class TCat: public TGrObj,public TTimer{
	int Stop,Silly;
	TPicClass * *PicClass;
	int PCount;
public:
	TCat( int Sx,int Sy );
	~TCat();
	void MsgProc (	void * ,
						unsigned Msg ,
						unsigned long  ,
						unsigned long  );
	virtual void TimerProc( int Id );
	virtual void Proc ()  ;
};
//******************************************************************************
TCat::TCat(int Sx,int Sy):TGrObj(Sx,Sy),TTimer()	{
	Alfa = M_PI/(random(180)+1);
	High=43;
	Size=2.0;
	Register();
	Min=170;
	Step = int( 450000L / _SpeedNum );
	Name=GR_CAT;
	Cast=NME;
	MapColor=PC_ORANGE;
	Silly=Stop=FALSE;
	PicClass=(TPicClass **)PicServer::GetPic( CAT );
	Pic = &((*PicClass)->Pic[0]) ;
	PCount=1;
	SetTimer( 1, CALL_PROC , 2 );
	SetTimer( 2, CALL_PROC , 10 );    // stop, silly
}
//******************************************************************************
TCat::~TCat()	{
	DelTimer( 1 );
	PicServer::Free( CAT );
};
//******************************************************************************
void TCat::MsgProc (	void * ,
							unsigned Msg ,
							unsigned long Lparam ,
							unsigned long Wparam )	{
	switch ( Msg )	{
		case MSG_CRASH:
			switch ( GR_NAME(Wparam) )	{
				case GR_TOMATO:
					Silly=Stop=4;
					break;
				case GR_ME:
					if ( !Silly )
						SendMessage( (void *)Lparam   , MSG_CRASH , TOLp(this) , TOWp(Name) );
					Stop=2;
					break;
			}	break;
		case MSG_EXIT:
			DelTimer( 1 );
			DelTimer( 2 );
		break;
	}
}
//******************************************************************************
void TCat::TimerProc( int Id )	{
	switch ( Id )	{
		 case 1: ++PCount ;
			break;
		 case 2:
			Stop-=!(!Stop);
			if ( Silly ) Silly--;
			break;
	}
};
//******************************************************************************
void TCat::Proc()	{
	if ( Beta!=0.0 && !Stop )	{
		Alfa=Beta+M_PI;
		StepOne();
	};
	if ( Beta==0.0 && !Stop )	{
		float W;
		if ( !StepOne( W ) ) {
			int next=random(160)-80;
			Alfa = norm(W+(M_PI/(next?next:1)));
		}
	}
	if ( Silly )	{
		Pic=&((*PicClass)->Pic[3+PCount%2]);
	}	else Pic= &((*PicClass)->Pic[((PCount%4)==3)?1:PCount%4]);
};
#endif //_CAT_CPP
