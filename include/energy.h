#ifndef _ENERGY_CPP
	#define _ENERGY_CPP

#include "obj.h"
#include "scrobj.h"

class TEnergy: TObj	{
	int Q;
	TScrObj *Back, *Rows;    // h�tt�r , �rt�k
	int RX;
public:
	TEnergy( POINT Poz );
	~TEnergy();
	int Add(int D);
	int GetNum() { return Rows->Pic->X; };
};

#endif // _ENERGY_CPP
