#include <stdio.h>
#include <time.h>
#include <cstring>

#include "typedef.h"

// #include "pic_serv.cpp"
#include "bmp.h"
// #include "init.cpp"
// #include "walls.cpp"
#include "intro.h"

// void xLines();
void xFind(const char * fname , int &Errors);	
void xError(int &E);
void xOk();

BOOL FileInspecor()	
{
	printf("╔════════════════════════════════════════════════════════════╗\n");
	printf("║         < MOUSE TRAP (reloaded) -- 3D Game v1.02 >         ║\n");
	printf("║                  by:  Zoltan Gonczi <OWL>                  ║\n");
	printf("║                      - 2002 Hungary -                      ║\n");
	printf("╚════════════════════════════════════════════════════════════╝\n");
	int Errors = 0;
	int f = 0;
	int n = 0;
	while (TIntro::IntroFiles[n]) {
		char Fname[80];
		strcpy(Fname, "> img/");
		strcat(Fname, TIntro::IntroFiles[n]);
		strcat(Fname, BMP_FLAG);
		printf("%-50s", Fname );
		xFind(TIntro::IntroFiles[n] , Errors);
		printf("\n");
		n++;
	}

	// do	{
	// 	char Fname[80];
	// 	switch ( Pic_Files[f].PType )	{
	// 		case TBMP:
	// 		case TPICTURE:	{
	// 			xLines();
	// 			strcpy( Fname , "> pictures\\" );
	// 			strcat( Fname , Pic_Files[f].FName );
	// 			strcat( Fname , BMP_FLAG );
	// 			printf("%-50s", Fname );
	// 			xFind( Pic_Files[f].FName , Errors );
	// 			printf("\n");
	// 		}	break;
	// 		case TPICCLASS:	{
	// 			int fa=0;
	// 			while ( Pic_Files[f].FNameArray[fa] )	{
	// 				xLines();
	// 				strcpy( Fname , "> pictures\\" );
	// 				strcat( Fname , Pic_Files[f].FNameArray[fa] );
	// 				strcat( Fname , BMP_FLAG );
	// 				printf("%-50s", Fname );
	// 				xFind( Pic_Files[f].FNameArray[fa++] , Errors );
	// 				printf("\n");
	// 			}
	// 		}
	// 	};
	// }	while ( Pic_Files[f++].PType!=NOTHING )	;
	// f=0;
	// while ( TWalls::WallFname[f] )	{
	// 	xLines();
	// 	printf("> %-48s", TWalls::WallFname[f] );
	// 	int File=open( TWalls::WallFname[f++] , O_BINARY );
	// 	if (	File==-1	)	{
	// 		xError( Errors );
	// 	}	else	{
	// 			xOk();
	// 			close( File );
	// 		}
	// 	printf("\n");
	// };
	// f=0;
	// while ( TInit::ObjFname[f] )	{
	// 	xLines();
	// 	printf("> %-48s", TInit::ObjFname[f] );
	// 	int File=open( TInit::ObjFname[f++] , O_BINARY );
	// 	if (	File==-1	)	{
	// 		xError( Errors );
	// 	}	else	{
	// 			xOk();
	// 			close( File );
	// 		}
	// 	printf("\n");
	// };
	// xLines();
	// printf("> %-48s", USER_DAT );
	// int File=open( USER_DAT , O_BINARY );
	// if (	File==-1	)	{
	// 	xError( Errors );
	// 	Errors--;
	// }	else	{
	// 		xOk();
	// 		close( File );
	// 	}
	// printf("\n");
	// xLines();
	// printf("> %-48s %lu", " Mem test: ",coreleft() );
	// if ( coreleft()>350000L )	{
	// 	xOk;
	// }	else	{
	// 		xError( Errors );
	// 	}
	// printf("\n");
	// xLines();
	// printf("> %-s", " Speed test: " );
	// time_t t=time(NULL);
	// while ( t==time(NULL) );
	// t=time(NULL);
	// while ( t==time(NULL) ) 	{
	// 	if ( (_SpeedNum++ % 2000)==0 ) putch('.');
	// }

	// _SpeedNum*=100;

	// xLines();
	// printf(" %ld ",_SpeedNum);
	// xOk;
	// printf("\n");
	// window( 1,1,80,25 );
	// if ( Errors )	{
	// 	out ( 5 , 24 , " Sorry , ther are errors..." , WHITE+BLINK , RED );
	// }	else {
	// 		out( 5 , 24 ," Have a lot of fun...");
	// 	}
	// printf( " Press any key " );
	// for ( int z=0 ; (z<200) && !kbhit() ; z++ )	{
	// 	delay(30);
	// 	if ( z%10==0 ) putch('.');
	// }
	// while ( kbhit() ) getch();
	
	return (!Errors) ? TRUE : FALSE;
};

void xFind(const char * fname , int &Errors)	
{
	TBmp *BitMap = new TBmp();
	
	if (BitMap->Load(fname)) {
		xError(Errors);
	} else {
		xOk();
	};
	delete BitMap;
}

void xError(int &E)	
{
	printf("!!!  ERROR  !!!");
	E++;
}

void xOk()
{
	printf("      OK");
};
