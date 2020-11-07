#include <math.h>

#include "intro.h"

// #include "graph13.cpp"
// #include "bmp.cpp"
// #include "picclass.cpp"
// #include "pic_serv.cpp"

const char *TIntro::IntroFiles[] = { 
	"intro/mandel" , 
	"intro/intro" , 
	"intro/press" ,
	"intro/o1",
	"intro/o2",
	"intro/o3",
	"intro/o4",
	"intro/o5",
	"intro/o6", 
	NULL 
};

TIntro::TIntro()	
{
// 	char *iBgr=NULL;
// 	TBmp *IntroPic=NULL;
// 	long PCount=0;
// //***************************************************     BE�SZ�S    *********
// 	TBmp * Mandel=new TBmp ;
// 	Mandel->Load( IntroFiles[0] );
// 	Mandel->Draw(0,0);
// 	delete Mandel;
// 	IntroPic=new TBmp();
// 	iBgr=(char *)calloc( 320 , 200 );
// 	if ( !iBgr )	{
// 		Perror( "Intro: calloc iBgr");
// 		delete IntroPic;
// 		return;
// 	}
// 	IntroPic->Load( IntroFiles[1] );
// 	while ( SPC );
// 	SetTimer( 1 , INC_COUNT , 1 );
// 	int High=20;
// 	GetImage( 0,0,iBgr,320,200 );
// 	for ( int v=318 ; v>1 && !SPC ; v-=5 ) 	{
// 		PCount=Count;
// 		Wait();
// 		for ( int x=0 ; x<(320-v) ; x++ )	{
// 			for ( int y=0 ; y<IntroPic->Y ; y++ )	{
// 				if ( IntroPic->Pic[ x+y*IntroPic->X ]==IntroPic->DeadColor )
// 					PutPixel(v+x,y+(200-IntroPic->Y)/2+High, iBgr[ v+x+(y+(200-IntroPic->Y)/2+High)*IntroPic->X ] );
// 					else 	PutPixel(v+x , y+(200-IntroPic->Y)/2+High , IntroPic->Pic[ x+y*IntroPic->X ]);
// 			}
// 		}
// 	}
// 	delete IntroPic;
// 	free ( iBgr );
// 	DelTimer( 1 );
// 	if ( SPC ) return;
// //**************************************************************** EGO *******
// 	char *Bgr=NULL;
// 	TPicClass *Owl=NULL;
// 	int merno=0;
// 	if ( (Owl=new TPicClass()) == NULL )	{
// 		Perror( "Intro: new TPicCLass" );
// 		return;
// 	};
// 	merno=Owl->Load( &IntroFiles[3] );
// 	if ( merno )	{
// 		Perror( "Owl Load" );
// 		delete Owl;
// 		return;
// 	}
// 	if ( (Bgr=(char *)calloc( Owl->Pic[0].X , Owl->Pic[0].Y ))==NULL )	{
// 		Perror( "Intro: calloc Bgr" );
// 		delete Owl;
// 		return;
// 	}
// 	GetImage(190,20, Bgr , Owl->Pic[0].X,Owl->Pic[0].Y);
// 	TBmp * Press=new TBmp();
// 	Press->Load( IntroFiles[2] );
// 	int PY,PX=Press->X;
// 	Press->Draw( 0 , 200-(PY=Press->Y) );
// 	delete Press;
// 	Count=1;
// 	SetTimer(1 , INC_COUNT , 1 );
// 	while ( !SPC )	{
// 		Owl->Draw( Count%6 , 190 , 20);
// 		while ( Count==PCount && !SPC );
// 		PutImage(190,20,Bgr,Owl->Pic[0].X,Owl->Pic[0].Y);
// 		PCount=Count;
// 	};
// 	DelTimer( 1 );
// 	delete Owl;   // :)
// 	free( Bgr );
// 	while( SPC );
	// Bar( 0 , 200-PY , PX , 200 , 0 );
}

