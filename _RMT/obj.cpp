/*******************************************************************************
			obj.cpp
******************************************************************************/
#include <stdlib.h>
#ifndef __OBJ_CPP
	#define __OBJ_CPP
// az alap rendszer leírása és kezelõi

#include "typedef.cpp"
#include "error.cpp"
// rendszer ciklus üzenetek:
#define MC_KILL 1
#define MC_EXIT 2
// játékos üzenetek:
#define MSG_EXIT 	101
#define MSG_CRASH 102
#define MSG_BONUS 103
// speciális címzettek:
#define LOOP     (long)NULL
#define BROADCAST  0xFFFFL
class TObj;
// üzenet struktúra
struct MSG	{
	void * 				Adr;
	unsigned      Command;
	unsigned long 	Lparam;
	unsigned long 	Wparam;
	MSG * Next;
};
#define TOWp(a) ((unsigned long)(a))
#define TOLp(a) ((unsigned long)(a))
// a megszüntetés módja:
typedef enum OBJTYPE{ STATIC , DINAMIC  };
class TLoop	{
protected:
	static TObj *ObjList;                  // objektumok listája
private:
	static MSG *MsgList;                   // üzenet lista
	static BOOL ExitFlag;                  // kilépõ kapu
	static BOOL Exist(TObj *);             // létezés vizsgálat
	static TObj *ObjListEnd();             // a lista legutoésó eleme
	static TObj *ObjFindPrev(TObj *otag);  // az elem elõzõ lista eleme
	static void ObjInsert(TObj *newtag);   // lista elem beszúrása
	static int General();                  // rendszer feldatok elvégzése
public:
	void Register();                       // regisztrálás a rendszerciklusba
	// üzenet küldése:
	void SendMessage( 	void * Adr , unsigned Msg , unsigned long Lparam , unsigned long Wparam );
	// rendszerciklus indítása:
	static int Start();
};
TObj *	TLoop::ObjList	=	NULL;
MSG  *	TLoop::MsgList	=	NULL;
BOOL 		TLoop::ExitFlag= 	FALSE;
//-----------------------------------------------------------------------------
class TObj :public TLoop	{
	OBJTYPE Type;
public:
	OBJTYPE GetType(){ return Type; };
	virtual void Proc()  {};
	virtual void MsgProc ( 	void * Adr , unsigned Msg , unsigned long Lparam , unsigned long Wparam ){};
	TObj *Next;
	TObj( OBJTYPE iType=STATIC )	{
		Next=NULL ;
		Type=iType ;
	};
	virtual ~TObj(){ ; };
};
//*****************************************************************************
TObj *TLoop::ObjListEnd()
{
	TObj *Head=ObjList;
	while ( Head->Next!=NULL )
		Head=Head->Next;
	return Head;
};
//*****************************************************************************
void TLoop::ObjInsert(TObj *newtag)
{
	if ( ObjList )
		(ObjListEnd()->Next=newtag)->Next=NULL;
	else
		(ObjList=newtag)->Next=NULL;
};
//*****************************************************************************
TObj* TLoop::ObjFindPrev(TObj *otag)	{
	TObj *Head=ObjList;
	while ( Head->Next!=otag )
		Head=Head->Next;
	return Head;
};
//*****************************************************************************
BOOL TLoop::Exist(TObj *NewObj)	{
	TObj *Head=ObjList;
	while ( Head )	{
		if ( Head==NewObj ) return TRUE;;
		Head=Head->Next;
	}
	return FALSE;
};
//*****************************************************************************
void TLoop::Register(){
	ObjInsert( (TObj *)this );
};
//*****************************************************************************
void TLoop::SendMessage( void * Adr , unsigned Msg , unsigned long Lparam , unsigned long Wparam )	{
	register MSG *Puff=MsgList;
	MsgList= new MSG ;
	MsgList->Adr=Adr;
	MsgList->Command=Msg;
	MsgList->Lparam=Lparam;
	MsgList->Wparam=Wparam;
	MsgList->Next=Puff;
};
//*****************************************************************************
int TLoop::General()	{
	while ( MsgList )	{
		register MSG *Puff=MsgList;
		MsgList=MsgList->Next;

		switch ( (long)Puff->Adr )	{
			case LOOP:	{
				switch ( Puff->Command )	{
					// objektum eltávolítása:
					case MC_KILL:	{
						if ( Exist((TObj *)Puff->Lparam) )	{
							((TObj *)Puff->Lparam)->MsgProc((TObj *)Puff->Lparam , MSG_EXIT , 0  , 0 );
							if ( ObjList==(TObj *)Puff->Lparam ) ObjList=((TObj *)Puff->Lparam)->Next;
							else ObjFindPrev((TObj *)Puff->Lparam)->Next=((TObj *)Puff->Lparam)->Next;
							delete ((TObj *)Puff->Lparam);
						}
					}	break;
					// rendszer vége:
					case MC_EXIT:	{
							int ret=int(Puff->Lparam);
							while ( ObjList )	{   // lista elemeinek megszüntetése
								register TObj *Process=ObjList->Next;
								ObjList->MsgProc( ObjList , MSG_EXIT , 0  , 0 );
								if ( ObjList->GetType()==DINAMIC )	{
									delete ObjList;
								}
								ObjList=Process;
							};
							ExitFlag=TRUE;      // kapu kinyit
							while ( MsgList )	{
								 register MSG *MPuff=MsgList->Next;
								 delete MsgList;
								 MsgList=MPuff;
							}
							delete Puff;
							return ret;          // kilépõ kód
					}
				}
			}	break;
			case BROADCAST	:	{              // üzenet minden objektumnak
				register TObj *TOPuff=ObjList;
				while	(	TOPuff  )	{
					TOPuff->MsgProc( Puff->Adr , Puff->Command , Puff->Lparam , Puff->Wparam );
					TOPuff=TOPuff->Next;
				}
			}	break;
			default :                       // üzenet a címzettnek
				if ( Exist((TObj *)Puff->Adr) )
				((TObj *)Puff->Adr)->MsgProc( Puff->Adr , Puff->Command , Puff->Lparam , Puff->Wparam );
		}
		delete Puff;
	}
	return 0;
}
//*****************************************************************************
int TLoop::Start()	{
	int ret=0;
	while ( !ExitFlag )	{
		register TObj *PProc=ObjList;
		while ( PProc )	{
			PProc->Proc();            // objektum fut
			PProc=PProc->Next;        // következõ objektum
		}
		ret=General();               // rendszerfeladatok elvégzése
	}
	ExitFlag=FALSE;
	return ret;
};
//---****---------*********-------*********---------**********---------********-
// néhány hasznos makró:
#define ExitLoop(A) TLoop::SendMessage( LOOP, MC_EXIT, (unsigned long)A , 0 );
#define KillMe()   TLoop::SendMessage( LOOP, MC_KILL, (unsigned long)this, 0 );
#endif // _OBJ_CPP
