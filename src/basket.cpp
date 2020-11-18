#include "basket.h"

#include "pic_serv.h"

//******************************************************************************
TBasket::TBasket(int Sx,int Sy):TGrObj(Sx,Sy, MRECT / 2, MRECT / 2, DINAMIC)	{
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
				SendMessage( (void *)Lparam , MSG_BONUS , 30L , TOWp(NEW_BASKET) );
				KillMe();
			}
			break;
	}
}

