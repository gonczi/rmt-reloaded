#include "timer.h"

#include <thread>
#include <unistd.h>

using namespace std;

#include <stddef.h>

bool timerTaskRun = true;
thread *timerTaskThread = NULL;

class TTimer;
// h�v�s nyilv�ntart� l�nc eleme:
struct TProc	{
	int Id;            // aktiv�l�s azonos�t�ja
	int Count;         // id�z�t�k�sleltet�s
	int Limit;         // id�z�t�k�sleltet�s null�z�s�nak l�p�s sz�ma
	int Mode;          // h�v�s m�dja
	union 	{
		void (*Proc)();   // a h�vott f�ggv�ny c�me
		TTimer  * PObj;   // ua. csak a f�ggv�ny oszt�ly tag
	};
	TProc *Next;         // k�vetlez� lista elem
} *_TimerProc_List_Head=NULL;  // a lista feje


BOOL TTimer::SetTimer( int Id ,  int Mode  ,  int Count  )	
{
	BOOL ret=TRUE;                            // besz�r�s list�ba
	if ( Count>0 )	{
		if ( _TimerProc_List_Head==NULL )	{
			_TimerProc_List_Head			=	new TProc;
			_TimerProc_List_Head->PObj	=	this;
			_TimerProc_List_Head->Id	=  Id;
			_TimerProc_List_Head->Count=	1;
			_TimerProc_List_Head->Limit=	Count;
			_TimerProc_List_Head->Next	=	NULL;
			_TimerProc_List_Head->Mode =  Mode;
		}	else	{
				register TProc *Now=_TimerProc_List_Head;
				while ( Now->Next )	Now=Now->Next;
				Now=Now->Next	=	new TProc;
				Now->PObj		=	this;
				Now->Id			=  Id;
				Now->Count		=	1;
				Now->Limit		=	Count;
				Now->Next		=	NULL;
				Now->Mode      =  Mode;
			};
	}	else	ret=FALSE;
	return ret;
};

BOOL TTimer::DelTimer( int Id )	
{
	BOOL ret=FALSE;
	if ( _TimerProc_List_Head  )	{
		register TProc *Now=_TimerProc_List_Head;
		if ( (_TimerProc_List_Head->PObj==this) && (_TimerProc_List_Head->Id==Id) )	{
			_TimerProc_List_Head=_TimerProc_List_Head->Next;
			delete Now;
		}	else	{
				while ( Now->Next )	{
					if ( ( Now->Next->PObj==this ) && ( Now->Next->Id==Id ) )	{
						register TProc *Puff=Now->Next;
						Now->Next=Puff->Next;
						delete Puff;
						break;
					};
					Now=Now->Next;
				}
			};
		ret=TRUE;
	};
	return ret;
};

void timerTask(string msg)
{
	while (timerTaskRun) {

		usleep(1000);

		register TProc *Calling=_TimerProc_List_Head;
		while ( Calling )	{
			if ( (Calling->Count++)==(Calling->Limit) )	{
				if ( Calling->Mode )	{
					register TTimer * PObj=Calling->PObj;
					if ( Calling->Mode==INC_COUNT )	{
						PObj->Count++;
					}	else	if ( Calling->Mode==CALL_PROC )	{
							PObj->TimerProc( Calling->Id );
						}
				}	else	{
						Calling->Proc();
				}
				Calling->Count=1;
			};
			Calling=Calling->Next;
		}
	}
}

void InstallTimer()	
{
	timerTaskThread = new thread(timerTask, "");
};

void FlushTimer()	
{
	while	( _TimerProc_List_Head    )	{
		register TProc *Puff=_TimerProc_List_Head->Next;
		delete _TimerProc_List_Head;
		_TimerProc_List_Head=Puff;
	}
}

void ResumeTimer()	
{	
	timerTaskRun = FALSE;
	timerTaskThread->join();
	FlushTimer();
};
