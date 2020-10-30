//******************************************************************************
// basket.cpp
//******************************************************************************
#ifndef _BASKET_CPP
	#define _BASKET_CPP
// a kosár objektum
#include "grobj.cpp"
#include "globals.cpp"

class TBasket: public TGrObj	{
	public:
	TBasket(int Sx,int Sy);
	virtual ~TBasket();
	void MsgProc (	void * ,
						unsigned Msg ,
						unsigned long  ,
						unsigned long  );
};
//******************************************************************************
TBasket::TBasket(int Sx,int Sy):TGrObj(Sx,Sy)	{
	High=20;
	Size=2.0;
	Register();

	Name=GR_BASKET;
	Cast=FRIEND;
	MapColor=PC_RED;
	Pic=*((TPicture **)PicServer::GetPic( BASKET ));
}
//******************************************************************************
TBasket::~TBasket()	{
	PicServer::Free( BASKET );
};
//******************************************************************************
void TBasket::MsgProc (	void * ,
								unsigned Msg ,
								unsigned long Lparam ,
								unsigned long Wparam )	{
	switch ( Msg )	{
		case MSG_CRASH:
			if ( Wparam==GR_ME ){
				SendMessage( (void far *)Lparam , MSG_BONUS , 30L , TOWp(NEW_BASKET) );
				KillMe();
			}
			break;
	}
}
#endif //_CHEESE_CPP
