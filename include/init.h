#ifndef _INIT_CPP
	#define _INIT_CPP

#include "walls.h"
#include "obj.h"

class TInit :public TObj	{
	BOOL LoadObjTable( char *Fname );
	char *ObjTable;
	int Level;
	TWalls *Walls;
	void SaveUserData();
public:
	static char *ObjFname[];
	TInit( int Lev );
	~TInit();
};

#endif //_INIT_CPP
