#ifndef _MYMOUSE_CPP
	#define _MYMOUSE_CPP

#include "timer.h"
#include "picclass.h"

#define SHAPE 3  //     a k�pek sz�ma az anim�ci�ban

class TMyMouse : TTimer	{
	BOOL Drawing;
	char *FCurName[SHAPE];     // k�p f�jlok nevei
	BOOL CURDIR,Visible ;
	TPicClass *Cur;            // a k�peket tertalmaz� obj
	int Count;                 // id�z�t� sz�ml�l�
	char *CurBackGr;           // kurzor h�ttere
	RECT CurRect;              // m�retei
	int Clx,Cly;               // a legut�bbi kurzor pozici�
	void Draw();
	void Clear();
public:
	TMyMouse();
	~TMyMouse();
	virtual void  TimerProc( int Id );
	int Mx,My;
	void Show();
	void Hide();
};

#endif // _MYMOUSE_CPP
