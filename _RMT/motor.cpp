/*******************************************************************************
		motor.cpp
*******************************************************************************/
#ifndef _MOTOR_CPP
	#define _MOTOR_CPP
// a grafikus motor
#include <math.h>
#include <values.h>
#include "ME.CPP"
#include "walls.cpp"
#include "grobj.cpp"
#include "scrobj.cpp"
#include "globals.cpp"
#include "typedef.cpp"
// szabad vektor egy oszlopban, le�r� rekoirdja
struct	TSpace	{
	int Sp,Ep;        // kezd� pont v�gpont
};
#define  MIN(A,B) ((A>B)?B:A)
#define  MAX(A,B) ((A<B)?B:A)
#define OTHER (SSFlag?0:1)
long SCR   =200 ;  	// elm�leti t�vols�g a monitol s�kj�t�l
long TOP	=300;
#define CRASHMIN 280.0    // legkissebb t�vols�g k�t TObj k�z�tt.  ?:)
#define BLINDSTAIN 	2    // legkissebb vizsg�lati sz�g, "vakfolt"
float  LOOKTOP=0.91;
int 	 SCRTOP=162;   // horizont emel�se

class TMotor: TObj	{
	TMe *Me;
	long RMax;     // a legut�bbi oszlop kirajzol�snl m�rt legnagyobb fal t�vols�g
	int OSP;       // az obj stack teteje
	int SSPHi[2];  // a list�k teteje
	int SSPLo[2];  // a list�k alja
	static char SSFlag;    // az aktu�lis sor azonos��ja
	void DelList()	{ SSPLo[1]=SSPLo[0]=SSPHi[1]=SSPHi[0]=OSP=0; };
	TGrObj *ObjStack[100]; // objektum nyilv�ntart� lista
	TSpace Space[100][2];  // a kett�s sor
	void OSAdd( TGrObj *NewObj );  // GrObj hozz�ad�sa a list�hoz
	void SSPush( int iSp , int iEp , char SF );    // szabad vektor lits�hoz ad�sa
	BOOL SSPop( int &iSp , int &iEp , char SF );   // adat kiemel�se a list�b�l
	void MakeObjList();    // az objektumok meghat�roz�sa a p�ly�n, objlist elk�sz�t�se
public:
	TMotor( TMe* iMe );
	~TMotor();
	virtual void Proc();
	TBmp * *Air;
};
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
	register id,shift;
	register long look;
	register idV=0;
	register float shiftV=0,lookV=MAXLONG;
	register idH=0;
	register float shiftH=0,lookH=MAXLONG;
	char far *xAir=&((*Air)->Pic[ (unsigned)((norm(Me->Alfa)/(2.0*M_PI))*((*Air)->Y))*((*Air)->X)  ]);
	for ( register int cx=0 ; cx< MAXX ; cx++ )
	{
		register RSCR=int(sqrt((SCR*SCR)+(cx-160.0)*(cx-160.0)));
		register float beta=norm(Me->Alfa+atan((cx-160.0)/SCR));
		register int sinb=(sin(beta)*1000);
		register int cosb=(cos(beta)*1000);
		if ( cosb> BLINDSTAIN ) {          // vertik�lis fal keres�s keleti ir�nyba
			register double b=(-Me->Fx);
			for ( long fx=0 ; fx<(SIZEX-Me->SectorX) ; fx++ )	{
				register float a;
				b+=MRECT;
				a=tan(beta)*b;
				long ar=((Me->Fy+a)/MRECT-((a<0)?1:0));
				register int wx,wy;
				wx=int(Me->SectorX+fx+1);
				wy=int(ar+Me->SectorY);
				if ( TableV[wx][wy] )	{
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
				register int wx,wy;
				b-=MRECT;
				a=tan(beta)*b;
				long ar=((Me->Fy+a)/MRECT-((a<0)?1:0));
				wx=int(Me->SectorX+fx);
				wy=int(ar+Me->SectorY);
				if ( TableV[wx][wy] )	{
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
				register int wx,wy;
				a=((MRECT-Me->Fy)+(fy*MRECT));
				b=(a/tan(beta));
				long br=((Me->Fx+b)/MRECT-((b<0)?1:0));
				wx=int(br+Me->SectorX);
				wy=int(Me->SectorY+fy+1);
				if ( TableH[wx][wy] ) {
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
					register int wx,wy;
					a=((fy*MRECT)-Me->Fy);
					b=(a/tan(beta));
					long br=((Me->Fx+b)/MRECT-((b<0)?1:0));
					wx=int(br+Me->SectorX);
					wy=int(Me->SectorY+fy);
					if ( TableH[wx][wy]) {
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
		register long sega000x=0xa0000000L+cx;
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
						register Sp=Vector->Sp+ScrObj->Poz.y;
						register Ep=Vector->Ep+ScrObj->Poz.y;
						if ( (Hi<Ep) && (Lo>Sp) )	{
							Out=FALSE;
							for ( int Sy=MAX(Sp,Hi) ; Sy<MIN(Ep,Lo) ; Sy++ )	{
								((char far *)sega000x)[Sy*320]=Vector->Start[ Sy-Sp ];
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
						register Sp=SCRTOP+(( Vector->Sp - GrObj->High - (int)GrObj->Pic->Y/2)*GrObj->Size*SCR)/GrObj->R;
						register Ep=SCRTOP+(( Vector->Ep - GrObj->High - (int)GrObj->Pic->Y/2)*GrObj->Size*SCR)/GrObj->R;
						if ( (Hi<Ep) && (Lo>Sp) )	{
							Out=FALSE;
							for ( int Sy=MAX(Sp,Hi) ; Sy<MIN(Ep,Lo) ; Sy++ )	{
								((char far *)sega000x)[Sy*320]=Vector->Start[(int)(((float)Vector->Len/(Ep-Sp))*(Sy-Sp))];
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
		register sx=(*Wall[id])->X,
					sy=(*Wall[id])->Y;
		register szorz=int((look*sy*sy)/(RSCR*TOP));
		if ( !szorz )	szorz=1;
		register plus=(LOOKTOP*sy);
		register char * picture=((*Wall[id])->Pic+shift+(plus*sx));
		int Hi,Lo;
		register Sp=((-plus*sy)/szorz)+SCRTOP;
		register Ep=(((sy-plus)*sy)/szorz)+SCRTOP;
		if ( xAir >= &((*Air)->Pic[(*Air)->Size-(*Air)->Y]) ) xAir = &((*Air)->Pic[0L]);
			else xAir+=((*Air)->X);
		while ( SSPop( Hi , Lo ) )	{
			register iSp=MAX(Sp,Hi);
			register iEp=MIN(Ep,Lo);
			for ( register  cy=(iSp<0)?0:iSp ; cy<((iEp>200)?200:iEp) ; cy++ )
				((char far *)sega000x)[cy*320]=picture[ (((cy-SCRTOP)*szorz)/sy)*sx ];
			for ( cy=MIN(iEp,Hi);  cy<MIN(SCRTOP,MIN(Lo,iSp));  cy++ )
				((char far *)sega000x)[cy*320]=xAir[ cy%((*Air)->X) ];
			for ( cy=MAX(SCRTOP,MAX(Hi,iEp));  cy<Lo;  cy++ )
				((char far *)sega000x)[cy*320]=PC_GREEN;
		}
	}
}
#endif //_MOTOR_CPP
