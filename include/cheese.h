#ifndef _CHEESE_CPP
	#define _CHEESE_CPP

#include "grobj.h"

class TCheese: public TGrObj{
	public:
	TCheese( int Sx,int Sy );
	~TCheese();
	void MsgProc (	void * ,
						unsigned Msg ,
						unsigned long  ,
						unsigned long  );
};

#endif //_CHEESE_CPP
