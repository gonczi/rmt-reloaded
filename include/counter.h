#ifndef _COUNTER_CPP
	#define _COUNTER_CPP

#include "number.h"
#include "timer.h"
#include "scrobj.h"

class TCounter	:TTimer 	{
	int MNum;                            // a kijelz�n megjelen� sz�m
	BOOL Visible;
	int Step;                            // h�tt�r k�p be�sz�si temp�ja
	TNumber * Num_100;                   // sz�mjegyek ...
	TNumber * Num_10;
	TNumber * Num_1;
	TScrObj * BackPic;                   // h�tt�r k�p
public:
	TCounter( int iId );
	~TCounter();
	void Show( int );
	void Hide();
	void Set( int Num );                  // friss�t�s
	virtual void TimerProc( int );
};

#endif // _COUNTER_CPP
