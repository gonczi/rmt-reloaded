#include "mymouse.h"

#include "graph13.h"
#include "mouse.h"
#include "globals.h"
#include "pic_serv.h"

//*****************************************************************************
TMyMouse::TMyMouse()	{
	Drawing=Visible=FALSE;
	Count = 1 ;
	CURDIR = TRUE ;
	Cur=*((TPicClass ** )PicServer::GetPic( MOUSE_CUR ));
	Cur->GetRect( 0 , CurRect );
	CurBackGr=(char *)calloc( CurRect.Sx , CurRect.Sy );
	InitMouse();
	HideMouse();
}
//*****************************************************************************
TMyMouse::~TMyMouse()	{
	PicServer::Free( MOUSE_CUR );
	free ( CurBackGr );
};
//*****************************************************************************
void TMyMouse::Draw()	{
	Mx=MouseX();
	My=MouseY();
	Clx= (CurRect.Sx+Mx)>320? 320-Mx :CurRect.Sx;
	Cly= (CurRect.Sy+My)>200? 200-My :CurRect.Sy;
	GetImage( Mx , My ,CurBackGr, Clx , Cly );
	Cur->Draw( Count ,Mx,My);
};
//*****************************************************************************
void TMyMouse::Clear()	{
	PutImage( Mx , My , CurBackGr , Clx , Cly );
};
//*****************************************************************************
void TMyMouse::TimerProc( int )	{
	if ( !Drawing )	{
		Clear();
		if ( CURDIR )	{
			if ( (++Count)>=(SHAPE-1) ) CURDIR=FALSE;
		}	else	{
				if ( (--Count)<=0 ) CURDIR=TRUE;
			};
		Draw();
	}
};
//*****************************************************************************
void TMyMouse::Show()	{
	Drawing=TRUE;
	if ( !Visible )	{
		Mx=MouseX();
		My=MouseY();
		Clx= (CurRect.Sx+Mx)>320? 320-Mx :CurRect.Sx;
		Cly= (CurRect.Sy+My)>200? 200-My :CurRect.Sy;
		GetImage( Mx , My ,CurBackGr, Clx , Cly );
		SetTimer( 1 , CALL_PROC , 100 );
		Visible=TRUE;
	}
	Drawing=FALSE;
}
//*****************************************************************************
void TMyMouse::Hide()	{
	Drawing=TRUE;
	if ( Visible )	{
		Clear();
		DelTimer( 1 );
		Visible=FALSE;
	}
	Drawing=FALSE;
}
