//******************************************************************************
//mymouse.cpp
//******************************************************************************
#ifndef _MYMOUSE_CPP
	#define _MYMOUSE_CPP
// saj�t tervez�s� anim�lt kurzorral rendelkez� eg�r kezel�
#include "mouse.cpp"
#include "graph13.cpp"
#include "globals.cpp"
#include "pic_serv.cpp"
#define SHAPE 3  //     a k�pek sz�ma az anim�ci�ban
class TMyMouse : TTimer	{
	BOOL Drawing;
	char *FCurName[SHAPE];     // k�p f�jlok nevei
	BOOL CURDIR,Visible ;
	TPicClass *Cur;            // a k�peket tertalmaz� obj
	int Count;                 // id�z�t� sz�ml�l�
	char *CurBackGr;           // kurzor h�ttere
	RECT CurRect;              // m�retei
	int Clx,Cly;               // a legut�bbi kurzor pozici�
	void Draw();
	void Clear();
public:
	TMyMouse();
	~TMyMouse();
	virtual void  TimerProc( int Id );
	int Mx,My;
	void Show();
	void Hide();
};
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
		SetTimer( 1 , CALL_PROC , 1 );
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
#endif // _MYMOUSE_CPP
