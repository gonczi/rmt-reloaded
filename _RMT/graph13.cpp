/******************************************************************************
					graph13.cpp
******************************************************************************/
#ifndef _GRAPH13_CPP
	#define _GRAPH13_CPP
// grafikus kezel� f�ggv�nyek
#include "typedef.cpp"
#include "error.cpp"

char Mode;                  // k�perny� m�d puffere
long sega000=0xA0000000L;   // k�perny� segmens kezd�c�me

BYTE Add(BYTE col1,BYTE col2);
void PutPixel(int X,int Y,char N);
char GetPixel(int X,int Y);
void Wait(void);
void SetPalette(char Color,char Red,char Green,char Blue);
//*****************************************************************************/
//*****************************************************************************/
int IntAbs( int Num )	{   // abszolut �rt�k f�ggv�ny int t�pusra
	return (Num<0)?-Num:Num;
}

// k�perny� ter�let elsz�nez�se adott sz�nnel, spec efektussal.
void ColoredBarLines( POINT Poz , RECT Rect , BYTE Color )	{
	Wait();
	for ( int Y=Poz.y ; Y<(Poz.y+Rect.Sy) ; Y+=2 )	{
		for ( int X=Poz.x ; X<(Poz.x+Rect.Sx) ; X++ )	{
			PutPixel( X , Y , Add(Color,GetPixel(X,Y))  );
			PutPixel( X , ((Rect.Sy)%2)?(2*Poz.y+Rect.Sy)-Y:(2*Poz.y+Rect.Sy-1)-Y ,
				Add(Color,GetPixel(X,((Rect.Sy)%2)?(2*Poz.y+Rect.Sy)-Y:(2*Poz.y+Rect.Sy-1)-Y ))  );
		}
	}
};
// k�perny� ter�let elsz�nez�se adott sz�nnel, spec efektus n�lk�l fentr�l lefel�.
void ColoredBar( POINT Poz , RECT Rect , BYTE Color )	{
	Wait();
	for ( int Y=Poz.y ; Y<(Poz.y+Rect.Sy) ; Y++ )	{
		for ( int X=Poz.x ; X<(Poz.x+Rect.Sx) ; X++ )	{
			PutPixel( X , Y , Add(Color,GetPixel(X,Y))  );
		}
	}
};
// adott k�perny� ter�letre �ttetsz� k�pet fest fel, am�retei a k�pnek
// azonosak a k�perny� ter�let�vel:
void ColoredBar( POINT Poz , RECT Rect , char *Pic )	{
//	wait();
	for ( int Y=Poz.y ; Y<(Poz.y+Rect.Sy) ; Y++ )	{
		for ( int X=Poz.x ; X<(Poz.x+Rect.Sx) ; X++ )	{
			BYTE Color=Pic[(X-Poz.x)+(Y-Poz.y)*Rect.Sx ];
			PutPixel( X , Y , Add(Color,GetPixel(X,Y))  );
		}
	}
};
// k�t sz�n azonos�t� �sszead�sa a standard sz�npaletta haszn�latatkor:
BYTE Add(BYTE col1,BYTE col2)	{
	BYTE ret;
	ret=(((col1&3)+(col2&3))>>1);
	ret+=(((((col1%32)+(col2%32))>>1)>>2)<<2);
	ret+=((((col1>>5)+(col2>>5))>>1)<<5);
	return ret;
}
// be�ll�tja a standard sz�n palett�t:
void InitMainPal()	{
	for ( int c=0 ; c<256 ; c++ )
		SetPalette(c , (c/32)*8 , (((c%32)/4)*8) , (c%4)*21 );
}
// grafikus k�perny� t�rl�se
void ClearDevice()	{
	for ( register int poz=(320*200); poz ; *(char far *)(sega000+poz--)=0 );
};
// k�perny� t�rl�se sz�nnel
void FillScreen(char color)	{
	for ( register int poz=(320*200); poz ; *(char far *)(sega000+poz--)=color );
};
// k�p kirajzol�sa :
//          args:  hova x,y , adatok c�me , m�ret Sx,Sy
void PutImage (int x,int y,char *src,int i,int j)	{
	for ( int cy=0 ; cy<(((j+y)>=200)?(200-y):j) ; cy++ )
		memcpy((void far *)(sega000+(((((y+cy)<0)?0:(y+cy)))*320L)+x),&src[cy*i],
			((i+x)>=320)?(320-x):i  );
};
// mem�ria ter�let m�sol�sa a null �rt�kek n�lk�l
void fmemzerocpy(void far *dest,void *src,unsigned length)
{
	char puff;
	for ( unsigned l=0 ; l<length ; l++ )
		if ( (puff=(((char *)src)[l]))!=0 )
			(((char far *)dest)[l])=puff;
};
// k�p felfest�se, a nulla sz�nk�dok n�lk�l:
void PutImageNull (int x,int y,char *src,int i,int j)	{
	for ( int cy=0 ; cy<(((j+y)>=200)?(200-y):j) ; cy++ )
		fmemzerocpy((void far *)(sega000+(((((y+cy)<0)?0:(y+cy)))*320L)+x),&src[cy*i],
			((i+x)>=320)?(320-x):i  );
};
// k�perny� ter�let elment�se
void GetImage (int x,int y,char *src,int i,int j)	{
	for ( unsigned cy=0 ; cy<j ; cy++ )
	_fmemcpy(&src[cy*i],(void far *)(sega000+((y+cy)*320L)+x),i);
};
// v�rakoz�s vertik�lis visszafut�sra a monitoron
void Wait(void)	{
	asm {
	mov dx,0x03da };
wait:
	asm {
	in  al,dx
	and al,8
	jz  wait};
};
// bekapcsolja a grafikus �zemm�dot, �s menti az el�z� be�ll�t�st
void Init13(void)	{
	asm {
		MOV AH,0x0F
		INT 0x10
		MOV Mode,AL
		MOV AX,0x0013
		INT 0x10
	}
}
// vissza �ll�tja az eredeti k�perny� m�dot
void Done13(void)	{
	asm {
		MOV AL,Mode
		MOV AH,0x00
		INT 0x10
	}
}
// pixel kigy�jt�sa megszak�t�son kereszt�l
void PutPixel(int X,int Y,char N)	{
	Y*=320;
	asm {
	MOV AX,0A000h
	MOV ES,AX
	MOV DX,Y
	ADD DX,X
	MOV DI,DX
	MOV AL,N
	STOSB
	}
};
// pixel kigy�jt�sa k�zvetlen mem�ri�ba �r�ssal
void PutPixel13(int X,int Y,char N)	{
	unsigned char far *sp=(unsigned char far *)sega000+X+(Y*320);
	*sp=N;
}
// pixel sy�n�nek lek�rdez�se
char GetPixel(int X,int Y)	{
	Y*=320;
	asm {
	MOV AX,0A000h
	MOV ES,AX
	MOV DX,Y
	MOV DI,DX
	ADD DI,X
	MOV AL,ES:[DI]
	}
	return(_AL);
};
// egyenes h�z�sa
void Straight(int x1,int y1,int x2,int y2,int c)	{
	if ( (x1==x2) && (y1==y2) ) PutPixel(x1,y1,c);
	else	{
		int dx,dy,n=0,i;
		float fi;
		if ( IntAbs(dx=(x1-x2) )>IntAbs(dy=(y1-y2) ) )
			for ( i= (dx/IntAbs(dx)),fi=((dy)/float(dx)) ; n!=dx ; n+=i )
				PutPixel(x1-n,y1-(fi*n),c);
		else
			for ( i= (dy/IntAbs(dy)),fi=((dx)/float(dy)) ; n!=dy ; n+=i )
				PutPixel(x1-(fi*n),y1-n,c);
	};
};
// kit�lt��tt n�gyzet kirajzol�sa
void Bar(int X1,int Y1,int X2,int Y2,char N)	{
	int x,y;
	for ( x=X1 ; x<X2 ; x++ )
		for ( y=Y1; y<Y2 ; y++)
			PutPixel(x,y,N);
};
// egy sz�n RGB �sszetev�inek be�ll�t�sa:
void SetPalette(char Color,char Red,char Green,char Blue)	{
	asm {  /*
	MOV DX,03DAh };       // nincs v�rakoz�s
L1:
	asm {
	IN AL,DX
	TEST AL,8
	JNZ L1 }
L2:
	asm {
	IN AL,DX
	TEST AL,8
	JZ L2
/**/ 	MOV DX,03C8h
	MOV AL,Color
	OUT DX,AL
	INC DX
	MOV AL,Red
	OUT DX,AL
	MOV AL,Green
	OUT DX,AL
	MOV AL,Blue
	OUT DX,AL }
};
// teljes paletta be�ll�t�sa t�mb�n kereszt�l v�rakoz�s n�lk�l
void SetPaletteRegistersNoWait(	unsigned char Start,
											unsigned Number,
											void far*Table)	{
//	void *L1,*L2;
	asm {
	XOR BH,BH
	MOV BL,Start
	MOV CX,Number
	MOV DX,0x03DA
/*L1:
	IN AL,DX
	TEST AL,8
	JNZ L1
L2:
	IN AL,DX
	TEST AL,8
	JZ L2
*/	LES DX,Table
	MOV AX,0x1012
	INT 0x10
	};
};
// teljes paletta be�ll�t�sa t�mb�n kereszt�l v�rakoz�ssal
void SetPaletteRegisters(unsigned char Start,unsigned Number,void far*Table)	{
//	void *L1,*L2;
	asm {
	XOR BH,BH
	MOV BL,Start
	MOV CX,Number
	MOV DX,0x03DA
	}
L1:
	asm {
	IN AL,DX
	TEST AL,8
	JNZ L1
	}
L2:
	asm {
	IN AL,DX
	TEST AL,8
	JZ L2
	LES DX,Table
	MOV AX,0x1012
	INT 0x10
	};
};
// a teljes sz�n paletta lek�tdez�se
void GetPaletteRegisters(unsigned char Start,unsigned Number,void far* Table)	{
	asm {
		  XOR BH,BH
		  MOV BL,Start
		  MOV CX,Number
		  MOV AX,0x1017
	LES DX,Table
		  INT 0x10
	};
};

#endif  // _GRAPH13_CPP
