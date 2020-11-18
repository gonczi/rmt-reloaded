#ifndef _CRASH_CPP
	#define _CRASH_CPP

#include "obj.h"
#include "grobj.h"

class TCrash  : TObj , TPozition	{
public:
	TCrash();
	virtual void Proc();
};

#endif //
