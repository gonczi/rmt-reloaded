#ifndef _MOTOR_CPP
	#define _MOTOR_CPP

#include "grobj.h"
#include "bmp.h"

// szabad vektor egy oszlopban, le�r� rekoirdja
struct	TSpace	{
	int Sp,Ep;        // kezd� pont v�gpont
};

#define  MIN(A,B) ((A>B)?B:A)
#define  MAX(A,B) ((A<B)?B:A)
#define OTHER (SSFlag?0:1)

extern long SCR;  	// elm�leti t�vols�g a monitol s�kj�t�l
extern long TOP;

#define CRASHMIN 280.0    // legkissebb t�vols�g k�t TObj k�z�tt.  ?:)
#define BLINDSTAIN 	2    // legkissebb vizsg�lati sz�g, "vakfolt"

extern float  LOOKTOP;
extern int 	 SCRTOP;   // horizont emel�se

class TMe;

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

#endif //_MOTOR_CPP
