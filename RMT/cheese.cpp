/*******************************************************************************
cheese.cpp
*******************************************************************************/
#ifndef _CHEESE_CPP
	#define _CHEESE_CPP
// a sajt objektum
#include "grobj.cpp"
#include "timer.cpp"
class TCheese: public TGrObj{
	public:
	TCheese( int Sx,int Sy );
	~TCheese();
	void MsgProc (	void * ,
						unsigned Msg ,
						unsigned long  ,
						unsigned long  );
};
//*******************************************************************************
TCheese::TCheese(int Sx,int Sy):TGrObj(Sx,Sy)	{
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
				SendMessage( (void far *)Lparam , MSG_BONUS , 10L , TOWp(NEW_CHEESE) );
				KillMe();
			}
			break;
	}
}
#endif //_CHEESE_CPP
