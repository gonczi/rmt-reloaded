/*******************************************************************************
			energy.cpp
*******************************************************************************/
#ifndef _ENERGY_CPP
	#define _ENERGY_CPP
// energia kijelz� Screen objektum
#include "obj.cpp"
#include "scrobj.cpp"
class TEnergy: TObj	{
	int Q;
	TScrObj *Back, *Rows;    // h�tt�r , �rt�k
	int RX;
public:
	TEnergy( POINT Poz );
	~TEnergy();
	int Add(int D);
	int GetNum() { return Rows->Pic->X; };
};
//******************************************************************************
TEnergy::TEnergy( POINT Poz )	{
	Rows=new TScrObj( 1  , TSC_EN_ROWS );
	Back=new TScrObj( 30 , TSC_EN_BACK );
	Rows->Poz=POINT( Poz.x+25 , Poz.y+6  );
	Rows->Show();
	RX = Rows->Pic->X;
	Back->Poz=Poz;
	Back->Show();
};
//******************************************************************************
TEnergy::~TEnergy()	{
	Rows->Hide();
	Back->Hide();
	delete Rows;
	delete Back;
};
//******************************************************************************
int TEnergy::Add(int D)	{
	register Ert=Rows->Pic->X+D;
	if ( Ert<=0 )
		return Rows->Pic->X=0;
	// hogyha cs�kkentem a k�p elm�leti sz�less�g�t akkor a megjelen�t� sem
	// rajzolja tov�bb �s �gy keskenyebb k�p lessz felfestve
	if ( Ert>=RX )
		return Rows->Pic->X=RX;
	return Rows->Pic->X=Ert;
};
//******************************************************************************
#endif // _ENERGY_CPP
