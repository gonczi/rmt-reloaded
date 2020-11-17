#ifndef _ScrObj_CPP
	#define _ScrObj_CPP

#include "typedef.h"
#include "pic_serv.h"

class TScrObj	{
	BOOL Registered;                  // biztons�gi regisztr�l�s jelz�
	int MId;                          // k�p azonos�t�
protected:
	void Register();
	void Delete();
public:
	int Num;                          // fed�si sorrend jelz�je
	TScrObj * Next;                   // k�vetkez� elem
	union {                           // k�p
		TPicture * Pic;
		TPicClass * PicClass;
	};
	POINT Poz;                        // pzici� a k�perny�n
	TScrObj(  int iNum , int Id );
	~TScrObj();
	void Hide()	{ if ( Registered )  Delete(); };
	void Show() { if ( !Registered ) Register(); };
};

extern TScrObj * ScrObjList;

#endif // _ScrObj_CPP
