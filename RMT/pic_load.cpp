#ifndef PIC_LOAD
	#define PIC_LOAD

#include "typedef.cpp"
#include "BMP.cpp"
#include "error.cpp"

fstream ez( "log.txt", ios::out | ios::trunc );
int R=0,V=0,D=0;

class Pic_Vector	{
public:
	int Sp,Ep;
	int Len;
	char *Start;
	Pic_Vector()	{
		Len=Sp=Ep=0;
		Start=NULL;
		V++;
	}
	~Pic_Vector()	{
		ez << "\td " << (void *)this << " Vector\n";;
		V--;
	}
};

class Pic_Row	{
public:
	int Num;
	char *Data;
	Pic_Vector *Vector;
	Pic_Row()	{
		Num=0;
		Data=NULL;
		Vector=NULL;
	};
	~Pic_Row();
};

Pic_Row::~Pic_Row()	{
	if ( Num>0 )	{
		for ( int z=0; z<Num ; z++ )	{
			delete &(Vector[z]);
		}
		ez << "\tf " << (void *)Data << " Data\n";
		free( Data );
	}
	ez << "d " << (void *)this << " Row\n";
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class TPicture	{
protected:

public:
	Pic_Row *Row;
	int X,Y;
	TPicture();
	TPicture( char *Fname );
	int Load( char *Fname );
	BOOL FreePic();
	~TPicture(){ FreePic(); } ;
	void Draw( int x , int y );
};
//-----------------------------------------------------------------------------
//	  |     |     |
//	  V     V     V
//-----------------------------------------------------------------------------
class TPicClass	{
public:
	int PC_Layers;
	TPicture *Pic;
	BOOL GetRect( int Id , RECT &Rect  );
	TPicClass();
	int Load( char *Fname , ... );
	int Load( char *Arg[] );
	BOOL Draw( int Id , int x , int y )	{
		if ( (Id<PC_Layers) && (Id>=0) )	{
			Pic[Id].Draw(x,y);
			return TRUE;
		} else 	{
				Eout << "Id: " << Id << "\n";
				Perror( "wrong PicClass Id");
				return FALSE;
			}
	};
	BOOL FreePC();
	~TPicClass(){  FreePC();  };
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
										// TPicture
//*****************************************************************************
TPicture::TPicture()	{
	Row=NULL;
	X=Y=0;
};
//*****************************************************************************
TPicture::TPicture( char *Fname )	{
	Row=NULL;
	X=Y=0;
	Load( Fname );
};
//*****************************************************************************

int TPicture::Load( char *Fname )	{
	if ( Row ) return 97;
	TBmp *BMPpic=NULL;
	BMPpic=new TBmp();
	ez << " &newBMP: " << (void *)BMPpic << " fname: " << Fname << "\n";
	if ( !BMPpic ) return 98;
	int ret=0;

	if ( (ret=BMPpic->Load(Fname))!=0 )		{
		delete BMPpic;
		return ret;
	}

	X = BMPpic->X;
	Y = BMPpic->Y;

	BYTE DeadCode=(BYTE)BMPpic->DeadColor;

	Row=NULL;
	ez << "##########" << (void *)this << "###################    NEW Picture : ######\n";
	ez << " X= " << X << "\n";
	Row=new Pic_Row[ X ];
	R=X;               // <--
	if ( !Row ) 	{
		_Perror( Fname , "Row calloc()" , NULL);
		delete BMPpic;
		return 99 ;
	};

	for ( int Sx=0 ; Sx<X ; Sx++ )	{
		ez << "n " << (void *)&Row[Sx] << " Row[" << Sx << "]\n";
// némi statisztika:

		int DataLen=0;
		BOOL InLine=FALSE;

		for ( int Sy=0 ; Sy<Y ; Sy++ )	{
			if ( (BYTE)BMPpic->Pic[ Sx+Sy*X ]!= DeadCode )	{
				DataLen++;
				if ( !InLine )	Row[Sx].Num++ ;
				InLine=TRUE;
			}	else	InLine=FALSE;
		};

// egy kevéske hely
		if ( Row[Sx].Num>0  )	{
			Row[Sx].Data=(char *)calloc( DataLen , 1 );                    //<--
//			ez << "c " << (void *)Row[Sx].Data << " Row[" << Sx << "].Data\n";
			D++;
			if ( !Row[Sx].Data )	{
				delete BMPpic;
				_Perror("data calloc() bocs !",NULL);

				Row=NULL;
				return 101;
			};

			Row[Sx].Vector=new Pic_Vector[ Row[Sx].Num ];   //<--
//			ez << "n " << (void *)Row[Sx].Vector << " Row[" << Sx << "].Vector\n";
			V++;
			if ( !(Row[Sx].Vector) )	{
				_Perror("vector calloc() bocs !",NULL);
				delete BMPpic;

				Row=NULL;
				return 100;
			};
// majd felvéssûk az adatokat
			DataLen=0;
			int Vect=0;
			InLine=FALSE;

			for ( int Sy=0 ; Sy<Y ; Sy++ )	{
				if ( (BYTE)BMPpic->Pic[ Sx+Sy*X ]!= DeadCode )	{
					if ( !InLine )	{
						Row[Sx].Vector[Vect].Start=&(Row[Sx].Data[DataLen]) ;
						Row[Sx].Vector[Vect].Sp=Sy;
					};
					Row[Sx].Vector[Vect].Len++;
					Row[Sx].Data[DataLen++]=BMPpic->Pic[ Sx+Sy*X ];
					InLine=TRUE;
				}	else	{
						if ( InLine )	{
							Row[Sx].Vector[Vect].Ep=(Row[Sx].Vector[Vect].Sp+Row[Sx].Vector[Vect].Len);
							Vect++;
							InLine=FALSE;
						}
					}
			}
		}
	}
	delete BMPpic;
	return 0;
}
//*****************************************************************************
BOOL TPicture::FreePic()	{
	ez << "*********###" << (void *)this << "####********************** FREEE PIC ***\n";
	if ( Row )	{
		for ( int iSx=0 ; iSx<X ; iSx++ )	{
			delete &(Row[iSx]);
		}
		Row=NULL;
 //		ez << "R: " << R <<" V: " << V <<" D: " << D << "\n";
		return TRUE;
	};
	return FALSE;
};
//*****************************************************************************}

void TPicture::Draw( int x , int y )	{
	for ( int Sx=0 ; Sx<X ; Sx++ )
		for ( int Vect=0 ; Vect<Row[Sx].Num ; Vect++ )
			for ( int Sy=0 ; Sy<Row[Sx].Vector[Vect].Len ; Sy++ )	{
				register Py=(int)Row[Sx].Vector[Vect].Sp + Sy + y;
				if ( Py<200 && (Sx+x)<320 ) PutPixel( Sx+x , Py , Row[Sx].Vector[Vect].Start[Sy] );
			}
};

//*****************************************************************************
//*****************************************************************************
										// TPicClass
TPicClass::TPicClass()	{
	PC_Layers=0;
	Pic = NULL;
}
//*****************************************************************************}

int TPicClass::Load( char *Arg[] )	{
	int ret=0;
	if ( !Pic )	{
		int iLayers=0;
		while ( Arg[iLayers] ) iLayers++;
		Pic =new TPicture[iLayers] ;
		for ( int Lyr=0; Lyr< iLayers ; Lyr++ )	{
			Eout << " errno: " << Pic[Lyr].Load( Arg[Lyr] ) << "\n";
			Eout << &(Pic[Lyr]) << " new " << Arg[Lyr] << "\n";
		}
		PC_Layers=iLayers;
	}	else ret=200;
	return ret;
};

//*****************************************************************************}

int TPicClass::Load( char *Fname , ... )	{
	char * *Arg=&Fname;
	return Load(Arg);
};

//*****************************************************************************
BOOL TPicClass::FreePC()	{
	BOOL ret=FALSE;
	if ( Pic )	{
		for ( int Lyr=0; Lyr<PC_Layers ; Lyr++ )	{
			delete &(Pic[Lyr]);
			Eout << &(Pic[Lyr]) << " :deleted \n";
		}
		Pic=NULL;
		ret=TRUE;
	};
	return ret;
};
//*****************************************************************************
BOOL TPicClass::GetRect( int Id , RECT &Rect  )	{
	if ( Id<PC_Layers )	{
		Rect.Sx=Pic[Id].X;
		Rect.Sy=Pic[Id].Y;
		return TRUE;
	}
	return FALSE;
};

#endif	//PIC_LOAD



