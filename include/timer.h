#ifndef _TIMER_CPP
# define _TIMER_CPP

#include "typedef.h"

#define  CALL_NORMAL_TPROC  0   	// oszt�lyon k�v�li f�ggv�ny h�v�s k�relme
											// nem implement�lt
#define  CALL_PROC  1            // TimerProc h�v�sa
#define  INC_COUNT   2           // sz�ml�l� n�vel�se

//-----------------------------------------------------------------------------
//    a timer proc fut�sa alatt nem h�hat�:            !!!
//		DelTimer
//		SetTimer
class TTimer	
{
public:
	virtual void TimerProc( int Id ){ ; };     // absztrakt f�ggv�ny
	int Count;                                 // sz�ml�l�
	BOOL SetTimer( int Id ,int Mode  ,  int Count  );  // �j id�z�t�s ind�t�sa
	BOOL DelTimer( int Id  );                          // id�z�t� v�ge
};

#endif //_TIMER_CPP
