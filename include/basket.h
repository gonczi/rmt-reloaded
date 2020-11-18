#ifndef _BASKET_CPP
	#define _BASKET_CPP

#include "grobj.h"
#include "globals.h"

class TBasket: public TGrObj	{
	public:
	TBasket(int Sx,int Sy);
	virtual ~TBasket();
	void MsgProc (	void * ,
						unsigned Msg ,
						unsigned long  ,
						unsigned long  );
};

#endif //_CHEESE_CPP
