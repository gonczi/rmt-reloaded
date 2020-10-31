/*******************************************************************************
				crash.cpp
*******************************************************************************/
#ifndef _CRASH_CPP
	#define _CRASH_CPP
// �tk�z�sek figyel�se a p�ly�n
#include "obj.cpp"
#include "grobj.cpp"
class TCrash  : TObj , TPozition	{
public:
	TCrash();
	virtual void Proc();
};
//******************************************************************************
TCrash::TCrash() : TObj( DINAMIC )	{
	Register();
}
//******************************************************************************
void TCrash::Proc()	{
	TGrObjList *Puff=GrObjList;
	while ( Puff )	{
		register Id;
		if ( (Id=Puff->GrObj->Cast) != GR_NOBODY )	{
			TGrObjList *PSecond=Puff->Next;
			while ( PSecond )	{
				register SId;
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
#endif //
