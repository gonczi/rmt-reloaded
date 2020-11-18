#include "flower.h"

#include "pic_serv.h"

//******************************************************************************
TFlower::TFlower(int Sx,int Sy)
		:TGrObj(Sx, Sy, MRECT / 2, MRECT / 2, DINAMIC)	
{
	High=20;
	Size=2.0;
	Register();
	Name=GR_FLOWER;
	Cast=FRIEND;
	MapColor= PC_GREEN + PC_BLINK;
	Pic=*((TPicture **)PicServer::GetPic( FLOWER ));
}
//******************************************************************************
TFlower::~TFlower()	{
	PicServer::Free( FLOWER );
};
//******************************************************************************
void TFlower::MsgProc (	void * ,
								unsigned Msg ,
								unsigned long Lparam ,
								unsigned long Wparam	 )	{
	switch ( Msg )	{
		case MSG_CRASH:
			if ( Wparam==GR_ME )	{
				SendMessage( (void *)Lparam , MSG_BONUS , 1L , (long)NEW_FLOWER );
				KillMe();
			}
			break;
	}
}
