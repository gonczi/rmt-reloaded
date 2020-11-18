#include "crash.h"
#include "motor.h"

//******************************************************************************
TCrash::TCrash() : TObj( DINAMIC )	{
	Register();
}
//******************************************************************************
void TCrash::Proc()	{
	TGrObjList *Puff=GrObjList;
	while ( Puff )	{
		register int Id;
		if ( (Id=Puff->GrObj->Cast) != GR_NOBODY )	{
			TGrObjList *PSecond=Puff->Next;
			while ( PSecond )	{
				register int SId;
				if ( ((SId=PSecond->GrObj->Cast)!=NOBODY) && (Id!=SId) )
					if ( GetDR(Puff->GrObj,PSecond->GrObj) < CRASHMIN )	{
						// �zenet k�ld�se a k�t �tk�z�sben l�v� f�lnek
						SendMessage( Puff->GrObj , MSG_CRASH , TOLp(PSecond->GrObj) ,
							TOWp(PSecond->GrObj->Name) );
						SendMessage( PSecond->GrObj , MSG_CRASH , TOLp(Puff->GrObj) ,
							TOWp(Puff->GrObj->Name) );
					}
				PSecond=PSecond->Next;
			}
		};
		Puff=Puff->Next;
	}
};

