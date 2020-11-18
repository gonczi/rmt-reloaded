#include "init.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "globals.h"
#include "typedef.h"
#include "obj.h"
#include "walls.h"
#include "crash.h"
#include "cat.h"
#include "cheese.h"
#include "basket.h"
#include "flower.h"
#include "usr.h"

char *TInit::ObjFname[] = {	
	"maze/first.otb",
	"maze/second.otb", 
	NULL
};

/*****************************************************************************/
TInit::TInit( int Lev ):TObj( DINAMIC ){
	// randomize();
	Level=Lev;
	switch ( Level )	{
		case 2:
			SaveUserData();
		case 1:	{
			if ( LoadObjTable( ObjFname[ Level-1 ] ) )	{
				for ( int x=0 ; x<SIZEX ; x++ )	{
					for ( int y=0 ; y<SIZEY ; y++ )	{
						switch( ObjTable[y+x*SIZEX] )	{
							case 1:	{
								new TCat(  x , y  );
							} 	break;
							case 2:	{
								new TCheese ( x , y );
							}	break;
							case 3:	{
								new TBasket ( x , y );
							}	break;
							case 4:	{
								new TFlower ( x , y );
							}	break;
						}
					}
				}
				free( ObjTable );
			}	else 	return;
		}	break;
		default:	{
			SaveUserData();
			ExitLoop(-1);
			return;
		}
	}
	Walls=new TWalls( Level );
	new TCrash();
	Register();
}
/*****************************************************************************/
TInit::~TInit()	{
	delete Walls;
}
/*****************************************************************************/
BOOL TInit::LoadObjTable( char *iFname )	{
	if ( (ObjTable=(char *)calloc(SIZEX,SIZEY))==NULL )	{
		Perror( "LoadObjTable -> calloc" );
		return FALSE;
	}
	int F=0;
	if ( (F=open( iFname ,O_BINARY ))==-1 )	{
		_Perror("OBJTable open",ObjFname,NULL);
		return FALSE;
	};
	size_t r=0;
	if ( 	(r=read( F , ObjTable , SIZEY*SIZEX ))!= (SIZEY*SIZEX)  )	{
		char ize[40];
		itoa( r , ize , 10 );
		_Perror( ize ," OBJTable read", iFname , NULL );
		// getch();
		return FALSE;
	};
	close(F);
	return TRUE;
}
//*****************************************************************************
void TInit::SaveUserData()	{
	TUserData * UDStr=new TUserData[5];
	int F=open( USER_DAT , O_BINARY | O_RDWR );
	if ( F==-1 ) Perror( USER_DAT );
		else	{
			if ( read( F , UDStr , 5*sizeof( TUserData ) )!=(5*sizeof( TUserData )) )	{
				for ( int z=0 ; z<5 ;z++ )	{
					UDStr[z].Level=0;
					UDStr[z].Time = 0xFFFFFFFF; // MAXLONG
					strcpy( UDStr[z].Name , "*" );
				}
				lseek( F , 0L, SEEK_SET);
				if ( write( F , UDStr , 5*sizeof( TUserData ) )!=(5*sizeof( TUserData )))
					Perror( USER_DAT );
			};
			close( F );
			for ( int Usr=0; Usr<5 ; Usr++ )	{
				if (	(UDStr[Usr].Name[0]=='*') 		||
						(UDStr[Usr].Level<(Level-1))	||
						( ((UDStr[Usr].Level=(Level-1))!=0)	&&
							(UDStr[Usr].Time>TMe::UserTime)) 	)	{

					for ( int U=4 ; U>Usr ; U-- )	{
						memcpy( &(UDStr[U]) , &(UDStr[U-1]) , sizeof(TUserData) );
					}

					if ( strlen(TMe::UserName)==0 )
						strcpy( UDStr[Usr].Name , "---" );
						else	strcpy( UDStr[Usr].Name , TMe::UserName );
					UDStr[Usr].Time=TMe::UserTime;
					UDStr[Usr].Level=Level-1;

					F=open( USER_DAT , O_BINARY | O_RDWR );
					write( F , UDStr , 5*sizeof( TUserData ) );
					close( F );
					delete []UDStr;
					return;				}
			}
		}
	delete []UDStr;
};
