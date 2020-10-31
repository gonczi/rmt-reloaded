/******************************************************************************
					graph13.cpp
******************************************************************************/
#ifndef _GRAPH13_CPP
	#define _GRAPH13_CPP
// grafikus kezelõ függvények
#include "typedef.cpp"
#include "error.cpp"

char Mode;                  // képernyõ mód puffere
long sega000=0xA0000000L;   // képernyõ segmens kezdõcíme

#define MAXY 200            // képernyõ felbontás függõleges irányban
#define MAXX 320            // képernyõ felbontás vízszintes irányban

BYTE Add(BYTE col1,BYTE col2);
void PutPixel(int X,int Y,char N);
char GetPixel(int X,int Y);
void Wait(void);
void SetPalette(char Color,char Red,char Green,char Blue);
//*****************************************************************************/
//*****************************************************************************/
int IntAbs( int Num )	{   // abszolut érték függvény int típusra
	return (Num<0)?-Num:Num;
}

// képernyõ terület elszínezése adott színnel, spec efektussal.
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
// képernyõ terület elszínezése adott színnel, spec efektus nélkül fentrõl lefelé.
void ColoredBar( POINT Poz , RECT Rect , BYTE Color )	{
	Wait();
	for ( int Y=Poz.y ; Y<(Poz.y+Rect.Sy) ; Y++ )	{
		for ( int X=Poz.x ; X<(Poz.x+Rect.Sx) ; X++ )	{
			PutPixel( X , Y , Add(Color,GetPixel(X,Y))  );
		}
	}
};
// adott képernyõ területre áttetszõ képet fest fel, améretei a képnek
// azonosak a képernyõ területével:
void ColoredBar( POINT Poz , RECT Rect , char *Pic )	{
//	wait();
	for ( int Y=Poz.y ; Y<(Poz.y+Rect.Sy) ; Y++ )	{
		for ( int X=Poz.x ; X<(Poz.x+Rect.Sx) ; X++ )	{
			BYTE Color=Pic[(X-Poz.x)+(Y-Poz.y)*Rect.Sx ];
			PutPixel( X , Y , Add(Color,GetPixel(X,Y))  );
		}
	}
};
// két szín azonosítõ összeadása a standard színpaletta használatatkor:
BYTE Add(BYTE col1,BYTE col2)	{
	BYTE ret;
	ret=(((col1&3)+(col2&3))>>1);
	ret+=(((((col1%32)+(col2%32))>>1)>>2)<<2);
	ret+=((((col1>>5)+(col2>>5))>>1)<<5);
	return ret;
}
// beállítja a standard szín palettát:
void InitMainPal()	{
	for ( int c=0 ; c<256 ; c++ )
		SetPalette(c , (c/32)*8 , (((c%32)/4)*8) , (c%4)*21 );
}
// grafikus képernyõ törlése
void ClearDevice()	{
	for ( register int poz=(320*200); poz ; *(char far *)(sega000+poz--)=0 );
};
// képernyõ törlése színnel
void FillScreen(char color)	{
	for ( register int poz=(320*200); poz ; *(char far *)(sega000+poz--)=color );
};
// kép kirajzolása :
//          args:  hova x,y , adatok címe , méret Sx,Sy
void PutImage (int x,int y,char *src,int i,int j)	{
	for ( int cy=0 ; cy<(((j+y)>=200)?(200-y):j) ; cy++ )
		memcpy((void far *)(sega000+(((((y+cy)<0)?0:(y+cy)))*320L)+x),&src[cy*i],
			((i+x)>=320)?(320-x):i  );
};
// memória terület másolása a null értékek nélkül
void fmemzerocpy(void far *dest,void *src,unsigned length)
{
	char puff;
	for ( unsigned l=0 ; l<length ; l++ )
		if ( (puff=(((char *)src)[l]))!=0 )
			(((char far *)dest)[l])=puff;
};
// kép felfestése, a nulla színkódok nélkül:
void PutImageNull (int x,int y,char *src,int i,int j)	{
	for ( int cy=0 ; cy<(((j+y)>=200)?(200-y):j) ; cy++ )
		fmemzerocpy((void far *)(sega000+(((((y+cy)<0)?0:(y+cy)))*320L)+x),&src[cy*i],
			((i+x)>=320)?(320-x):i  );
};
// képernyõ terület elmentése
void GetImage (int x,int y,char *src,int i,int j)	{
	for ( unsigned cy=0 ; cy<j ; cy++ )
	_fmemcpy(&src[cy*i],(void far *)(sega000+((y+cy)*320L)+x),i);
};
// várakozás vertikális visszafutásra a monitoron
void Wait(void)	{
	asm {
	mov dx,0x03da };
wait:
	asm {
	in  al,dx
	and al,8
	jz  wait};
};
// bekapcsolja a grafikus üzemmódot, és menti az elõzõ beállítást
void Init13(void)	{
	asm {
		MOV AH,0x0F
		INT 0x10
		MOV Mode,AL
		MOV AX,0x0013
		INT 0x10
	}
}
// vissza állítja az eredeti képernyõ módot
void Done13(void)	{
	asm {
		MOV AL,Mode
		MOV AH,0x00
		INT 0x10
	}
}
// pixel kigyújtása megszakításon keresztül
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
// pixel kigyújtása közvetlen memõriába írással
void PutPixel13(int X,int Y,char N)	{
	unsigned char far *sp=(unsigned char far *)sega000+X+(Y*320);
	*sp=N;
}
// pixel syínének lekérdezése
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
// egyenes húzása
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
// kitöltöött négyzet kirajzolása
void Bar(int X1,int Y1,int X2,int Y2,char N)	{
	int x,y;
	for ( x=X1 ; x<X2 ; x++ )
		for ( y=Y1; y<Y2 ; y++)
			PutPixel(x,y,N);
};
// egy szín RGB összetevõinek beállítása:
void SetPalette(char Color,char Red,char Green,char Blue)	{
	asm {  /*
	MOV DX,03DAh };       // nincs várakozás
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
// teljes paletta beállítása tömbön keresztül várakozás nélkül
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
// teljes paletta beállítása tömbön keresztül várakozással
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
// a teljes szín paletta lekétdezése
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
