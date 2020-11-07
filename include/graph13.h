#ifndef _GRAPH13_CPP
	#define _GRAPH13_CPP

#include "typedef.h"

#define MAXY 200            // k�perny� felbont�s f�gg�leges ir�nyban
#define MAXX 320            // k�perny� felbont�s v�zszintes ir�nyban

BYTE Add(BYTE col1,BYTE col2);
void PutPixel(int X,int Y,char N);
char GetPixel(int X,int Y);
void Wait(void);
void SetPalette(char Color,char Red,char Green,char Blue);

void PutImage (int x,int y,char *src,int i,int j);

#endif  // _GRAPH13_CPP