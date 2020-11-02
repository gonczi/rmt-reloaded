#include "typedef.h"

long absl( long Num )	{       // abszolut �rt�k long t�pusra
	return (Num<0)?(-Num):Num;
}

float absf( float Num )	{       // abszolut �rt�k float t�pusra
	return (Num<0.0)?(-Num):Num;
}

float norm( float beta )	{    // pozit�v �rt�k sz�gekre radi�nban
	return ( beta < 0.0 ) ? beta+(2*M_PI) : beta;
}

//*********************************************** SPECI�LIS OPER�TOROK

POINT operator +( POINT p1 , POINT p2 )	{
	return POINT( p1.x+p2.x , p1.y+p2.y );
}

POINT operator +( POINT p , RECT r )	{
	return POINT( p.x+r.Sx , p.y+r.Sy );
}

POINT POINT::operator =( POINT p2 )	{
	return POINT( x=p2.x , y=p2.y );
}

float POINT::operator !()	{       // egy pont orig�hoz k�pesti sz�ge rad.-ban
	return norm((x)?(atan(float(y)/float(x))+((x<0)*M_PI)):((y>0)?M_PI/2:M_PI*1.5));
};

POINT operator +=( POINT &p1 , POINT p2 )	{
	return POINT( p1.x+=p2.x , p1.y+=p2.y );
}

POINT operator -( POINT p1 , POINT p2 )	{
	return POINT( p1.x-p2.x , p1.y-p2.y );
}

float operator /( POINT p1 , POINT p2 )	{
	register float Dx=(p1.x)-(p2.x);
	register float Dy=(p1.y)-(p2.y);
	return sqrt(Dx*Dx+Dy*Dy);
}

float operator %( POINT p1 , POINT p2 )	{
	return !(p2-p1);
}


RECT operator +( RECT p1 , RECT p2 )	{
	return RECT( p1.Sx+p2.Sx , p1.Sy+p2.Sy );
}

RECT RECT::operator =( RECT p2 )	{
	return RECT( Sx=p2.Sx , Sy=p2.Sy );
}

RECT operator +=( RECT &p1 , RECT p2 )	{
	return RECT( p1.Sx+=p2.Sx , p1.Sy+=p2.Sy );
}

RECT operator /( RECT p1 , int m )	{
	return RECT( p1.Sx/m , p1.Sy/m );
}
