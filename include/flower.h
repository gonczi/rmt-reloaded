#ifndef _FLOWER_CPP
	#define _FLOWER_CPP

#include "grobj.h"
#include "globals.h"

class TFlower: public TGrObj	{
	public:
	TFlower(int Sx,int Sy);
	virtual ~TFlower();
	void MsgProc (	void * ,
						unsigned Msg ,
						unsigned long  ,
						unsigned long  );
};

#endif //_FLOWER_CPP
