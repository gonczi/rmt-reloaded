#include "cheese.h"
#include "globals.h"
#include "pic_serv.h"

//*******************************************************************************
TCheese::TCheese(int Sx,int Sy)
	:TGrObj(Sx,Sy, MRECT / 2, MRECT / 2, DINAMIC)	
{
	High=10;
	Size=1.5;
	Register();

	Name=GR_CHEESE;
	Cast=FRIEND;
	MapColor=PC_YELLOW;
	Pic=*((TPicture* *)PicServer::GetPic( CHEESE ));
}
//*******************************************************************************
TCheese::~TCheese()	{
	PicServer::Free( CHEESE );
};
//*******************************************************************************
void TCheese::MsgProc (	void * ,
								unsigned Msg ,
								unsigned long Lparam ,
								unsigned long Wparam )	{
	switch ( Msg )	{
		case MSG_CRASH:
			if ( Wparam==GR_ME )	{
				SendMessage( (void *)Lparam , MSG_BONUS , 10L , TOWp(NEW_CHEESE) );
				KillMe();
			}
			break;
	}
}
