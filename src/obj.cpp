#include "obj.h"

#include <stdlib.h>
#include <unistd.h>

TObj *	TLoop::ObjList	=	NULL;
MSG  *	TLoop::MsgList	=	NULL;
BOOL 		TLoop::ExitFlag= 	FALSE;

TObj::TObj( OBJTYPE iType )	{
	Next=NULL ;
	Type=iType ;
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
					// objektum elt�vol�t�sa:
					case MC_KILL:	{
						if ( Exist((TObj *)Puff->Lparam) )	{
							((TObj *)Puff->Lparam)->MsgProc((TObj *)Puff->Lparam , MSG_EXIT , 0  , 0 );
							if ( ObjList==(TObj *)Puff->Lparam ) ObjList=((TObj *)Puff->Lparam)->Next;
							else ObjFindPrev((TObj *)Puff->Lparam)->Next=((TObj *)Puff->Lparam)->Next;
							delete ((TObj *)Puff->Lparam);
						}
					}	break;
					// rendszer v�ge:
					case MC_EXIT:	{
							int ret=int(Puff->Lparam);
							while ( ObjList )	{   // lista elemeinek megsz�ntet�se
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
							return ret;          // kil�p� k�d
					}
				}
			}	break;
			case BROADCAST	:	{              // �zenet minden objektumnak
				register TObj *TOPuff=ObjList;
				while	(	TOPuff  )	{
					TOPuff->MsgProc( Puff->Adr , Puff->Command , Puff->Lparam , Puff->Wparam );
					TOPuff=TOPuff->Next;
				}
			}	break;
			default :                       // �zenet a c�mzettnek
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
			usleep(5000);
			PProc->Proc();            // objektum fut
			PProc=PProc->Next;        // k�vetkez� objektum
		}
		ret=General();               // rendszerfeladatok elv�gz�se
	}
	ExitFlag=FALSE;
	return ret;
};
//---****---------*********-------*********---------**********---------********-
