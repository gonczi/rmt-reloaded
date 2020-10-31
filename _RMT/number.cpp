/******************************************************************************
				number.cpp
*******************************************************************************/
#ifndef _NUMBER_CPP
	#define _NUMBER_CPP
// számjegy kirajzoló Screen objektum csoport
/***********************
	  111
	0     2
	0     2
	  333
	4     6
	4     6
	  555
***********************/
#include "ScrObj.cpp"
#include "pic_serv.cpp"
class TNumber/*:protected TObj  */	{
protected :
	int Number;                            // számjegy
	POINT *Poz;                            // pozició bal felsõ sarok
	TScrObj *Tick[7];                      // vonalkák
public :
	TNumber( int iNum ,  int Px , int Py );
	~TNumber();
	void Show();
	void Hide();
	void Set( int iNum );                  // frissítés
};
// a vonalkák relatív poziciója:
POINT TickPoz[ 7 ]=	{	POINT( 0 , 4  ),
								POINT( 4	, 0  ),
								POINT( 13, 4  ),
								POINT( 4 , 13	),
								POINT( 0 , 17	),
								POINT( 4 , 26	),
								POINT( 13, 17	) 		  	};
// egy számjegy leírója:
int  Numb[10][7]={	{ 1,1,1,0,1,1,1 },  // 0
							{ 0,0,1,0,0,0,1 },  // 1
							{ 0,1,1,1,1,1,0 },  // 2
							{ 0,1,1,1,0,1,1 },  // 3
							{ 1,0,1,1,0,0,1 },  // 4
							{ 1,1,0,1,0,1,1 },  // 5
							{ 1,1,0,1,1,1,1 },  // 6
							{ 0,1,1,0,0,0,1 },  // 7
							{ 1,1,1,1,1,1,1 },  // 8
							{ 1,1,1,1,0,1,1 } };// 9
//******************************************************************************
TNumber::TNumber( int iNum , int Px , int Py ){
	Number=0;
	Poz= new POINT(Px,Py);
	for ( int TSO=0 ; TSO<7 ; TSO++ )	{
		Tick[TSO]=new TScrObj( iNum , (TSO%2)?TSC_TICKH:TSC_TICKV ) ;
		Tick[TSO]->Poz.x = Poz->x + TickPoz[TSO].x;
		Tick[TSO]->Poz.y = Poz->y + TickPoz[TSO].y;
	};
}
TNumber::~TNumber(){
	Hide();
	delete Poz;
	for ( int TSO=0 ; TSO<7 ; TSO++ )	{
		delete Tick[TSO];
	};
}
//******************************************************************************
void TNumber::Show()	{
	for ( int Tck=6 ; Tck>= 0  ; Tck-- )	{
		if ( Numb[Number][Tck] )	Tick[Tck]->Show();
			else 	Tick[Tck]->Hide();
	}
};
//******************************************************************************
void TNumber::Hide()	{
	for ( int Tck=6 ; Tck>= 0  ; Tck-- )
		Tick[Tck]->Hide();
}
//******************************************************************************
void TNumber::Set( int iNum )	{
	Number=iNum%10;
	Show();
};
#endif // _NUMBER_CPP
