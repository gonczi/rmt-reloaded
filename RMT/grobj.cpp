/*******************************************************************************
					grobj.cpp
*******************************************************************************/
#ifndef _GROBJ_CPP
	#define _GROBJ_CPP
// grafikus szerepl� objektumok a j�t�kban
#include "typedef.cpp"
#include "globals.cpp"
#include "obj.cpp"
#include "picclass.cpp"
#include "walls.cpp"
#define TOGROBJ(a) ((TGrObj *)(a))
// objektumok oszt�lyoz�sa az �tk�z�s szempontj�b�l
typedef enum CAST{ NOBODY , FRIEND , NME };
// egy�ni azonos�t�k az objektumok sz�m�ra, az �zenet kezel�shez
typedef enum GR_NAME{ 	GR_NOBODY , GR_CAT , GR_CHEESE ,
								GR_BASKET , GR_FLOWER , GR_TOMATO ,
								GR_ME };
// �zenet a bonusz objektumok sz�m�ra
#define NEW_BASKET 100
#define NEW_FLOWER 101
#define NEW_CHEESE 102
class TPozition	{
	void AddPoz( int , int );           // l�ptet�s a p�ly�n
	float StepOk( BOOL &Corner );       // ellen�rzi hogy az obj. pozici�ja megfelel�-e
public:
	CAST  Cast;                         // �tk�z�s oszt�ly
	GR_NAME  Name;                      // azonos�t�
	int MapColor;                       // sz�n a t�rk�pen
	int SectorX,SectorY;                // aktu�lis szektor
	int Fx,Fy;                          // pontos pozici� a szektorban
	float Alfa;                         // ir�ny sz�g
	int Min,Step;                       // minim�lis falmegk�zel�t�si t�vols�g, l�p�s k�z
	BOOL StepOne();                     // l�ptet egyet az adott ir�nyba Step t�vols�gnyit
	BOOL StepOne( float &Wall );        // ua. csak visszat�r az �rintett fal ir�nysz�g�vel
};
class TGrObj;
struct TGrObjList	{                    // GrObj lista elem defin�ci�
	TGrObj *GrObj;                      // mutat� az elemre
	TGrObjList *  Next;                 // mutat� a k�vetkez� elemre
} * GrObjList=NULL;                    // glob�lis lista fej

class TGrObj:public TObj, public TPozition	{
	void GrRegister();                  // az objektum regisztr�l�sa ...
	void GrDelete();                    // ... t�rl�se
public:
	TPicture *Pic;                      // a hozz� tartoz� k�p
	TGrObj( 	int Sx , int Sy , int iFx , int iFy , OBJTYPE gType  );
	virtual ~TGrObj();
// a motor haszn�lja a k�vetkez�ket:
//           a megfigyel�h�z viszony�tott:
	long R,Start,End;                   // t�vols�g
	float Beta;                         // sz�g
	int High;                           // lebeg�s a p�ly�n
	float Size;                         // k�p m�ret�nek ny�jt�sa
};
//-*****************************************************************************
TGrObj::TGrObj( 	int Sx=0 , int Sy=0 , int iFx=int(MRECT/2) , int iFy=int(MRECT/2) ,
						OBJTYPE gType=DINAMIC ):TObj( gType )	{
	High=0;                             // alap�rtelmez�s szerinti �rt�kek
	Name=GR_NOBODY;
	Cast = NOBODY;
	Pic=NULL;
	SectorX=Sx;
	SectorY=Sy;
	Fx=iFx;
	Fy=iFy;
	Beta=0.0;
	GrRegister();
}
//-*****************************************************************************
TGrObj::~TGrObj()	{
	GrDelete();
}
//-*****************************************************************************
void TGrObj::GrRegister()	{           // besz�r�s a lista elej�re
	register TGrObjList *Puff=GrObjList;
	GrObjList = new TGrObjList;
	GrObjList->GrObj=this;
	GrObjList->Next=Puff;
};
//-*****************************************************************************
void TGrObj::GrDelete()	{             // keres�s, t�rl�s
	if (	GrObjList )	{
		register TGrObjList *Puff=GrObjList;
		if ( Puff->GrObj==this )	{
			GrObjList=GrObjList->Next;
			delete Puff;
		}	else	{
				while ( Puff->Next )	{
					if ( Puff->Next->GrObj == this )	{
						register TGrObjList *Puff2=Puff->Next->Next;
						delete Puff->Next;
						Puff->Next=Puff2;
						break;
					};
					Puff=Puff->Next;
				}
			};
	}
};
//-*****************************************************************************
float  TPozition::StepOk( BOOL &Corner )	{
	Corner=FALSE;
	if ( Fx<Min )	{
		if ( TableV[SectorX][SectorY] )
			return (M_PI*2.0);
	}	else	{
			if ( (Fx>(MRECT-Min)) && TableV[SectorX+1][SectorY] )
			return (M_PI);
		}
	if ( (Fy<Min) && TableH[SectorX][SectorY] )	{
		return (M_PI/2.0) ;
	}	else	{
			if ( (Fy>(MRECT-Min)) && TableH[SectorX][SectorY+1] )
			return (M_PI*1.5);
		}
	Corner=TRUE;
	POINT Poz( Fx,Fy );
	if ( 	TableV[ SectorX ][ SectorY-1 ]  ||
			TableH[ SectorX-1 ][ SectorY ]  )	{
		if ( Poz/POINT(0.0,0.0) <= Min )	{
				return POINT(0.0,0.0)%Poz;
		}
	}
	if ( 	TableV[ SectorX ][ SectorY+1 ]  ||
			TableH[ SectorX-1 ][ SectorY+1 ]  )	{
		if ( Poz/POINT(0.0,MRECT) <= Min )	{
			return POINT(0.0,MRECT)%Poz;
		}
	}
	if ( 	TableV[ SectorX+1 ][ SectorY-1 ]  ||
			TableH[ SectorX+1 ][ SectorY   ]  )	{
		if ( Poz/POINT(MRECT,0.0) <= Min )	{
			return POINT(MRECT,0.0)%Poz;
		}
	}
	if ( 	TableV[ SectorX+1 ][ SectorY+1 ]  ||
			TableH[ SectorX+1 ][ SectorY+1 ]  )	{
		if ( Poz/POINT(MRECT,MRECT) <= Min )	{
			return POINT(MRECT,MRECT)%Poz;
		}
	}
	Corner=FALSE;
	return 0.0;
}
//-*****************************************************************************
void TPozition::AddPoz( int Dx,int Dy )	{
	register nSx=SectorX , nSy=SectorY;
	register nFx=Fx+Dx;
	register nFy=Fy+Dy;
	if ( nFx<0.0 )	{
		nSx--;
		nFx+=MRECT;
	}
	if ( nFx>=MRECT )	{
		nSx++;
		nFx-=MRECT;
	}
	if ( nFy<0.0 )	{
		nSy--;
		nFy+=MRECT;
	}
	if ( nFy>=MRECT )	{
		nSy++;
		nFy-=MRECT;
	}
	SectorX=nSx;
	SectorY=nSy;
	Fx=nFx;
	Fy=nFy;
}
//-*****************************************************************************
BOOL TPozition::StepOne( float &Wall )	{
	BOOL Ret=TRUE;
	AddPoz( int(cos(Alfa)*Step) , int(sin(Alfa)*Step) );
	int z=0;
	BOOL Corner=FALSE;
	while ( ( Wall=StepOk( Corner ) )!=0.0 )	{
		float Gamma=((Wall-Alfa)-M_PI);
		float BackStep=cos(Gamma)*Step;
		if ( BackStep<2.0 ) BackStep=2.0;
		AddPoz( int(cos(Wall)*(BackStep)) , int(sin(Wall)*(BackStep)) );
		Ret=FALSE;
		if ( z++ >300 ) return Ret;   // :)
	}
	return Ret;
};
//-*****************************************************************************
BOOL  TPozition::StepOne()	{
	float dumy=0.0;
	return StepOne( dumy );
};
//-*****************************************************************************
#include <math.h>                   // a motor haszn�lja, gyorsabb t�vols�g m�r�sre
float GetDR(TGrObj* Obj1,TGrObj* Obj2)	{  // k�t objektum k�z�tt
	register float Dx=(Obj1->SectorX*MRECT+Obj1->Fx)-(Obj2->SectorX*MRECT+Obj2->Fx);
	register float Dy=(Obj1->SectorY*MRECT+Obj1->Fy)-(Obj2->SectorY*MRECT+Obj2->Fy);
	return sqrt(Dx*Dx+Dy*Dy);
};
#endif //_GROBJ_CPP
