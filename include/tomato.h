#ifndef _Tomato_CPP
	#define _Tomato_CPP

#include "pic_serv.h"
#include "grobj.h"
#include "timer.h"

class TTomato: public TGrObj 	{
	long StepD;                       // l�p�sk�z
	BOOL Kill;                        // megsemmis�t�s folyamat�nak jelz� �rt�ke
	TPicClass * PicClass;             // a l�ved�k k�pe
	//  k�p[0] a rep�l� l�ved�k�
	//  k�p[1] a megsemmis�lt l�ved�k k�pe
public:
	TTomato(int , int , int , int , float);
	virtual ~TTomato();
	void Proc () ;
	void MsgProc ( void * Adr , unsigned Msg , unsigned long Lparam , unsigned long Wparam );
};

#endif // _Tomato_CPP
