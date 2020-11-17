#ifndef _NUMBER_CPP
	#define _NUMBER_CPP

#include "scrobj.h"
#include "pic_serv.h"

class TNumber/*:protected TObj  */	{
protected :
	int Number;                            // sz�mjegy
	POINT *Poz;                            // pozici� bal fels� sarok
	TScrObj *Tick[7];                      // vonalk�k
public :
	TNumber( int iNum ,  int Px , int Py );
	~TNumber();
	void Show();
	void Hide();
	void Set( int iNum );                  // friss�t�s
};

//******************************************************************************

#endif // _NUMBER_CPP
