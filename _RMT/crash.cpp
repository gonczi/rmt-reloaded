/*******************************************************************************
				crash.cpp
*******************************************************************************/
#ifndef _CRASH_CPP
	#define _CRASH_CPP
// ütközések figyelése a pályán
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
						// üzenet küldése a két ütközésben lévõ félnek
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
