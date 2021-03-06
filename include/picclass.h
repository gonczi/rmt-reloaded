#ifndef _PICCLASS_CPP
# define _PICCLASS_CPP

#include "picture.h"
#include "typedef.h"

class TPicClass	{
public:
	int Layers;              // k�pek sz�ma az objektumban
	TPicture *Pic;           // k�p t�mb mutat�ja
	TPicClass();
	~TPicClass();
	int Load( char *Fname , ... );   // bet�lt�s list�r�l
	int Load( char *Arg[] );         // bet�lt�s string t�mbb�l
	BOOL GetRect( int Id , RECT &Rect  );
	BOOL Draw( int Id , int x , int y );
};

#endif // _PICCLASS_CPP