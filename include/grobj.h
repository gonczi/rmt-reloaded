#ifndef _GROBJ_CPP
	#define _GROBJ_CPP

#include "typedef.h"
#include "obj.h"
#include "picture.h"

#define TOGROBJ(a) ((TGrObj *)(a))

// objektumok oszt�lyoz�sa az �tk�z�s szempontj�b�l
enum CAST{ NOBODY , FRIEND , NME };

// egy�ni azonos�t�k az objektumok sz�m�ra, az �zenet kezel�shez
enum GR_NAME{ 	GR_NOBODY , GR_CAT , GR_CHEESE ,
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

struct TGrObjList	{                   // GrObj lista elem defin�ci�
	TGrObj *GrObj;                      // mutat� az elemre
	TGrObjList *  Next;                 // mutat� a k�vetkez� elemre
};

extern TGrObjList* GrObjList;

//-*****************************************************************************

float GetDR(TGrObj* Obj1,TGrObj* Obj2);

#endif //_GROBJ_CPP
