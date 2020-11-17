#include "rmt_menu.h"

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "typedef.h"
#include "globals.h"
#include "timer.h"
#include "obj.h"
#include "bmp.h"
#include "pic_serv.h"
#include "scancode.h"
#include "mymouse.h"
#include "mouse.h"
#include "consol.h"
#include "usr.h"
#include "timer.h"
#include "button.h"
#include "me.h"
#include "graph13.h"

// a statikusan l�trehozott TButton p�ld�nyok
TButton Butt_Top5( BT_BUTTON , POINT( 40, 30) , ID_TOP5  	, MBUTT_TOP5 );
TButton Butt_New( BT_BUTTON , POINT( 40, 85) , ID_NEW  	, MBUTT_NEW );
TButton Butt_Con( BT_BUTTON , POINT( 40, 115) , ID_CON  	, MBUTT_CON );
TButton Butt_Exi( BT_BUTTON , POINT( 40,145) , ID_EXI  	, MBUTT_EXI );
TButton Butt_Yes( BT_BUTTON , POINT( 40,100) , ID_YES  	, MBUTT_YES );
TButton Butt_No ( BT_BUTTON , POINT(140,100) , ID_NO   	, MBUTT_NO );
TButton Butt_Ays( BT_SHAPE , POINT (70,70) , ID_NULL     , MPIC_AYS );
TButton Butt_Forw( BT_BUTTON , POINT( 40,25) , ID_FORW  	, MBUTT_FORW  , FALSE);
TButton Butt_Back( BT_BUTTON , POINT( 40,45) , ID_BACK  	, MBUTT_BACK  , FALSE);
TButton Butt_TLeft( BT_BUTTON , POINT( 40, 65) , ID_TLEFT  , MBUTT_TLEFT  , FALSE );
TButton Butt_TRight( BT_BUTTON , POINT( 40,85), ID_TRIGHT 	, MBUTT_TRIGHT , FALSE);
TButton Butt_Left( BT_BUTTON , POINT( 40, 105) , ID_LEFT  	, MBUTT_LEFT  , FALSE );
TButton Butt_Right( BT_BUTTON , POINT( 40,125), ID_RIGHT 	, MBUTT_RIGHT , FALSE);
TButton Butt_Fire( BT_BUTTON , POINT( 40,145) , ID_FIRE 	, MBUTT_FIRE  , FALSE);
TButton Butt_LevMap( BT_SHAPE , POINT( 40 , 173 )   , ID_NULL     , MPIC_LEVMAP );
TButton Butt_Ent( BT_SHAPE , POINT( 50 , 80)   , ID_NULL     , MPIC_ENT );
TButton Butt_Start( BT_BUTTON , POINT( 110,145) , ID_START  	, MBUTT_START );
TButton Butt_BackM( BT_BUTTON , POINT( 230,145) , ID_BACKM   , MBUTT_BACKM );
// a me� elemeinek csoportos�t�sa k�perny�nk�nt
TButton *Main_Menu[]={  &Butt_New 	, &Butt_Con 	, &Butt_Exi , &Butt_Top5 , NULL };
TButton *Cont_Menu[]={ 	&Butt_Forw 	, &Butt_Back 	, &Butt_TLeft	, &Butt_TRight ,
								&Butt_Left 	, &Butt_Right	,&Butt_Fire , &Butt_LevMap , &Butt_BackM  , NULL };
TButton *Exit_Menu[]={	&Butt_Yes 	, &Butt_No 	  	, &Butt_Ays , NULL };
TButton *Name_Menu[]={	&Butt_Start , &Butt_BackM 	, &Butt_Ent , NULL };
TButton *Top5_Menu[]={	&Butt_BackM , NULL };
// me� azonos�t� sz�mok

// az �sszes ismert k�perny� elem lista �sszefoglal�sa:
TButton * * ButtonList[]={ Main_Menu , Cont_Menu , Exit_Menu , Name_Menu ,
								Top5_Menu ,	NULL };
//-----------------------------------------------------------------------------

char TMenu::Text[256] = {0};
char TMenu::DrawText[256] = {0};          // sz�veg puffer
//*****************************************************************************

TMenu::TMenu( int iPLevel )		
{
	strcpy(Text, " On this map, you have to collect 7 flowers to complete the level. Good luck.      - press key -     ");

	SetTimer( 1 , INC_COUNT , 100 );
	PLevel=iPLevel;
	switch( PLevel )	{                       // a sz�ks�ges mem�ria el� �ll�t�sa:
		case 1:	{
			PicServer::FreeDirect( W_KOTEG );
			PicServer::FreeDirect( W_KOTEG2 );
			PicServer::FreeDirect( W_KO );
			PicServer::FreeDirect( W_KO2 );
			PicServer::FreeDirect( W_TEGLA );
			PicServer::FreeDirect( W_TEGLA2 );
		}	break;
		case 2:	{
			PicServer::FreeDirect( W2_KO );
			PicServer::FreeDirect( W2_KO2 );
			PicServer::FreeDirect( W2_TREE );
			PicServer::FreeDirect( W2_TREE2 );
		} break;
	};

	while ( ESC ) usleep(1000);
	
	MyMouse=new TMyMouse();
	Con=new TConsol();
	TB2=TextBack=NULL;
	TextLineMove=FALSE;
	ActiveLine=0;
	Buttons=NULL;
	MCLICKON=BOOL(MouseClick());
	MenuExit=FALSE;
	while ( ESC ) usleep(1000);
	DarkScr();
	ChangeMode( MT_MAIN );
	MyMouse->Show();
	int Mx=MouseX(),My=MouseY();
//-----------------Menu Loop
	while ( !MenuExit )	{
		
		usleep(100);

//-- billenty� kezel�s:
		if ( KbHit() )	{
			if ( TAB ||(MenuMode!=MT_CONTROL && DOWN) )	{
				MyMouse->Hide();
				do	{
					if ( ActiveButton )	{
						ActiveButton->Hide();
						ActiveButton->Show(0);
						register TButton * *Puff=Buttons;
						while ( (*Puff) )	{
							if ( (*Puff)==ActiveButton )	{
								if ( (*++Puff) )	{
									ActiveButton=(*Puff);
								}	else	{
										ActiveButton=(* Buttons);
									}
							}
							Puff++;
						}
					}	else	ActiveButton=(* Buttons);
				}	while ( ActiveButton->Type== BT_SHAPE );
				ActiveButton->Active();
				MyMouse->Show();
				if ( MenuMode==MT_CONTROL )	{
					if ( ActiveButton->Handler!=ID_BACKM )	{
						ActiveLine=ActiveButton->Handler-ID_FORW;
						Con->GotoXY( POINT (140+CurRect[ActiveLine].Sx , 25+ActiveLine*20 ));
					}
				};
				while ( TAB || DOWN ) usleep(1000);
			}	else	{
				if ( UP && (MenuMode!=MT_CONTROL) )	{
					MyMouse->Hide();
					do	{
						if ( ActiveButton )	{
							ActiveButton->Hide();
							ActiveButton->Show(0);
						};
						register TButton * *Puff=Buttons;
						if ( (*Puff)==ActiveButton ) while (*Puff) Puff++;
							else	while ( (*++Puff)!=ActiveButton );
						ActiveButton= *(--Puff);
					}	while ( ActiveButton->Type== BT_SHAPE );
					ActiveButton->Active();
					MyMouse->Show();
					while( UP ) {
						if ( TextLineMove ) {
							MoveLine();
						}
						usleep(1000);
					}
				}	else	{
					if ( ENTER || ((MenuMode!=MT_CONTROL) && SPC ) )	{
						if ( ActiveButton )	{
							MyMouse->Hide();
							ActiveButton->Active( TRUE , TRUE );
							MyMouse->Show();
							while ( ENTER || SPC ) {
								if ( TextLineMove ) {
									MoveLine();
								}
								usleep(1000);
							}
							MyMouse->Hide();
							ActiveButton->Active( TRUE , FALSE );
							MyMouse->Show();
							Event( ActiveButton->Handler );
						}
					}	else	{
						if ( ESC )	{
							switch ( MenuMode )	{
								case MT_EXIT:	{
									Event( ID_NO );
								}	break;
								case MT_TOP5:
								case MT_NAME:
								case MT_CONTROL:	{
									Event( ID_BACKM );
								}	break;
								case MT_MAIN:	{
									if ( !PLevel ) Event( ID_EXI );
										else MenuExit=TRUE;
								}	break;
							};
							while ( ESC ) {
								if ( TextLineMove ) MoveLine();
								usleep(1000);
							}
						}	else	{
							switch ( MenuMode )	{
								case MT_CONTROL:	{
									MyMouse->Hide();
									CKey[ActiveLine]=GetCh();
									PutImage( 140 , 25 , TextBack , 110 , 140 );
									for ( int n=0 ; n<7 ; n++ )	{
										Con->GotoXY( POINT(140 , 25+20*n) );
										char name[20];
										CurRect[n]=( Con->OutText( GetKeyName( CKey[n] , name ) ) );
									}
									Con->GotoXY( POINT (140+CurRect[ActiveLine].Sx , 25+ActiveLine*20 ));
									MyMouse->Show();
									while ( KbHit() ) usleep(1000);
								}	break;
								case MT_NAME:	{
									char Ch;
									if ( (Ch=CodeToCh( GetCh() ))!=0 )	{
										if ( strlen(TMe::UserName)<17 )	{
											char hCh[2]={ Ch , 0 };
											strcat( TMe::UserName , hCh );
											MyMouse->Hide();
											Bar ( 50 , 120 , 280 , 140 , 0 );
											Con->HideCursor();
											Con->GotoXY( POINT (50 , 120) );
											Con->OutText( TMe::UserName );
											MyMouse->Show();
										};
									}	else	{
											int Nl=0;
											if ( BCKSPC && ((Nl=strlen( TMe::UserName ))>0)  )	{
												TMe::UserName[Nl-1]=0;
												MyMouse->Hide();
												Bar ( 50 , 120 , 280 , 140 , 0 );
												Con->HideCursor();
												Con->GotoXY( POINT (50 , 120) );
												Con->OutText( TMe::UserName );
												MyMouse->Show();
											}
										}
									while( KbHit() ) {
										if ( TextLineMove ) MoveLine();
										usleep(1000);
									}
								}	break;
							}
						}
					}
				}
			}
		}
//-- eg�r kezel�s:
		POINT MPoz( Mx=MouseX() , My=MouseY() );
		if ( Mx!=MouseX() || My!=MouseY() )	{
			register TButton * *Puff=Buttons;
			while ( (*Puff) )	{
				if ( (*Puff)->OnCoords( MPoz ) )	{
					if ( ActiveButton )	{
						if (  ActiveButton!=(*Puff) )	{
							MyMouse->Hide();
							ActiveButton->Hide();
							ActiveButton->Show(0);
							(*Puff)->Active();
							ActiveButton=(*Puff);
							MyMouse->Show();
						}
						break;
					}	else	{
							MyMouse->Hide();
							(*Puff)->Active();
							MyMouse->Show();
							ActiveButton=(*Puff);
							break;
						}
				};
				Puff++;
			}
			if ( TextLineMove ) MoveLine();
		}
		if ( TextLineMove ) MoveLine();
		//-----------------eg�r gomb lenyomva
		if ( MouseClick() &&  !MCLICKON )	{
			MCLICKON=TRUE;
			if ( ActiveButton )	{
				if ( ActiveButton->OnCoords( MPoz ) )	{
					MyMouse->Hide();
					ActiveButton->Hide();
					ActiveButton->Active();
					MyMouse->Show();
				}
			}
		}
		//-----------------eg�r gomb felengedve
		if ( !MouseClick() &&  MCLICKON )	{
			MCLICKON=FALSE;
			if ( ActiveButton )	{
				MyMouse->Hide();
				ActiveButton->Hide();
				ActiveButton->Active();
				MyMouse->Show();
				//--------------eg�r kettint�s esem�ny
				if ( ActiveButton->OnCoords( MPoz ) )	{
					Event( ActiveButton->Handler );
				}
			}
		}
	}
	delete Con;
	ChangeMode( MT_CLEAR );
	if ( ESC ) while ( ESC ) usleep(1000);
	MyMouse->Hide();
	delete MyMouse;
	switch ( PLevel )	{                          // a mem�ria helyre�ll�t�sa
		case 1:	{
			PicServer::LoadPicDirect( W_TEGLA2 );
			PicServer::LoadPicDirect( W_TEGLA );
			PicServer::LoadPicDirect( W_KO2 );
			PicServer::LoadPicDirect( W_KO );
			PicServer::LoadPicDirect( W_KOTEG2 );
			PicServer::LoadPicDirect( W_KOTEG );
		}	break;
		case 2:	{
			PicServer::LoadPicDirect( W2_TREE2 );
			PicServer::LoadPicDirect( W2_TREE );
			PicServer::LoadPicDirect( W2_KO2 );
			PicServer::LoadPicDirect( W2_KO );
		}	break;
	};
	DelTimer( 1 );
}

//*****************************************************************************
void TMenu::Event( int Hand )	{
	switch( Hand )	{
		case ID_TOP5:	{                    // a TOP5 gomb aktiv�l�sa
			ChangeMode( MT_TOP5 );
			MyMouse->Hide();
			TextBack=(char *)malloc( 310 * 122 );
			GetImage( 5 , 40 , TextBack , 310 , 122 );
			TUserData* UsrDat=new TUserData[5];
			int F=open( USER_DAT , O_RDWR | O_BINARY );
			if ( F!=-1 )	{
				if ( read( F , UsrDat , sizeof(TUserData)*5 )==sizeof(TUserData)*5 )	{
					for ( int r=0 ; r<5 ; r++ )	{
						Con->GotoXY( POINT( 5 ,r*22+40) );
						char Str[60],Num[3];
						itoa ( r+1 , Num , 10 );
						strcpy( Str , Num );
						strcat( Str , " " );
						if ( UsrDat[r].Name[0]!='*' )	{
							strcat( Str , UsrDat[r].Name );
							while ( strlen( Str )<19 )	strcat( Str , "." );
							strcat( Str , " 00.00 0" );
							Str[20]+=char(((UsrDat[r].Time/60)/10)%10);
							Str[21]+=char((UsrDat[r].Time/60)%10);
							Str[23]+=char((UsrDat[r].Time%60)/10);
							Str[24]+=char((UsrDat[r].Time%60)%10);
							Str[26]+=char(UsrDat[r].Level);
						}	else	{
								strcat( Str , "................. " );
							}
						Con->OutText( Str );
					}
				};
				close( F );
			}
			delete []UsrDat;
			MyMouse->Show();
		}	break;
		case ID_NEW:	{                        // a NEW GAME gomb akt�v�l�sa
			TextShift=0;
			ChangeMode( MT_NAME );
			MyMouse->Hide();
			TextBack=(char *)malloc( 20*230 );                    // <--
			TB2=(char *)malloc( 20*320 );
			GetImage( 50 , 120 , TextBack , 230 , 20 );
			GetImage( 0, 0 , TB2 , 320 , 20 );
			Bar ( 50 , 120 , 280 , 140 , 0 );
			Con->GotoXY( POINT (50 , 120) );
			Con->OutText( TMe::UserName );
			TextLineMove=TRUE;
			mouse_y_limit( 20 , 200 );
			MyMouse->Show();
		}	break;
		case ID_TLEFT:
		case ID_TRIGHT:
		case ID_LEFT:
		case ID_RIGHT:
		case ID_FORW:
		case ID_BACK:
		case ID_FIRE:	 {
			ActiveLine=ActiveButton->Handler-ID_FORW;
			MyMouse->Hide();
			Con->GotoXY( POINT (140+CurRect[ActiveLine].Sx , 25+ActiveLine*20 ));
			MyMouse->Show();
		}	break;
		case ID_EXI:  	{                         // az EXIT gomb akt�v�l�sa
			ChangeMode( MT_EXIT );
		}	break;
		case ID_BACKM:  	{                      // visszal�p�s a men�ben
			switch ( MenuMode )	{
				case MT_CONTROL:	{                     // a CONTROL me�b�l:
					MyMouse->Hide();
					PutImage( 140 , 25 , TextBack , 110 , 140 );
					free( TextBack );
					TextBack=NULL;
					MyMouse->Show();
					ActiveLine=0;
					ChangeMode( MT_MAIN );
				}	break;
				case MT_NAME:	{                        // a NEW GAME me�b�l:
					MyMouse->Hide();
					Con->HideCursor();                                     // <--
					PutImage( 50 , 120 , TextBack , 230 , 20 );
					PutImage( 0 ,0 , TB2 , 320 ,20 );
					free(TextBack);
					free( TB2);
					TB2=TextBack=NULL;
					TextLineMove=FALSE;
					mouse_y_limit( 0 , 200 );
					MyMouse->Show();
					ChangeMode( MT_MAIN );
				}	break;
				case MT_TOP5:	{                        // a TOP5 men�b�l
					MyMouse->Hide();
					PutImage( 5 , 40 , TextBack , 310 , 122 );
					free ( TextBack );
					TextBack=NULL;
					MyMouse->Show();
					ChangeMode( MT_MAIN );
				}	break;
			};
		}	break;
		case ID_CON:  	{                              // a CONTOL gomb akt�v�l�sa
			ChangeMode( MT_CONTROL );
			TextBack=(char *)malloc( 140*110 );
			MyMouse->Hide();
			GetImage( 140 , 25 , TextBack , 110 , 140 );
			for ( int n=0 ; n<7 ; n++ )	{
				Con->GotoXY( POINT(140 , 25+20*n) );
				char name [20];
				CurRect[n]=( Con->OutText( GetKeyName( CKey[n], name ) ) );
			}
			ActiveLine=0;
			Con->GotoXY( POINT (140+CurRect[ActiveLine].Sx , 25+ActiveLine*20 ));
			MyMouse->Show();
		}	break;
		case ID_YES:                                // a kil�p�s meger�s�t�se
			MenuExit=TRUE;
			ExitLoop( 0 );
			break;
		case ID_NO:                                 // vissza l�p�s a kl�p�s me�b�l
			ChangeMode( MT_MAIN );
			break;
		case ID_START:	{                            // �j j�t�k ind�t�sa
			MyMouse->Hide();
			mouse_y_limit( 0 , 200 );
			Con->HideCursor();
			PutImage( 50 , 120 , TextBack , 230 , 20 );
			PutImage( 0,0, TB2 , 320 , 20 );
			free(TextBack);
			free(TB2);                     // <--
			TextBack=NULL;
			TB2=NULL;
			MenuExit=TRUE;
			if ( PLevel>0 ) ExitLoop( 1 );
			MyMouse->Show();
			TextLineMove=FALSE;
		}	break;
	}
}
//*****************************************************************************
// a h�tt�rben l�that� els�t�t�tett sz�nes n�gyzetek:
void	TMenu::DarkScr()		{
	ColoredBarLines( POINT( 10 , 20 ) , RECT( 310 , 160 ) , (BYTE)0 );
	ColoredBarLines( POINT( 20 , 10 ) , RECT( 10 , 180 ) , PC_ORANGE );
	ColoredBarLines( POINT( 0 , 160 ) , RECT( 320 , 10 ) , PC_RED );
}
//*****************************************************************************
// me� v�lt�s:
void TMenu::ChangeMode( TMenuType Mode )	{
	MyMouse->Hide();
	switch ( Mode )	{
		case MT_MAIN:
		case MT_TOP5:
		case MT_EXIT:
		case MT_CLEAR:
			Con->HideCursor();
			break;
		case MT_CONTROL:
		case MT_NAME:
			Con->ShowCursor();
			break;
	}
	if ( Buttons )	{
		register TButton * *Puff=Buttons;   // minden men� elem elt�ntet�se:
		while ( (*Puff) )	{
			(*Puff)->Free();
			Puff++;
		}
	}
	Buttons = ButtonList[ MenuMode=Mode ]; // men� azonos�t� csere:
	if ( Buttons )	{
		register TButton * *Puff=Buttons;   // minden men� elem kirajzol�sa:
		while ( (*Puff) )	{
			(*Puff)->Show( 0 );
			Puff++;
		}
		ActiveButton=(* Buttons);
	}
	if ( ActiveButton ) ActiveButton->Active();
	MyMouse->Show();
};
//******************************************************************************
void TMenu::MoveLine()	{
	// if ( LastCount!=Count )	{
	// 	if ( TextShift>int(CUR_SIZE-2) ) TextShift=0 ;
	// 	if ( !TextShift )	{
	// 		char LastCh=Text[0];
	// 		int z;
	// 		for ( z=0 ; z<(strlen(Text)-1) ; z++ )	{
	// 			Text[z]=Text[z+1];
	// 		}
	// 		Text[z]=LastCh;
	// 		strcpy( DrawText , Text );
	// 		DrawText[27]=0;
	// 	}
	// 	Con->HideCursor();
	// 	POINT Last=Con->GotoXY( POINT ( 13-TextShift , 0 ) );
	// 	Con->OutText( DrawText , TRUE );
	// 	Con->ShowCursor();
	// 	LastCount=Count;
	// 	Con->GotoXY( Last );
	// 	TextShift+=3;
	// }
}

