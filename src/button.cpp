#include "button.h"
#include "pic_serv.h"
#include "graph13.h"
#include "mouse.h"

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

//******************************************************************************
BOOL TButton::OnCoords( POINT iPoz )	{
	return ( Type!=BT_SHAPE )?(((iPoz.x>Poz.x)&&(iPoz.x<Poz.x+Rect.Sx)&& \
		(iPoz.y>Poz.y)&&(iPoz.y<Poz.y+Rect.Sy))?TRUE:FALSE):FALSE;
} ;
//******************************************************************************
TButton::TButton( BUTT_TYPE BType , POINT iPoz , ButtId Hand , int iId , BOOL iHide )
				:TShape( iPoz , iId , BType )	{
	Hideing=iHide;
	Handler=Hand;
	ActiveOn=FALSE;
};
//******************************************************************************
void	TButton::Active( BOOL Direct, BOOL Selected )	{
	if ( (Type!=BT_SHAPE ) && ((! ActiveOn) || Direct ))	{
		Hide();
		if ( MouseClick() || Selected ) Show( 2 );
			else Show( 1 );
		if ( Hideing )	Show( 0 );
		ActiveOn=TRUE;
	};
}
