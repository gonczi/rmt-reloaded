#ifndef _MY_TYPES
	#define _MY_TYPES

// some common typedefinition and their functions

#include <math.h>

long absl( long Num );
float absf( float Num );
float norm( float beta );

// typedef enum BOOL{	FALSE=0 , TRUE=1	};
#define BOOL bool
#define TRUE true
#define FALSE false

typedef unsigned char BYTE;

//*************************************************************** POINT

class POINT 
{
public:
	int x,y;
	POINT() { x=y=0; };
	POINT( int ix , int iy ) { x=ix; y=iy; };
	POINT operator =( POINT p2 );
	float operator !();
};

POINT operator +( POINT p1 , POINT p2 );
POINT operator +=( POINT &p1 , POINT p2 );
POINT operator -( POINT p1 , POINT p2 );
float operator /( POINT p1 , POINT p2 );
float operator %( POINT p1 , POINT p2 );

//*************************************************************** RECT

class RECT
{
public:
	int Sx,Sy;
	RECT() { Sx=Sy=0; };
	RECT( int ix , int iy ) { Sx=ix; Sy=iy; };
	RECT operator =( RECT p2 );
};

RECT operator +( RECT p1 , RECT p2 );
RECT operator +=( RECT &p1 , RECT p2 );
RECT operator /( RECT p1 , int m );

POINT operator +( POINT p , RECT r );

#endif //_MY_TYPES
