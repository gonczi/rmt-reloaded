
#include "pic_serv.cpp"
#include "graph13.cpp"
#include "mouse.cpp"
#include <stdio.h>
#include <conio.h>

void main ()	{
	Init13();
	InitMainPal();
	ShowMouse();

	TBmp * Pic=*(TBmp **)PicServer::GetPic( MPIC_NYIL );

	PutPixel( 160 , 100 , 255 );
	POINT O( 160 , -100 );

	while ( !kbhit () )	{
		Pic->RDPaint( 160 , 100 , (180.0/M_PI)*( O%POINT(MouseX(),-MouseY()) +M_PI/2)  );
		Pic->RDPaint( 30 , 140 , (180.0/M_PI)*( POINT(30,-140)%POINT(MouseX(),-MouseY()) +M_PI/2)  );
		Pic->RDPaint( 260 , 30 , (180.0/M_PI)*( POINT(260,-30)%POINT(MouseX(),-MouseY()) +M_PI/2)  );
		Pic->RDPaint( 240 , 160 , (180.0/M_PI)*( POINT(240,-160)%POINT(MouseX(),-MouseY()) +M_PI/2)  );
		gotoxy( 1,1 );
		printf("%4d%4d",MouseX(),MouseY());
		gotoxy( 1,2 );
		printf("%4f" , O%POINT(MouseX(),-MouseY()) );
		gotoxy( 1,3 );
		printf("%4f" , O/POINT(MouseX(),-MouseY()) );
	}

	Done13();
}
