#include "timer.h"

#ifdef __cplusplus
	 #define __CPPARGS ...
#else
	 #define __CPPARGS
#endif

#define PROC_ON  Not_RuningNow=FALSE;   // megszak�t�s maszk bekapcsolva
#define PROC_OFF Not_RuningNow=TRUE;    // megszak�t�s maszk megsz�ntetve

#include <stddef.h>
// #include <dos.h>
// #define TMR_INT 0X1C   // az �ra megszak�t�s k�dja

// void interrupt ( *_OldInterrupt)(__CPPARGS);  // eredeti �ra megszak�t�si vektor
// void interrupt _Interrupt(__CPPARGS);         // az �j

// BOOL Not_RuningNow=TRUE;                      // megszak�t�s masz jelz� b�jtja

// class TTimer;
// // h�v�s nyilv�ntart� l�nc eleme:
// struct TProc	{
// 	int Id;            // aktiv�l�s azonos�t�ja
// 	int Count;         // id�z�t�k�sleltet�s
// 	int Limit;         // id�z�t�k�sleltet�s null�z�s�nak l�p�s sz�ma
// 	int Mode;          // h�v�s m�dja
// 	union 	{
// 		void (*Proc)();   // a h�vott f�ggv�ny c�me
// 		TTimer  * PObj;   // ua. csak a f�ggv�ny oszt�ly tag
// 	};
// 	TProc *Next;         // k�vetlez� lista elem
// } *_TimerProc_List_Head=NULL;  // a lista feje
//

BOOL TTimer::SetTimer( int Id ,  int Mode  ,  int Count  )	
{
	// PROC_ON;
	BOOL ret=TRUE;                            // besz�r�s list�ba
	// if ( Count>0 )	{
	// 	if ( _TimerProc_List_Head==NULL )	{
	// 		_TimerProc_List_Head			=	new TProc;
	// 		_TimerProc_List_Head->PObj	=	this;
	// 		_TimerProc_List_Head->Id	=  Id;
	// 		_TimerProc_List_Head->Count=	1;
	// 		_TimerProc_List_Head->Limit=	Count;
	// 		_TimerProc_List_Head->Next	=	NULL;
	// 		_TimerProc_List_Head->Mode =  Mode;
	// 	}	else	{
	// 			register TProc *Now=_TimerProc_List_Head;
	// 			while ( Now->Next )	Now=Now->Next;
	// 			Now=Now->Next	=	new TProc;
	// 			Now->PObj		=	this;
	// 			Now->Id			=  Id;
	// 			Now->Count		=	1;
	// 			Now->Limit		=	Count;
	// 			Now->Next		=	NULL;
	// 			Now->Mode      =  Mode;
	// 		};
	// }	else	ret=FALSE;
	// PROC_OFF;
	return ret;
};

BOOL TTimer::DelTimer( int Id )	
{
	// PROC_ON;                               // kivesz a list�b�l
	BOOL ret=FALSE;
	// if ( _TimerProc_List_Head  )	{
	// 	register TProc *Now=_TimerProc_List_Head;
	// 	if ( (_TimerProc_List_Head->PObj==this) && (_TimerProc_List_Head->Id==Id) )	{
	// 		_TimerProc_List_Head=_TimerProc_List_Head->Next;
	// 		delete Now;
	// 	}	else	{
	// 			while ( Now->Next )	{
	// 				if ( ( Now->Next->PObj==this ) && ( Now->Next->Id==Id ) )	{
	// 					register TProc *Puff=Now->Next;
	// 					Now->Next=Puff->Next;
	// 					delete Puff;
	// 					break;
	// 				};
	// 				Now=Now->Next;
	// 			}
	// 		};
	// 	ret=TRUE;
	// };
	// PROC_OFF;
	return ret;
};

// void interrupt _Interrupt(__CPPARGS)	{    // az �j megszak�t�s k�dja:
// 	if ( Not_RuningNow )	{
// 		PROC_ON;
// 		register TProc *Calling=_TimerProc_List_Head;
// 		while ( Calling )	{
// 			if ( (Calling->Count++)==(Calling->Limit) )	{
// 				if ( Calling->Mode )	{
// 					register TTimer * PObj=Calling->PObj;
// 					if ( Calling->Mode==INC_COUNT )	{
// 						PObj->Count++;
// 					}	else	if ( Calling->Mode==CALL_PROC )	{
// 							PObj->TimerProc( Calling->Id );
// 						}
// 				}	else	{
// 						Calling->Proc();
// 				}
// 				Calling->Count=1;
// 			};
// 			Calling=Calling->Next;
// 		}
// 		PROC_OFF;
// 	}
//   _OldInterrupt();
// }

// extern BOOL Timer_Installed=FALSE;
// // az id�z�t� telep�t�se
// void InstallTimer()	{
// 	if ( !Timer_Installed )	{
// 		_OldInterrupt= getvect( TMR_INT );
// 		setvect( TMR_INT , _Interrupt );
// 		Timer_Installed=TRUE;
// 	};
// };
// // a teljes lista t�rl�se
// void FlushTimer()	{
// 	while	( _TimerProc_List_Head    )	{
// 		register TProc *Puff=_TimerProc_List_Head->Next;
// 		delete _TimerProc_List_Head;
// 		_TimerProc_List_Head=Puff;
// 	}
// }
// // az id�z�t� alrendszer elt�vol�t�sa
// void ResumeTimer()	{
// 	if ( Timer_Installed  )	{
// 		setvect( TMR_INT , _OldInterrupt);
// 		FlushTimer();
// 		Timer_Installed=FALSE;
// 	};
// };
