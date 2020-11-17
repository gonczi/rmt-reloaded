#ifndef _MENU_CPP
	#define _MENU_CPP

// #include <string.h>
// #include "typedef.h"
// #include "globals.cpp"
#include "timer.h"
#include "obj.h"
// #include "bmp.cpp"
// #include "pic_serv.cpp"
// #include "scancode.cpp"
#include "mymouse.h"
#include "consol.h"
// #include "usr.h"
// #include "TIMER.CPP"
#include "button.h"

enum TMenuType{ MT_MAIN , MT_CONTROL , MT_EXIT , MT_NAME ,
								MT_TOP5 , MT_CLEAR };

class TMenu : TLoop , TTimer	{
public:
	int LastCount;
	TMyMouse *MyMouse;
	int PLevel;
	TConsol *Con;
	static char Text[256];
	static char DrawText[256];
	char * TextBack,* TB2;              // �ltal�nos k�p h�tt�r pufferek
	int TextShift;                      // aktu�lis sz�veg k�p eltol�s
	BOOL TextLineMove;                  // a f�nyrekl�m bekapcsolt �llapot�t jelz�
	void DarkScr();                     // s�t�t�tett h�tt�r
	RECT CurRect[7];
	int ActiveLine;
	TButton * * Buttons;                // az aktu�lis men� elem lista
	TButton *ActiveButton;              // az akt�v men�elem
	BOOL MCLICKON;                      // igaz ha volt m�r ki�rt�kelt eg�r gomb lenyom�s
	BOOL MenuExit;                      // a men� f� ciklus�nak kapuja
	void InitList( TMenuType );
	void ChangeMode( TMenuType );       // men� v�lt�s
	TMenuType MenuMode;                 // aktu�li men�
	void Event( int Hand );             // esem�ny �rtelmez�
	void MoveLine();                    // f�nyrekl�m l�ptet�

	TMenu(  int iPLevel  );                       // arg: p�lya azonos�t�
};

#endif //_MENU_CPP


