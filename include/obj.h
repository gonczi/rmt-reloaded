#include <stdlib.h>
#ifndef __OBJ_CPP
	#define __OBJ_CPP

#include "typedef.h"
#include "error.h"

#define MC_KILL 1
#define MC_EXIT 2

#define MSG_EXIT 	101
#define MSG_CRASH 102
#define MSG_BONUS 103

#define LOOP     (long)NULL
#define BROADCAST  0xFFFFL

class TObj;

struct MSG	{
	void * 				Adr;
	unsigned      Command;
	unsigned long 	Lparam;
	unsigned long 	Wparam;
	MSG * Next;
};

#define TOWp(a) ((unsigned long)(a))
#define TOLp(a) ((unsigned long)(a))

enum OBJTYPE{ STATIC , DINAMIC  };

class TLoop	{
protected:
	static TObj *ObjList;                  // objektumok list�ja
private:
	static MSG *MsgList;                   // �zenet lista
	static BOOL ExitFlag;                  // kil�p� kapu
	static BOOL Exist(TObj *);             // l�tez�s vizsg�lat
	static TObj *ObjListEnd();             // a lista leguto�s� eleme
	static TObj *ObjFindPrev(TObj *otag);  // az elem el�z� lista eleme
	static void ObjInsert(TObj *newtag);   // lista elem besz�r�sa
	static int General();                  // rendszer feldatok elv�gz�se
public:
	void Register();                       // regisztr�l�s a rendszerciklusba
	// �zenet k�ld�se:
	void SendMessage( 	void * Adr , unsigned Msg , unsigned long Lparam , unsigned long Wparam );
	// rendszerciklus ind�t�sa:
	static int Start();
};

class TObj :public TLoop	{
	OBJTYPE Type;
public:
	OBJTYPE GetType(){ return Type; };
	virtual void Proc()  {};
	virtual void MsgProc ( 	void * Adr , unsigned Msg , unsigned long Lparam , unsigned long Wparam ){};
	TObj *Next;
	TObj( OBJTYPE iType=STATIC );
	virtual ~TObj(){ ; };
};

#define ExitLoop(A) TLoop::SendMessage( LOOP, MC_EXIT, (unsigned long)A , 0 );
#define KillMe()   TLoop::SendMessage( LOOP, MC_KILL, (unsigned long)this, 0 );

#endif // _OBJ_CPP
