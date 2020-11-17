#ifndef _PICTURE_CPP
	#define _PICTURE_CPP

#include <stddef.h>

class Pic_Vector	{       // egy vektor le�r� rekordja
public:
	int Sp,Ep;             // kezd�pont, v�gpont
	int Len;               // hossz
	char *Start;           // adatok kezd� c�me
	Pic_Vector()	{       // konstruktor
		Sp=Ep=Len=0;
		Start=NULL;
	}
};
class Pic_Row	{          // egy oszlop le�r� rekordja
public:
	int Num;               // vektorok sz�ma az oszlopban
	Pic_Vector *Vector;    // a vektor t�mb els� elem�nek c�me
	Pic_Row();
	~Pic_Row();
};
//-----------------------------------------------------------------------------
class TPicture	{
	char *Data;            // a teljes k�p adatainak mem�ria t�mbje
public:
	Pic_Row *Row;          // oszlop t�mb kez� c�me
	int X,Y;               // k�p m�retei
	TPicture();
	~TPicture() ;
	int Load( const char *Fname );     //  bet�lt�s
	void Draw( int x , int y );  // kirajzol
};

#endif	//PICTURE
