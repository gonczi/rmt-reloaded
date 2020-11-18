#include "motor.h"

#include "me.h"

#include <math.h>
#include <values.h>
#include "walls.h"
#include "scrobj.h"
#include "globals.h"
#include "typedef.h"
#include "grobj.h"
#include "graph13.h"

long SCR   =200 ;  	// elm�leti t�vols�g a monitol s�kj�t�l
long TOP	=300;

float  LOOKTOP=0.91;
int 	 SCRTOP=162;   // horizont emel�se

char TMotor::SSFlag=0;

//******************************************************************************
TMotor::TMotor( TMe *iMe ):TObj( STATIC )	{
	Me=iMe;
	Register();
	for ( OSP=0 ; OSP<100 ; ObjStack[OSP++]=NULL );
	DelList();
	Air=(TBmp * *)PicServer::GetPic( AIR );
//   while ( !F1 );
};
//******************************************************************************
TMotor::~TMotor() {
	PicServer::Free( AIR );
};
//******************************************************************************
void TMotor::OSAdd( TGrObj *NewObj )	{
	ObjStack[ OSP++ ]=NewObj;
};
//******************************************************************************
void TMotor::SSPush( int iSp , int iEp , char SF=SSFlag )	{
	Space[ SSPHi[SF] ][ SF ].Sp=iSp;
	Space[ SSPHi[SF] ][ SF ].Ep=iEp;
	if ( ++SSPHi[SF] >= 100  ) SSPHi[SF]=0;
};
//******************************************************************************
BOOL TMotor::SSPop( int &iSp , int &iEp , char SF=SSFlag )	{
	if (  SSPHi[SF] != SSPLo[SF]  )	{
		iSp=Space[ SSPLo[SF] ][ SF ].Sp;
		iEp=Space[ SSPLo[SF] ][ SF ].Ep;
		if ( ++SSPLo[SF] >= 100 ) SSPLo[SF]=0;
		return TRUE;
	}
	return FALSE;
};
//******************************************************************************
void TMotor::MakeObjList()	{
	DelList();
	TGrObjList *Puff=GrObjList;
	register float Gamma=atan(160.0/SCR);   // a monitor l�t�sz�g fele
	while( Puff )	{                        // v�gig megy minden objektumon
		register TGrObj *GrObj = Puff->GrObj;
		register long Dx=(GrObj->SectorX*MRECT+GrObj->Fx)-(Me->SectorX*MRECT+Me->Fx);
		register long Dy=(GrObj->SectorY*MRECT+GrObj->Fy)-(Me->SectorY*MRECT+Me->Fy);
		register float R= sqrt(Dx*Dx+Dy*Dy);  // t�vols�g meghat�roz�sa
		if ( R < CRASHMIN )	{                // ha t�l k�zel van, akkor �tk�z�s
			SendMessage( GrObj , MSG_CRASH , TOLp(Me)  , TOWp(GR_ME) );
		}
		if ( ( R<RMax ) && (R!=0.0) )	{
			register float Beta= norm(( Dy>0 ) ? acos( Dx/R ) : -acos( Dx/R ));
			register float Delta= norm(atan(((GrObj->Pic->X/2)*GrObj->Size)/R) + Gamma);
			if ( (absf(Beta-Me->Alfa)<Delta) || (absf(Beta-Me->Alfa)>norm((2.0*M_PI)-Delta))  )  	{
				GrObj->R=R;
				GrObj->Beta=Beta;
				GrObj->Start=160L-tan( Me->Alfa-Beta+Delta-Gamma )*SCR;
				GrObj->End  =160L-tan( Me->Alfa-Beta-Delta+Gamma )*SCR;
				OSAdd( GrObj );
			} else GrObj->Beta=0.0;
		};
		Puff=Puff->Next;
	}													  // rendez�s t�vols�g alapj�n
	for ( char OS=0 ; OS<OSP ; OS++ )
		for ( char OSN=(OS+1) ; OSN<OSP ; OSN++ )
			if	( ObjStack[OS]->R > ObjStack[OSN]->R )	{
				register TGrObj *Puff=ObjStack[OSN];
				ObjStack[OSN]=ObjStack[OS];
				ObjStack[OS]=Puff;
			}
};
//******************************************************************************
void TMotor::Proc()	{
	MakeObjList();
	RMax=0;
	register int id,shift;
	register long look;
	register int idV=0;
	register float shiftV=0,lookV=MAXLONG;
	register int idH=0;
	register float shiftH=0,lookH=MAXLONG;
	char *xAir=&((*Air)->Pic[ (unsigned)((norm(Me->Alfa)/(2.0*M_PI))*((*Air)->Y))*((*Air)->X)  ]);
	for ( register int cx=0 ; cx< MAXX ; cx++ )
	{
		register int RSCR=int(sqrt((SCR*SCR)+(cx-160.0)*(cx-160.0)));
		register float beta=norm(Me->Alfa+atan((cx-160.0)/SCR));
		register int sinb=(sin(beta)*1000);
		register int cosb=(cos(beta)*1000);
		if ( cosb> BLINDSTAIN ) {          // vertik�lis fal keres�s keleti ir�nyba
			register double b=(-Me->Fx);
			for ( long fx=0 ; fx<(SIZEX-Me->SectorX) ; fx++ )	{
				register float a;
				register unsigned wx,wy;
				b+=MRECT;
				a=tan(beta)*b;
				long ar=((Me->Fy+a)/MRECT-((a<0)?1:0));
				wx=unsigned(Me->SectorX+fx+1);
				wy=unsigned(ar+Me->SectorY);
				if ( (SIZEX > wx) && (SIZEY > wy) && TableV[wx][wy] )	{
					idV=TableV[wx][wy];
					shiftV=(long(a+Me->Fy)-long(ar*MRECT));
					shiftV=( (*Wall[idV])->X*(shiftV/MRECT));
					lookV=sqrt((a*a)+(b*b));
					break;
				} else lookV=MAXLONG;
			};
	} else if ( cosb< -BLINDSTAIN ) {     // vertik�lis fal keres�s nyugatra
				register float b=(MRECT-Me->Fx);
				for ( long fx=0 ; fx>(-(Me->SectorX+1)) ; fx-- )	{
				register float a;
				register unsigned wx,wy;
				b-=MRECT;
				a=tan(beta)*b;
				long ar=((Me->Fy+a)/MRECT-((a<0)?1:0));
				wx=unsigned(Me->SectorX+fx);
				wy=unsigned(ar+Me->SectorY);
				if ( (SIZEX > wx) && (SIZEY > wy) && TableV[wx][wy] )	{
					idV=TableV[wx][wy];
					shiftV=(long(a+Me->Fy)-long(ar*MRECT));
					shiftV=((*Wall[idV])->X*(shiftV/MRECT));
					lookV=sqrt((a*a)+(b*b));
					break;
				} else lookV=MAXLONG;
			};
		};
	if ( sinb> BLINDSTAIN ) {				// horizont�lis falak d�li ir�nyban
			for ( long fy=0 ; fy<(SIZEY-Me->SectorY) ; fy++ ) {
				register float a,b;
				register unsigned wx,wy;
				a=((MRECT-Me->Fy)+(fy*MRECT));
				b=(a/tan(beta));
				long br=((Me->Fx+b)/MRECT-((b<0)?1:0));
				wx=unsigned(br+Me->SectorX);
				wy=unsigned(Me->SectorY+fy+1);
				if ( (SIZEX > wx) && (SIZEY > wy) && TableH[wx][wy] )	{
					idH=TableH[wx][wy];
					shiftH=(long(b+Me->Fx)-long(br*MRECT));
					shiftH=((*Wall[idH])->X*(shiftH/MRECT));
					lookH=sqrt((a*a)+(b*b));
					break;
				} else lookH=MAXLONG;
			};
	} else if ( sinb< -BLINDSTAIN ) {  // horizont�lis falak �szakra
				for ( long fy=0 ; fy>(-(Me->SectorY+1)) ; fy-- ) {
					register float a,b;
					register unsigned wx,wy;
					a=((fy*MRECT)-Me->Fy);
					b=(a/tan(beta));
					long br=((Me->Fx+b)/MRECT-((b<0)?1:0));
					wx=unsigned(br+Me->SectorX);
					wy=unsigned(Me->SectorY+fy);
				if ( (SIZEX > wx) && (SIZEY > wy) && TableH[wx][wy] )	{
						idH=TableH[wx][wy];
						shiftH=(long(b+Me->Fx)-long(br*MRECT));
						shiftH=((*Wall[idH])->X*(shiftH/MRECT));
						lookH=sqrt((a*a)+(b*b));
						break;
					} else lookH=MAXLONG;
				};
			};
		if ( lookV<lookH )	{    // �sszehasonl�t�s a kappott eredm�nyek alapj�n
			look=lookV;            // csak a k�zelebbit kell figyelembe venni
			id=idV;
			shift=shiftV;
		} else	{
			look=lookH;
			id=idH;
			shift=shiftH;
		};
		if ( look>RMax ) RMax=look;  // ez lesz az el�z� oslop fal t�vols�ga
		
		register long sega000x = sega000 + cx;

		SSPush( 0 ,199 );            // a forr�s verem inicializ�l�sa
//******************************************************   SCREEN OBJECTS  *****
// Screen objektumok kerers�se felfest�se
		TScrObj *ScrObj=ScrObjList;
		while	( ScrObj	)	{
			if ( (cx < (ScrObj->Poz.x + ScrObj->Pic->X)) && ( cx >= ScrObj->Poz.x ) )	{
				int Rx= cx-(ScrObj->Poz.x);
				int Hi,Lo;
				while ( SSPop( Hi , Lo ) )	{
					BOOL Out=TRUE;
					for ( int Vect=0 ; Vect < ScrObj->Pic->Row[Rx].Num ; Vect++ ){
						register Pic_Vector *Vector=&(ScrObj->Pic->Row[Rx].Vector[Vect]);
						register int Sp=Vector->Sp+ScrObj->Poz.y;
						register int Ep=Vector->Ep+ScrObj->Poz.y;
						if ( (Hi<Ep) && (Lo>Sp) )	{
							Out=FALSE;
							for ( int Sy=MAX(Sp,Hi) ; Sy<MIN(Ep,Lo) ; Sy++ )	{
								((char *)sega000x)[Sy*320]=Vector->Start[ Sy-Sp ];
							}
							if ( Hi<Sp ) SSPush( Hi , Sp , OTHER );
							if ( Lo>Ep )	{
								Out=TRUE;
								Hi=Ep;
							} 	else break;
						}
					}
					if ( Out ) SSPush( Hi , Lo , OTHER );
				}
				SSFlag=( OTHER );
			}
			ScrObj=ScrObj->Next;
		}
//******************************************************   OBJECTS   ***********
// GrObj objektumok kirajzol�sa
// az elk�sz�tett lista alapj�n
		for ( char SS=0; (SS < OSP) && (ObjStack[SS]->R<look) ; SS++ )	{
			register TGrObj *GrObj=ObjStack[SS];
			if ( cx>GrObj->Start && cx<GrObj->End )	{
				int Rx=(tan(GrObj->Beta - beta)*GrObj->R)/GrObj->Size+(GrObj->Pic->X/2);
				int Hi,Lo;
				while ( SSPop( Hi , Lo ) )	{
					BOOL Out=TRUE;
					for ( int Vect=0 ; Vect<GrObj->Pic->Row[Rx].Num ; Vect++ ){
						register Pic_Vector *Vector=&GrObj->Pic->Row[Rx].Vector[Vect];
						register int Sp=SCRTOP+(( Vector->Sp - GrObj->High - (int)GrObj->Pic->Y/2)*GrObj->Size*SCR)/GrObj->R;
						register int Ep=SCRTOP+(( Vector->Ep - GrObj->High - (int)GrObj->Pic->Y/2)*GrObj->Size*SCR)/GrObj->R;
						if ( (Hi<Ep) && (Lo>Sp) )	{
							Out=FALSE;
							for ( int Sy=MAX(Sp,Hi) ; Sy<MIN(Ep,Lo) ; Sy++ )	{
								((char *)sega000x)[Sy*320]=Vector->Start[(int)(((float)Vector->Len/(Ep-Sp))*(Sy-Sp))];
							}
							if ( Hi<Sp ) SSPush( Hi , Sp , OTHER );
							if ( Lo>Ep )	{
								Out=TRUE;
								Hi=Ep;
							} 	else break;
						}
					}
					if ( Out ) SSPush( Hi , Lo , OTHER );
				}
				SSFlag=( OTHER );
			}
		}
//******************************************************  WALLS & BACKGR *******
// falak �s a h�tt�r k�p kirajzol�sa
		register int sx=(*Wall[id])->X,
					sy=(*Wall[id])->Y;
		register int szorz=int((look*sy*sy)/(RSCR*TOP));
		if ( !szorz )	szorz=1;
		register int plus=(LOOKTOP*sy);
		register char * picture=((*Wall[id])->Pic+shift+(plus*sx));
		int Hi,Lo;
		register int Sp=((-plus*sy)/szorz)+SCRTOP;
		register int Ep=(((sy-plus)*sy)/szorz)+SCRTOP;
		if ( xAir >= &((*Air)->Pic[(*Air)->Size-(*Air)->Y]) ) xAir = &((*Air)->Pic[0L]);
			else xAir+=((*Air)->X);
		while ( SSPop( Hi , Lo ) )	{
			register int iSp=MAX(Sp,Hi);
			register int iEp=MIN(Ep,Lo);
			for ( register int cy=(iSp<0)?0:iSp ; cy<((iEp>200)?200:iEp) ; cy++ )
				((char *)sega000x)[cy*320]=picture[ (((cy-SCRTOP)*szorz)/sy)*sx ];
			for ( register int cy=MIN(iEp,Hi);  cy<MIN(SCRTOP,MIN(Lo,iSp));  cy++ )
				((char *)sega000x)[cy*320]=xAir[ cy%((*Air)->X) ];
			for ( register int cy=MAX(SCRTOP,MAX(Hi,iEp));  cy<Lo;  cy++ )
				((char *)sega000x)[cy*320]=PC_GREEN;
		}
	}
}
