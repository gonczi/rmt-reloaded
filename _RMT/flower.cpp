//******************************************************************************
//flower.cpp
//******************************************************************************
#ifndef _FLOWER_CPP
	#define _FLOWER_CPP
// a virág objektum
#include "grobj.cpp"
#include "globals.cpp"

class TFlower: public TGrObj	{
	public:
	TFlower(int Sx,int Sy);
	virtual ~TFlower();
	void MsgProc (	void * ,
						unsigned Msg ,
						unsigned long  ,
						unsigned long  );
};
//******************************************************************************
TFlower::TFlower(int Sx,int Sy):TGrObj(Sx,Sy)	{
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
				SendMessage( (void far *)Lparam , MSG_BONUS , 1L , (long)NEW_FLOWER );
				KillMe();
			}
			break;
	}
}
#endif //_FLOWER_CPP
