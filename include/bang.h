#ifndef _BANG_CPP
	#define _BANG_CPP

#include "obj.h"
#include "timer.h"
#include "graph13.h"

class TBang : TObj,TTimer	{
	static BOOL Banging;             // ha TRUE, akkor egy villog�s folyamatban van m�r
	static BOOL First;               // az els� objektumig TRUE
	static unsigned char RedPal[257][3],NormPal[257][3];   // k�t sz�npaletta: v�r�s,norm�l
	int mCount;                      // id�z�t� sz�ml�l�ja
	BOOL TSet;                       // ha villog�s van folyamatban megsz�n�skor
		// akkor vissza kell �ll�tani az eredeti sz�npalett�t, ezt jelzi ez
public:
	TBang();
	virtual void TimerProc( int Id );
	virtual~TBang()	{
		SetPaletteRegistersNoWait(0,256,&NormPal);
		if ( TSet )DelTimer( 1 );
		Banging=FALSE;
	};
};

#endif//_BANG_CPP
