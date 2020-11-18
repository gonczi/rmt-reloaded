#ifndef	_CAT_CPP
	#define _CAT_CPP

#include "grobj.h"
#include "timer.h"
#include "picclass.h"

class TCat: public TGrObj,public TTimer{
	int Stop,Silly;
	TPicClass * *PicClass;
	int PCount;
public:
	TCat( int Sx,int Sy );
	~TCat();
	void MsgProc (	void * ,
						unsigned Msg ,
						unsigned long  ,
						unsigned long  );
	virtual void TimerProc( int Id );
	virtual void Proc ()  ;
};

#endif //_CAT_CPP
