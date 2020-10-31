/******************************************************************************
				timer.cpp
******************************************************************************/
#ifndef _TIMER_CPP
	#define _TIMER_CPP
// az idõzítõ alrendszer definiálása , és kezelõ függvényei
#include "typedef.cpp"
#include <stddef.h>
#include <dos.h>
#define TMR_INT 0X1C   // az óra megszakítás kódja

#define  CALL_NORMAL_TPROC  0   	// osztályon kívüli függvény hívás kérelme
											// nem implementált
#define  CALL_PROC  1            // TimerProc hívása
#define  INC_COUNT   2           // számláló növelése

#ifdef __cplusplus
	 #define __CPPARGS ...
#else
	 #define __CPPARGS
#endif

#define PROC_ON  Not_RuningNow=FALSE;   // megszakítás maszk bekapcsolva
#define PROC_OFF Not_RuningNow=TRUE;    // megszakítás maszk megszüntetve
class TTimer;
// hívás nyilvántartó lánc eleme:
struct TProc	{
	int Id;            // aktiválás azonosítója
	int Count;         // idõzítõkésleltetés
	int Limit;         // idõzítõkésleltetés nullázásának lépés száma
	int Mode;          // hívás módja
	union 	{
		void (*Proc)();   // a hívott függvény címe
		TTimer  * PObj;   // ua. csak a függvény osztály tag
	};
	TProc *Next;         // követlezõ lista elem
} *_TimerProc_List_Head=NULL;  // a lista feje

void interrupt ( *_OldInterrupt)(__CPPARGS);  // eredeti óra megszakítási vektor
void interrupt _Interrupt(__CPPARGS);         // az új

BOOL Not_RuningNow=TRUE;                      // megszakítás masz jelzõ bájtja

//-----------------------------------------------------------------------------
//    a timer proc futása alatt nem híható:            !!!
//		DelTimer
//		SetTimer
class TTimer	{
public:
	virtual void TimerProc( int Id ){ ; };     // absztrakt függvény
	int Count;                                 // számláló
	BOOL SetTimer( int Id ,int Mode  ,  int Count  );  // új idõzítés indítása
	BOOL DelTimer( int Id  );                          // idõzítõ vége
};
//------------------------------------------
BOOL TTimer::SetTimer( int Id ,  int Mode  ,  int Count  )	{
	PROC_ON;
	BOOL ret=TRUE;                            // beszúrás listába
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
	PROC_OFF;
	return ret;
};
//----------------------------------------- TTimer:
BOOL TTimer::DelTimer( int Id )	{
	PROC_ON;                               // kivesz a listából
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
	PROC_OFF;
	return ret;
};

//*****************************************************************************

void interrupt _Interrupt(__CPPARGS)	{    // az új megszakítás kódja:
	if ( Not_RuningNow )	{
		PROC_ON;
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
		PROC_OFF;
	}
  _OldInterrupt();
}
//*****************************************************************************
extern BOOL Timer_Installed=FALSE;
// az idõzítõ telepítése
void InstallTimer()	{
	if ( !Timer_Installed )	{
		_OldInterrupt= getvect( TMR_INT );
		setvect( TMR_INT , _Interrupt );
		Timer_Installed=TRUE;
	};
};
// a teljes lista törlése
void FlushTimer()	{
	while	( _TimerProc_List_Head    )	{
		register TProc *Puff=_TimerProc_List_Head->Next;
		delete _TimerProc_List_Head;
		_TimerProc_List_Head=Puff;
	}
}
// az idõzítõ alrendszer eltávolítása
void ResumeTimer()	{
	if ( Timer_Installed  )	{
		setvect( TMR_INT , _OldInterrupt);
		FlushTimer();
		Timer_Installed=FALSE;
	};
};
#endif //_TIMER_CPP
