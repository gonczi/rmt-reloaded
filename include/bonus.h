#ifndef _BONUS_CPP
	#define _BONUS_CPP

#include "obj.h"
#include "scrobj.h"
#include "timer.h"

class TBonus : TObj,public TTimer	{
	int mCount;
	BOOL TSet;
	TScrObj *Pic;
public:
	TBonus();
	~TBonus()	{
		DelTimer( 1 );
		delete Pic;
	};
	virtual void Proc();
};

#endif // class TBonus
