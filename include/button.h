#ifndef _BUTTON_CPP
	#define _BUTTON_CPP

#include "picclass.h"

enum ButtId{ ID_NULL=1 , ID_NEW , ID_CON , ID_EXI , ID_YES , ID_NO ,
						 ID_FORW , ID_BACK , ID_TLEFT , ID_TRIGHT ,ID_LEFT ,
						 ID_RIGHT , ID_FIRE ,
						 ID_BACKM , ID_START , ID_TOP5 };

// gomb t�pus:
enum BUTT_TYPE{ BT_BUTTON , BT_SHAPE };

class TShape	{           // egy k�p a k�perny�n
protected:
	int Id;                 // azonos�t�
	POINT Poz;              // pozici� a k�perny�n
	RECT Rect;              // m�retei
	char *BackGr;           // h�tt�r
	TPicClass *Pic;         // a hozz� tartoz� k�p
public:
	BUTT_TYPE Type;         // t�pus
	BOOL ActiveOn;          // TRUE ha a f�kusz az objektumon van
	TShape( POINT , int , BUTT_TYPE );
	~TShape(){ Free(); };
	void Show( int iLayer );
	void Hide();
	void Load();            // k�p bet�lt�se
	void Free();
};

class TButton : public TShape	{   // gomb
	BOOL Hideing;
public:
	ButtId Handler;                // azonos�t�
	TButton( BUTT_TYPE , POINT , ButtId , int  , BOOL iHide=TRUE );
	void Active( BOOL Direct=FALSE , BOOL Selected=FALSE );    // a gombra helyezi a f�kuszt grafikusan
	BOOL OnCoords( POINT iPoz );   // meg�llap�tja hogy az adott koordin�ta a gomb ter�let�n van e
};

#endif // _BUTTON_CPP
