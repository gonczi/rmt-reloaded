/*******************************************************************************
				map.cpp
*******************************************************************************/
#ifndef _MAP_CPP
	#define _MAP_CPP
// a térkép megjelenítõje
#include "globals.cpp"
#include "timer.cpp"
#include "pic_serv.cpp"
#include "graph13.cpp"
#include "grobj.cpp"
#include "me.cpp"
class TMap : TTimer	{
	RECT Rect;                       // a térkép mérete
	POINT Poz;                       // poziciója a képernyõn
	void PutSign( POINT Poz , BYTE Color ); // kirak egy pontot a szektor közepébe
public:
	TMap();
	void Show( POINT MPoz , float MAlfa ); // kirajzolja a térképet
} ;
//******************************************************************************
TMap::TMap()	{
	Poz.x=52 ;
	Poz.y=0 ;
	Rect.Sx= SIZEX*4-3;
	Rect.Sy= SIZEY*4-4;
};
//******************************************************************************
void TMap::Show( POINT MPoz , float MAlfa )	{
	SetTimer( 1 , INC_COUNT , 2 );
	ColoredBarLines( Poz , Rect , 0 );

	for ( int Wx=0 ; Wx<SIZEX ; Wx++ )	{
		for ( int Wy=0 ; Wy<SIZEY ; Wy++ )	{
			if ( TableV[Wx][Wy] )	{                 // vízszintes vpnalkák
				Straight( Poz.x+Wx*4 , Poz.y+Wy*4 , Poz.x+Wx*4 , Poz.y+Wy*4+5 , 255 );
			}
			if ( TableH[Wx][Wy] )	{                 // függõleges vonalkák
				Straight( Poz.x+Wx*4 , Poz.y+Wy*4 , Poz.x+Wx*4+5 , Poz.y+Wy*4 , 255 );
			}
		}
	}
	TGrObjList *Puff = GrObjList;
	while( Puff )	{                                // objektumok
		if ( Puff->GrObj->MapColor!=char(PC_NOCOLOR) )
			PutSign( POINT(Puff->GrObj->SectorX,Puff->GrObj->SectorY) ,
						Puff->GrObj->MapColor );
		Puff=Puff->Next;
	}
	PutSign( MPoz , PC_BLUE );                      // ...
	MPoz=POINT( Poz.x+MPoz.x*4+2 , Poz.y+MPoz.y*4+2 );

	TBmp *Jelek=*((TBmp **)PicServer::GetPic( MPIC_JELEK )); // jelmagyarázat
	Jelek->Draw( 320-Jelek->X , 60 );
	PicServer::Free( MPIC_JELEK );

	TBmp *Nyil=*((TBmp **)PicServer::GetPic( MPIC_NYIL ));
	TPicClass *Point=*((TPicClass **)PicServer::GetPic( MPIC_POINT ));
	char *PBack=(char *)calloc( Point->Pic[0].X , Point->Pic[0].Y );
	GetImage( MPoz.x-(Point->Pic[0].X/2) , MPoz.y-(Point->Pic[0].Y/2) , PBack ,  Point->Pic[0].X , Point->Pic[0].Y );
/***/
	while ( TAB );
	int n=-20;
	while	(	((n+=15) < int((180.0/M_PI)*(2.5*M_PI-MAlfa))) && !TAB )  // nyil befordul
		Nyil->RDPaint( Nyil->X/2+2 , MAXY-Nyil->Y/2-2 , n  );
	Nyil->RDPaint( Nyil->X/2+2 , MAXY-Nyil->Y/2-2 , (180.0/M_PI)*(2.5*M_PI-MAlfa)  );
	int PCount=Count=0;
	while ( !TAB && !ESC )	{
		if ( PCount!=Count )	{
			PutImage( MPoz.x-(Point->Pic[0].X/2) , MPoz.y-(Point->Pic[0].Y/2) , PBack ,  Point->Pic[0].X , Point->Pic[0].Y );
			Point->Draw( Count%4 , MPoz.x-(Point->Pic[0].X/2) , MPoz.y-(Point->Pic[0].Y/2));
			PCount=Count;
		}
		Puff = GrObjList;
		while( Puff && !TAB && !ESC )	{                           // villogás
			if ( (Puff->GrObj->MapColor!=char(PC_NOCOLOR)) && (Puff->GrObj->MapColor<char(PC_BLINK)) )
				PutSign( POINT(Puff->GrObj->SectorX,Puff->GrObj->SectorY) ,
					(Count%2)?Puff->GrObj->MapColor:0 );
			Puff=Puff->Next;
		}
	};
	free ( PBack );
	PicServer::Free( MPIC_POINT );
	PicServer::Free( MPIC_NYIL );
	while ( TAB || ESC );
	DelTimer( 1 );
}
//******************************************************************************
void TMap::PutSign( POINT iPoz , BYTE Color )	{
	PutPixel( Poz.x+iPoz.x*4+2 , Poz.y+iPoz.y*4+2 , Color );
	PutPixel( Poz.x+iPoz.x*4+2 , Poz.y+iPoz.y*4+3 , Color );
	PutPixel( Poz.x+iPoz.x*4+3 , Poz.y+iPoz.y*4+3 , Color );
	PutPixel( Poz.x+iPoz.x*4+3 , Poz.y+iPoz.y*4+2 , Color );
};
#endif // _MAP_CPP
