//******************************************************************************
//fileinsp.cpp
//******************************************************************************
#ifndef _FILEINSP_CPP
	#define _FILEINSP_CPP
// f�jl ellen�rz� elj�r�sok
#include <stdio.h>
#include <conio.h>
#include "typedef.cpp"
#include "pic_serv.cpp"
#include "bmp.cpp"
#include "init.cpp"
#include "walls.cpp"
#include "intro.cpp"
#include <time.h>
//******************************************************************************
// kirak egy karaktert az adott pozici�ra az adott sz�nnel
void put(int x,int y,char kar,char c=WHITE , char bgr=BLACK)
{
	gotoxy( x ,y );
	textcolor( c );
	textbackground( bgr );
	putch( kar );
};
//******************************************************************************
// kiir egy null�val lez�rt karakter sorozatot az adott pzici�t�l, adott sz�nekkel
void out ( int x, int y , char * str , char c=WHITE , char bgr=BLACK )	{
	int mx=wherex(),my=wherey();
	gotoxy( x ,y );
	textcolor( c );
	textbackground( bgr );
	cprintf("%s",str);
	gotoxy(mx,my);
}
//******************************************************************************
// keretet rajzol
void frame( int f , POINT Poz , RECT Size ,char frame_col) {
	char frX,frY;
	struct corners { char lu,ru,ld,rd; } corn;
	switch ( f ) {
		case 2:          // double frame
			frX = 		205;
			frY = 		186;
			corn.lu =	201;
			corn.ld =	200;
			corn.ru =	187;
			corn.rd =	188;
			break;
		default:
		case 1:          // single frame
			frX = 		196;
			frY = 		179;
			corn.lu =	218;
			corn.ld =	192;
			corn.ru =	191;
			corn.rd =	217;
			break;
	};
	char x,y,mx = Poz.x+Size.Sx-1 ,my = Poz.y+Size.Sy-1;
	for ( x = Poz.x+1 ; x< ( Poz.x+Size.Sx-1 ) ; x++ ) {
		put(x	,Poz.y	, frX , frame_col );
		put(x	,my	, frX , frame_col );
	};
	for ( y = Poz.y ; y< ( Poz.y+Size.Sy ) ; y++ )	{
		put(Poz.x	, y 	, frY , frame_col );
		put(mx 	, y 	, frY , frame_col );
	};
	put( Poz.x	,Poz.y	,corn.lu,frame_col);
	put( Poz.x	, my 	,corn.ld,frame_col);
	put( mx		,Poz.y	,corn.ru,frame_col);
	put( mx 		, my	,corn.rd,frame_col);
};
//******************************************************************************
void xLines();
void xFind( char * , int &  );
void xError( int &  );
void xOk();
//******************************************************************************
BOOL FileInspecor()	{
	clrscr();
	textcolor(WHITE);
	clrscr();
	frame( 2 , POINT( 1,2 ) , RECT( 80 , 5 ) , WHITE );
	out(  6 , 4 , "< MOUSE TRAP -- 3D Game v1.01 >" , WHITE , BLUE);
	out( 52 , 3 , "by:  Zoltan Gonczi <OWL>");
	out( 52 , 5 , "     - 2002 Hungary -   ");
	window( 1,8,80,24 );
	textbackground( BLACK );
	textcolor( WHITE );
	clrscr();
	int Errors=0;
	int f=0;
	int n=0;
	while ( TIntro::IntroFiles[n] )	{
		char Fname[80];
		xLines();
		strcpy( Fname , "> img/" );
		strcat( Fname , TIntro::IntroFiles[n] );
		strcat( Fname , BMP_FLAG );
		printf("%-50s", Fname );
		xFind( TIntro::IntroFiles[n] , Errors );
		printf("\n");
		n++;
	}
	do	{
		char Fname[80];
		switch ( Pic_Files[f].PType )	{
			case TBMP:
			case TPICTURE:	{
				xLines();
				strcpy( Fname , "> img/" );
				strcat( Fname , Pic_Files[f].FName );
				strcat( Fname , BMP_FLAG );
				printf("%-50s", Fname );
				xFind( Pic_Files[f].FName , Errors );
				printf("\n");
			}	break;
			case TPICCLASS:	{
				int fa=0;
				while ( Pic_Files[f].FNameArray[fa] )	{
					xLines();
					strcpy( Fname , "> img/\\" );
					strcat( Fname , Pic_Files[f].FNameArray[fa] );
					strcat( Fname , BMP_FLAG );
					printf("%-50s", Fname );
					xFind( Pic_Files[f].FNameArray[fa++] , Errors );
					printf("\n");
				}
			}
		};
	}	while ( Pic_Files[f++].PType!=NOTHING )	;
	f=0;
	while ( TWalls::WallFname[f] )	{
		xLines();
		printf("> %-48s", TWalls::WallFname[f] );
		int File=open( TWalls::WallFname[f++] , O_BINARY );
		if (	File==-1	)	{
			xError( Errors );
		}	else	{
				xOk();
				close( File );
			}
		printf("\n");
	};
	f=0;
	while ( TInit::ObjFname[f] )	{
		xLines();
		printf("> %-48s", TInit::ObjFname[f] );
		int File=open( TInit::ObjFname[f++] , O_BINARY );
		if (	File==-1	)	{
			xError( Errors );
		}	else	{
				xOk();
				close( File );
			}
		printf("\n");
	};
	xLines();
	printf("> %-48s", USER_DAT );
	int File=open( USER_DAT , O_BINARY );
	if (	File==-1	)	{
		xError( Errors );
		Errors--;
	}	else	{
			xOk();
			close( File );
		}
	printf("\n");
	xLines();
	printf("> %-48s %lu", " Mem test: ",coreleft() );
	if ( coreleft()>350000L )	{
		xOk;
	}	else	{
			xError( Errors );
		}
	printf("\n");
	xLines();
	printf("> %-s", " Speed test: " );
	time_t t=time(NULL);
	while ( t==time(NULL) );
	t=time(NULL);
	while ( t==time(NULL) ) 	{
		if ( (_SpeedNum++ % 2000)==0 ) putch('.');
	}

	_SpeedNum*=100;

	xLines();
	printf(" %ld ",_SpeedNum);
	xOk;
	printf("\n");
	window( 1,1,80,25 );
	if ( Errors )	{
		out ( 5 , 24 , " Sorry , ther are errors..." , WHITE+BLINK , RED );
	}	else {
			out( 5 , 24 ," Have a lot of fun...");
		}
	printf( " Press any key " );
	for ( int z=0 ; (z<200) && !kbhit() ; z++ )	{
		delay(30);
		if ( z%10==0 ) putch('.');
	}
	while ( kbhit() ) getch();
	return (!Errors)?TRUE:FALSE;
};
//******************************************************************************
void xLines()	{
	if ( wherey()>16 )	{
		int y=wherey();
		gotoxy(1,1);
		delline();
		gotoxy(1,y-1);
	}
}
//******************************************************************************
void xFind( char * fname , int &Errors  )	{
	TBmp * BitMap=new TBmp();
	if ( BitMap->Load( fname ) )	{
		xError( Errors );
	}	else	{
			xOk();
		};
	delete BitMap;
}
//******************************************************************************
void xError( int & E  )	{
	textcolor( RED+BLINK );
	cprintf("!!!  ERROR  !!!");
	textcolor( WHITE );
	E++;
	printf(" press key ");
	getch();
}
//******************************************************************************
void xOk()	{
	textcolor( GREEN );
	cprintf("      OK");
	textcolor( WHITE );
};
#endif// _FILEINSP_CPP
