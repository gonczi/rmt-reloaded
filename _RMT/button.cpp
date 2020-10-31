/*******************************************************************************
				button.cpp
*******************************************************************************/
#ifndef _BUTTON_CPP
	#define _BUTTON_CPP
// grafikus gomb megjelenítõje
#include "pic_serv.cpp"
// gomb típus:
typedef enum BUTT_TYPE{ BT_BUTTON , BT_SHAPE };

class TShape	{           // egy kép a képernyõn
protected:
	int Id;                 // azonosító
	POINT Poz;              // pozició a képernyõn
	RECT Rect;              // méretei
	char *BackGr;           // háttér
	TPicClass *Pic;         // a hozzá tartozó kép
public:
	BUTT_TYPE Type;         // típus
	BOOL ActiveOn;          // TRUE ha a fókusz az objektumon van
	TShape( POINT , int , BUTT_TYPE );
	~TShape(){ Free(); };
	void Show( int iLayer );
	void Hide();
	void Load();            // kép betöltése
	void Free();
};
//******************************************************************************
void TShape::Load()	{
	if ( !Pic ) 	{
		Pic=*((TPicClass * *)PicServer::GetPic( Id ));
	}
	Pic->GetRect( (Type!=BT_SHAPE)*2 , Rect );
	Rect+=RECT( 1 ,1 );
	if ( !BackGr )	{
		BackGr=(char *)malloc( Rect.Sx * Rect.Sy );
		GetImage( Poz.x , Poz.y , BackGr , Rect.Sx , Rect.Sy );
	};
};
//******************************************************************************
void TShape::Free()	{
	Hide();
	if ( Pic ) PicServer::Free( Id );
	Pic=NULL;
};
//******************************************************************************
TShape::TShape( POINT iPoz  , int iId , BUTT_TYPE iType)	{
	Type=iType;
	Poz=iPoz;
	Pic=NULL;
	Id=iId;
	BackGr=NULL;
};
//******************************************************************************
void	TShape::Show( int iLayer )	{
	Load();
	if ( iLayer < Pic->Layers )	{
		Pic->Draw( iLayer , Poz.x+(iLayer==2) , Poz.y+(iLayer==2) );
		ActiveOn=FALSE;
	}
}
//******************************************************************************
void	TShape::Hide()	{
	if ( BackGr )	{
		PutImage( Poz.x , Poz.y , BackGr , Rect.Sx , Rect.Sy );
		free(BackGr);
		BackGr=NULL;
	}
	ActiveOn=FALSE;
}
//******************************************************************************
//******************************************************************************

class TButton : public TShape	{   // gomb
	BOOL Hideing;
public:
	ButtId Handler;                // azonosító
	TButton( BUTT_TYPE , POINT , ButtId , int  , BOOL );
	void Active( BOOL , BOOL );    // a gombra helyezi a fókuszt grafikusan
	BOOL OnCoords( POINT iPoz );   // megállapítja hogy az adott koordináta a gomb területén van e
};
//******************************************************************************
BOOL TButton::OnCoords( POINT iPoz )	{
	return ( Type!=BT_SHAPE )?(((iPoz.x>Poz.x)&&(iPoz.x<Poz.x+Rect.Sx)&& \
		(iPoz.y>Poz.y)&&(iPoz.y<Poz.y+Rect.Sy))?TRUE:FALSE):FALSE;
} ;
//******************************************************************************
TButton::TButton( BUTT_TYPE BType , POINT iPoz , ButtId Hand , int iId , BOOL iHide=TRUE )
				:TShape( iPoz , iId , BType )	{
	Hideing=iHide;
	Handler=Hand;
	ActiveOn=FALSE;
};
//******************************************************************************
void	TButton::Active( BOOL Direct=FALSE , BOOL Selected=FALSE  )	{
	if ( (Type!=BT_SHAPE ) && ((! ActiveOn) || Direct ))	{
		Hide();
		if ( MouseClick() || Selected ) Show( 2 );
			else Show( 1 );
		if ( Hideing )	Show( 0 );
		ActiveOn=TRUE;
	};
}
#endif // _BUTTON_CPP
