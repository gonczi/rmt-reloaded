#ifndef _MAP_CPP
	#define _MAP_CPP

#include "typedef.h"
#include "timer.h"

class TMap : TTimer	{
	RECT Rect;                       // a t�rk�p m�rete
	POINT Poz;                       // pozici�ja a k�perny�n
	void PutSign( POINT Poz , BYTE Color ); // kirak egy pontot a szektor k�zep�be
public:
	TMap();
	void Show( POINT MPoz , float MAlfa ); // kirajzolja a t�rk�pet
} ;

#endif // _MAP_CPP
