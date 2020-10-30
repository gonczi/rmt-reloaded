#ifndef _AnimObj_CPP
	#define _AnimObj_CPP
//

#include "grobj.cpp"
#include "timer.cpp"
#include "Pic_Load.cpp"

class TAnimObj:public TGrObj,protected TTimer	{
protected:
	TPicClass *PicClass;
public:
	TAnimObj();
	virtual ~TAnimObj();
	virtual void TimerProc( int Id );
	virtual void Proc();
	virtual void Init(	TPicClass *iPicClass ,
								int Sx ,
								int Sy ,
								int iFx ,
								int iFy );
	int Tick;
	int u;
	int Count;
};

int z=0;

TAnimObj::TAnimObj():	TTimer() , TGrObj()	{
	Tick=2;
	SetTimer( 1 , CALL_PROC , Tick  );
	Register();
	GrRegister();
	u=z++ ;
	Count=0;
};

void TAnimObj::Init(	TPicClass *iPicClass ,
							int Sx ,
							int Sy ,
							int iFx ,
							int iFy )	{
	PicClass = iPicClass;
	TGrObj::Init(	Sx ,Sy , iFx , iFy , iPicClass ? iPicClass->Pic[0] : NULL );
};


TAnimObj::~TAnimObj()	{
	GrDelete();
	DelTimer( 1 );
}

void TAnimObj::TimerProc( int Id )	{
	if ( ++Count >=(PicClass->Layers) ) Count=0;
};

void TAnimObj::Proc()	{
	Pic=PicClass->Pic[Count];
};

#endif // _AnimObj_CPP
