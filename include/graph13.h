#ifndef _GRAPH13_CPP
	#define _GRAPH13_CPP

#include "typedef.h"

#define MAXY 200            // k�perny� felbont�s f�gg�leges ir�nyban
#define MAXX 320            // k�perny� felbont�s v�zszintes ir�nyban

extern long sega000;

void Init13(void);
void InitMainPal();
void Done13(void);

void PutImage(int x, int y, char *src, int i, int j);
void GetImage (int x, int y, char *src, int i, int j);

void PutPixel(int X, int Y, uint8_t N);
void Bar(int X1,int Y1,int X2,int Y2,uint8_t N);
void ColoredBarLines( POINT Poz , RECT Rect , BYTE Color );
void Straight(int x1, int y1, int x2, int y2, uint8_t c);

void Wait(void);

void SetPaletteRegistersNoWait(	unsigned char Start, unsigned Number, void *Table);
void SetPaletteRegisters(unsigned char Start,unsigned Number,void *Table);
void GetPaletteRegisters(unsigned char Start,unsigned Number,void *Table);


#endif  // _GRAPH13_CPP