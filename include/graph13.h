#ifndef _GRAPH13_CPP
	#define _GRAPH13_CPP

#include "typedef.h"

void Init13(void);
void InitMainPal();
void Done13(void);

void PutImage(int x, int y, char *src, int i, int j);
void GetImage (int x, int y, char *src, int i, int j);

void PutPixel(int X, int Y, uint8_t N);
void Bar(int X1,int Y1,int X2,int Y2,uint8_t N);

void Wait(void);

#endif  // _GRAPH13_CPP