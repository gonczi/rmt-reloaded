#ifndef _PIC_SERV_CPP
	#define _PIC_SERV_CPP

#include "typedef.h"
#include "picclass.h"
#include "picfiles.h"

class PicServer	{                           //  a k�p kiszolg�l�
public:
	static void FreeAll();                     // minden bet�lt�tt k�p t�rl�se
	static void * GetPic( int Id );        // k�p bet�lt�se
	static TMainPicType GetType( int iId );    // k�p t�pus�nak lek�r�se
	static int Free( int iId );                // k�p t�rl�se
	static void FreeDirect( int iId );         // k�p ideiglenes t�rl�se a mem�ri�b�l
	static void LoadPicDirect( int iId ) ;     // az ideiglenesen t�r�lt k�p visszat�lt�se
};

#endif // _PIC_SERV_CPP
