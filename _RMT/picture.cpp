/******************************************************************************
				picture.cpp
******************************************************************************/
#ifndef _PICTURE_CPP
	#define _PICTURE_CPP
//  a TPicture ostály definíciója
#include "typedef.cpp"
#include "BMP.cpp"
#include "error.cpp"
class Pic_Vector	{       // egy vektor leíró rekordja
public:
	int Sp,Ep;             // kezdõpont, végpont
	int Len;               // hossz
	char *Start;           // adatok kezdõ címe
	Pic_Vector()	{       // konstruktor
		Sp=Ep=Len=0;
		Start=NULL;
	}
};
class Pic_Row	{          // egy oszlop leíró rekordja
public:
	int Num;               // vektorok száma az oszlopban
	Pic_Vector *Vector;    // a vektor tömb elsõ elemének címe
	Pic_Row()	{
		Vector=NULL;
		Num=0;
	};
	~Pic_Row()	{
		if ( Vector ) delete Vector;
	};
};
//-----------------------------------------------------------------------------
class TPicture	{
	char *Data;            // a teljes kép adatainak memõria tömbje
public:
	Pic_Row *Row;          // oszlop tömb kezõ címe
	int X,Y;               // kép méretei
	TPicture();
	~TPicture() ;
	int Load( char *Fname );     //  betöltés
	void Draw( int x , int y );  // kirajzol
};
//*****************************************************************************
TPicture::TPicture()	{
	Row=NULL;
	Data=NULL;
	X=Y=0;
};
//*****************************************************************************
TPicture::~TPicture()	{
	if ( Row )	{
		delete []Row;
		Row=NULL;
		free ( Data );
		Data = NULL;
		X=Y=0;
	};
};
//*****************************************************************************
int TPicture::Load( char *Fname )	{
	if ( Row ) return ERR_TWICE;
	TBmp *BMPpic=new TBmp();
	if ( !BMPpic ) return ERR_NO_MEM;
	if ( BMPpic->Load(Fname) )		{
		BMPpic->Perror();
		delete BMPpic;
		return ERR_NO_READ;
	}
	X = BMPpic->X ;
	Y = BMPpic->Y ;
	char DeadCode = BMPpic->DeadColor;
	unsigned DataLen=0;
	for ( int Sx=0 ; Sx<X ; Sx++ )          // a hsznos adatok méretének mérése
		for ( int Sy=0 ; Sy<Y ; Sy++ )
			if ( BMPpic->Pic[ Sx+Sy*X ]!= DeadCode )
				DataLen++;
	Data=(char *)malloc( DataLen );         // adat terület lefoglalása
	if ( !Data )	{
		_Perror( Fname , "Data malloc" , NULL);
		delete BMPpic;
		return ERR_NO_MEM ;
	}
	Row=new Pic_Row[ X ];                   // oszlop tömb dinamikus létrehozása
	if ( !Row ) 	{
		_Perror( Fname , "Rows alloc" , NULL);
		delete BMPpic;
		return ERR_NO_MEM ;
	};
	DataLen=0;
	for ( Sx=0 ; Sx<X ; Sx++ )	{            // elemzés soronként
		BOOL InLine=FALSE;
		int RowNum=0;
		for ( int Sy=0 ; Sy<Y ; Sy++ )	{   // vektorok számlálása oszloponként
			if ( BMPpic->Pic[ Sx+Sy*X ]!= DeadCode )	{
				if ( !InLine )		{
					RowNum++ ;
					InLine=TRUE;
				};
			}	else	InLine=FALSE;
		};
		if ( RowNum>0  )	{
			Row[Sx].Num=RowNum;
			Row[Sx].Vector=new Pic_Vector[ RowNum ];  // új vektor tömb
			if ( !(Row[Sx].Vector) )	{
				_Perror("vector calloc() !",NULL);
				delete BMPpic;
				Row=NULL;
				return ERR_NO_MEM;
			};
			int Vect=0;
			BOOL WrInLine=FALSE;
			for ( int Sy=0 ; Sy<Y ; Sy++ )	{       // a vektorok adatainak megadása
				if ( BMPpic->Pic[ Sx+Sy*X ]!= DeadCode )	{
					if ( !WrInLine )	{
						Row[Sx].Vector[Vect].Start=&(Data[DataLen]) ;
						Row[Sx].Vector[Vect].Sp=Sy;
					};
					Row[Sx].Vector[Vect].Len++;
					Data[DataLen++] = BMPpic->Pic[ Sx+Sy*X ];
					WrInLine=TRUE;
				}	else	{
						if ( WrInLine )	{
							Row[Sx].Vector[Vect].Ep=(Row[Sx].Vector[Vect].Sp+Row[Sx].Vector[Vect].Len);
							Vect++;
						}
						WrInLine=FALSE;
					}
			}
		}
	}
	delete BMPpic;
	return ERR_OK;
}
//*****************************************************************************}
void TPicture::Draw( int x , int y )	{
	for ( int Sx=0 ; Sx<X ; Sx++ )
		for ( int Vect=0 ; Vect<Row[Sx].Num ; Vect++ )
			for ( int Sy=0 ; Sy<Row[Sx].Vector[Vect].Len ; Sy++ )	{
				register Py=(int)Row[Sx].Vector[Vect].Sp + Sy + y;
				if ( Py<200 && (Sx+x)<320 )
					PutPixel( Sx+x , Py , Row[Sx].Vector[Vect].Start[Sy] );
			}
};
//*****************************************************************************
#endif	//PICTURE


