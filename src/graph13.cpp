#include "graph13.h"
#include "error.h"
#include "scancode.h"

#include <thread>
#include <unistd.h>

using namespace std;

#include <stddef.h>

//Using SDL and standard IO
#include <SDL.h>

#define far

#define MAXY 200            // k�perny� felbont�s f�gg�leges ir�nyban
#define MAXX 320            // k�perny� felbont�s v�zszintes ir�nyban

uint8_t sega000_buff[MAXX * MAXY] = {0};
long sega000 = (long)sega000_buff;

char Mode;                  // k�perny� m�d puffere
BYTE Add(BYTE col1, BYTE col2);
void PutPixel(int X, int Y, uint8_t N);
void PutPixel13(int X, int Y, uint8_t N);
uint8_t GetPixel(int X, int Y);
void Wait(void);
void SetPalette(uint8_t Color, uint8_t Red, uint8_t Green, uint8_t Blue);

void sync_segabuff();

//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;

typedef struct {
	uint8_t r;
	uint8_t g; 
	uint8_t b;
} __attribute__((packed)) pixel_t;

pixel_t palette[256] = 
{
	{  0,  0,  0},
	{  0,  0,170},
	{  0,170,  0},
	{  0,170,170},
	{170,  0,  0},
	{170,  0,170},
	{170, 85,  0},
	{170,170,170},
	{ 85, 85, 85},
	{ 85, 85,255},
	{ 85,255, 85},
	{ 85,255,255},
	{255, 85, 85},
	{255, 85,255},
	{255,255, 85},
	{255,255,255},
	{  0,  0,  0},
	{ 20, 20, 20},
	{ 32, 32, 32},
	{ 44, 44, 44},
	{ 56, 56, 56},
	{ 68, 68, 68},
	{ 80, 80, 80},
	{ 97, 97, 97},
	{113,113,113},
	{129,129,129},
	{145,145,145},
	{161,161,161},
	{182,182,182},
	{202,202,202},
	{226,226,226},
	{255,255,255},
	{  0,  0,255},
	{ 64,  0,255},
	{125,  0,255},
	{190,  0,255},
	{255,  0,255},
	{255,  0,190},
	{255,  0,125},
	{255,  0, 64},
	{255,  0,  0},
	{255, 64,  0},
	{255,125,  0},
	{255,190,  0},
	{255,255,  0},
	{190,255,  0},
	{125,255,  0},
	{ 64,255,  0},
	{  0,255,  0},
	{  0,255, 64},
	{  0,255,125},
	{  0,255,190},
	{  0,255,255},
	{  0,190,255},
	{  0,125,255},
	{  0, 64,255},
	{125,125,255},
	{157,125,255},
	{190,125,255},
	{222,125,255},
	{255,125,255},
	{255,125,222},
	{255,125,190},
	{255,125,157},
	{255,125,125},
	{255,157,125},
	{255,190,125},
	{255,222,125},
	{255,255,125},
	{222,255,125},
	{190,255,125},
	{157,255,125},
	{125,255,125},
	{125,255,157},
	{125,255,190},
	{125,255,222},
	{125,255,255},
	{125,222,255},
	{125,190,255},
	{125,157,255},
	{182,182,255},
	{198,182,255},
	{218,182,255},
	{234,182,255},
	{255,182,255},
	{255,182,234},
	{255,182,218},
	{255,182,198},
	{255,182,182},
	{255,198,182},
	{255,218,182},
	{255,234,182},
	{255,255,182},
	{234,255,182},
	{218,255,182},
	{198,255,182},
	{182,255,182},
	{182,255,198},
	{182,255,218},
	{182,255,234},
	{182,255,255},
	{182,234,255},
	{182,218,255},
	{182,198,255},
	{  0,  0,113},
	{ 28,  0,113},
	{ 56,  0,113},
	{ 85,  0,113},
	{113,  0,113},
	{113,  0, 85},
	{113,  0, 56},
	{113,  0, 28},
	{113,  0,  0},
	{113, 28,  0},
	{113, 56,  0},
	{113, 85,  0},
	{113,113,  0},
	{ 85,113,  0},
	{ 56,113,  0},
	{ 28,113,  0},
	{  0,113,  0},
	{  0,113, 28},
	{  0,113, 56},
	{  0,113, 85},
	{  0,113,113},
	{  0, 85,113},
	{  0, 56,113},
	{  0, 28,113},
	{ 56, 56,113},
	{ 68, 56,113},
	{ 85, 56,113},
	{ 97, 56,113},
	{113, 56,113},
	{113, 56, 97},
	{113, 56, 85},
	{113, 56, 68},
	{113, 56, 56},
	{113, 68, 56},
	{113, 85, 56},
	{113, 97, 56},
	{113,113, 56},
	{ 97,113, 56},
	{ 85,113, 56},
	{ 68,113, 56},
	{ 56,113, 56},
	{ 56,113, 68},
	{ 56,113, 85},
	{ 56,113, 97},
	{ 56,113,113},
	{ 56, 97,113},
	{ 56, 85,113},
	{ 56, 68,113},
	{ 80, 80,113},
	{ 89, 80,113},
	{ 97, 80,113},
	{105, 80,113},
	{113, 80,113},
	{113, 80,105},
	{113, 80, 97},
	{113, 80, 89},
	{113, 80, 80},
	{113, 89, 80},
	{113, 97, 80},
	{113,105, 80},
	{113,113, 80},
	{105,113, 80},
	{ 97,113, 80},
	{ 89,113, 80},
	{ 80,113, 80},
	{ 80,113, 89},
	{ 80,113, 97},
	{ 80,113,105},
	{ 80,113,113},
	{ 80,105,113},
	{ 80, 97,113},
	{ 80, 89,113},
	{  0,  0, 64},
	{ 16,  0, 64},
	{ 32,  0, 64},
	{ 48,  0, 64},
	{ 64,  0, 64},
	{ 64,  0, 48},
	{ 64,  0, 32},
	{ 64,  0, 16},
	{ 64,  0,  0},
	{ 64, 16,  0},
	{ 64, 32,  0},
	{ 64, 48,  0},
	{ 64, 64,  0},
	{ 48, 64,  0},
	{ 32, 64,  0},
	{ 16, 64,  0},
	{  0, 64,  0},
	{  0, 64, 16},
	{  0, 64, 32},
	{  0, 64, 48},
	{  0, 64, 64},
	{  0, 48, 64},
	{  0, 32, 64},
	{  0, 16, 64},
	{ 32, 32, 64},
	{ 40, 32, 64},
	{ 48, 32, 64},
	{ 56, 32, 64},
	{ 64, 32, 64},
	{ 64, 32, 56},
	{ 64, 32, 48},
	{ 64, 32, 40},
	{ 64, 32, 32},
	{ 64, 40, 32},
	{ 64, 48, 32},
	{ 64, 56, 32},
	{ 64, 64, 32},
	{ 56, 64, 32},
	{ 48, 64, 32},
	{ 40, 64, 32},
	{ 32, 64, 32},
	{ 32, 64, 40},
	{ 32, 64, 48},
	{ 32, 64, 56},
	{ 32, 64, 64},
	{ 32, 56, 64},
	{ 32, 48, 64},
	{ 32, 40, 64},
	{ 44, 44, 64},
	{ 48, 44, 64},
	{ 52, 44, 64},
	{ 60, 44, 64},
	{ 64, 44, 64},
	{ 64, 44, 60},
	{ 64, 44, 52},
	{ 64, 44, 48},
	{ 64, 44, 44},
	{ 64, 48, 44},
	{ 64, 52, 44},
	{ 64, 60, 44},
	{ 64, 64, 44},
	{ 60, 64, 44},
	{ 52, 64, 44},
	{ 48, 64, 44},
	{ 44, 64, 44},
	{ 44, 64, 48},
	{ 44, 64, 52},
	{ 44, 64, 60},
	{ 44, 64, 64},
	{ 44, 60, 64},
	{ 44, 52, 64},
	{ 44, 48, 64},
	{  0,  0,  0},
	{  0,  0,  0},
	{  0,  0,  0},
	{  0,  0,  0},
	{  0,  0,  0},
	{  0,  0,  0},
	{  0,  0,  0},
	{  0,  0,  0}
};

pixel_t pixels[MAXX * MAXY * 4] = {0};

bool graph13TaskRun = true;
thread *graph13TaskThread = NULL;

void graph13Task(string msg)
{
	while (graph13TaskRun) {
		usleep(10000);
		sync_segabuff();
	}
}

void sync_segabuff()
{
	SDL_Surface* drawSurface = NULL;

	for (int x = 0; x < MAXX; x++) {
		for (int y = 0; y < MAXY; y++) {
			int srcpos = x + (y * MAXX);
			// pixels[srcpos] = palette[sega000_buff[srcpos]];

			// double it:
			int pos = (x*2) + (y * 2 * MAXX * 2);
			pixels[pos] = palette[sega000_buff[srcpos]];
			pixels[pos+1] = pixels[pos];
			pixels[pos+(MAXX*2)] = pixels[pos];
			pixels[pos+(MAXX*2)+1] = pixels[pos];
		}	
	}

	drawSurface = SDL_CreateRGBSurfaceFrom((void*)pixels,
					MAXX * 2,
					MAXY * 2,
					3 * 8,          		// bits per pixel = 24
					MAXX * 2 * 3,  				// pitch
					0x0000FF,              	// red mask
					0x00FF00,              	// green mask
					0xFF0000,              	// blue mask
					0);                    	// alpha mask (none)			

	SDL_BlitSurface(drawSurface, NULL, screenSurface, NULL);

	//Update the surface
	SDL_UpdateWindowSurface(window);

	SDL_FreeSurface(drawSurface);
}

//*****************************************************************************/
//*****************************************************************************/

int IntAbs( int Num )	
{   // abszolut �rt�k f�ggv�ny int t�pusra
	return (Num<0)?-Num:Num;
}

// k�perny� ter�let elsz�nez�se adott sz�nnel, spec efektussal.
void ColoredBarLines( POINT Poz , RECT Rect , BYTE Color )	
{
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
void ColoredBar( POINT Poz , RECT Rect , BYTE Color )	
{
	Wait();
	for ( int Y=Poz.y ; Y<(Poz.y+Rect.Sy) ; Y++ )	{
		for ( int X=Poz.x ; X<(Poz.x+Rect.Sx) ; X++ )	{
			PutPixel( X , Y , Add(Color,GetPixel(X,Y))  );
		}
	}
};

// adott k�perny� ter�letre �ttetsz� k�pet fest fel, am�retei a k�pnek
// azonosak a k�perny� ter�let�vel:
void ColoredBar( POINT Poz , RECT Rect , char *Pic )	
{
//	wait();
	for ( int Y=Poz.y ; Y<(Poz.y+Rect.Sy) ; Y++ )	{
		for ( int X=Poz.x ; X<(Poz.x+Rect.Sx) ; X++ )	{
			BYTE Color=Pic[(X-Poz.x)+(Y-Poz.y)*Rect.Sx ];
			PutPixel( X , Y , Add(Color,GetPixel(X,Y))  );
		}
	}
};

// k�t sz�n azonos�t� �sszead�sa a standard sz�npaletta haszn�latatkor:
BYTE Add(BYTE col1,BYTE col2)	
{
	BYTE ret;
	ret=(((col1&3)+(col2&3))>>1);
	ret+=(((((col1%32)+(col2%32))>>1)>>2)<<2);
	ret+=((((col1>>5)+(col2>>5))>>1)<<5);
	return ret;
}

// be�ll�tja a standard sz�n palett�t:
void InitMainPal()	
{
	for (uint16_t c = 0 ; c < 256 ; c++) {
		SetPalette(
			c, 
			4 * ((c / 32) * 9), 
			4 * (((c % 32) / 4) * 9), 
			4 * (c % 4) * 21
		);
	}
}

// grafikus k�perny� t�rl�se
void ClearDevice()	
{
	// for ( register int poz=(320*200); poz ; *(char far *)(sega000+poz--)=0 );
};

// k�perny� t�rl�se sz�nnel
void FillScreen(uint8_t color)	
{
	for ( register int poz=(320*200); poz ; *(uint8_t *)(sega000+poz--)=color );
};

// k�p kirajzol�sa :
//          args:  hova x,y , adatok c�me , m�ret Sx,Sy
void PutImage (int x, int y, char *src, int i, int j)	
{
	for (int cy = 0; cy < (((j+y)>=200)?(200-y):j); cy++ ) {
		memcpy(
			(void *)(sega000 + (((((y + cy) < 0) ? 0 : (y + cy))) * MAXX) + x),
			&src[cy * i],
			((i+x)>=320)?(320-x):i
		);
	}
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
void PutImageNull (int x,int y,char *src,int i,int j)	
{
	// for ( int cy=0 ; cy<(((j+y)>=200)?(200-y):j) ; cy++ )
	// 	fmemzerocpy((void far *)(sega000+(((((y+cy)<0)?0:(y+cy)))*320L)+x),&src[cy*i],
	// 		((i+x)>=320)?(320-x):i  );
};

// k�perny� ter�let elment�se
void GetImage (int x, int y, char *src, int i, int j)	
{
	for (unsigned cy = 0; cy < j; cy++) {
		memcpy(&src[cy * i], (void *)(sega000 + ((y + cy) * MAXX) + x), i);
	}
};

// v�rakoz�s vertik�lis visszafut�sra a monitoron
void Wait(void)	
{
// 	asm {
// 	mov dx,0x03da };
// wait:
// 	asm {
// 	in  al,dx
// 	and al,8
	// jz  wait};
};

// bekapcsolja a grafikus �zemm�dot, �s menti az el�z� be�ll�t�st
void Init13(void)	
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	} else {
		//Create window
		window = SDL_CreateWindow(
			"RMT (reloaded)", 
			SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 
			MAXX * 2, 
			MAXY * 2, 
			0 // TODO: SDL_WINDOW_FULLSCREEN
		);
		if (window == NULL) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		} else {
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface black
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0x00, 0x00, 0x00));
			
			//Update the surface
			SDL_UpdateWindowSurface(window);
		}
	}

	graph13TaskThread = new thread(graph13Task, "");
}

void Done13(void)	
{
	graph13TaskRun = FALSE;
	graph13TaskThread->join();

	//Wait some
	SDL_Delay(1000);

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();
}

// pixel kigy�jt�sa megszak�t�son kereszt�l
void PutPixel(int X, int Y, uint8_t N)	
{
	PutPixel13(X, Y, N);	
};

// pixel kigy�jt�sa k�zvetlen mem�ri�ba �r�ssal
void PutPixel13(int X, int Y, uint8_t N)	
{
	uint8_t *sp = (uint8_t *)sega000 + X + (Y * MAXX);
	*sp = N;
}

// pixel sy�n�nek lek�rdez�se
uint8_t GetPixel(int X, int Y)	
{
	uint8_t *sp = (uint8_t *)sega000 + X + (Y * MAXX);
	return *sp;
};

// egyenes h�z�sa
void Straight(int x1, int y1, int x2, int y2, uint8_t c)	
{
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
void Bar(int X1,int Y1,int X2,int Y2,uint8_t N)	
{
	int x,y;
	for ( x=X1 ; x<X2 ; x++ )
		for ( y=Y1; y<Y2 ; y++)
			PutPixel(x,y,N);
};

// egy sz�n RGB �sszetev�inek be�ll�t�sa:
void SetPalette(uint8_t Color, uint8_t Red, uint8_t Green, uint8_t Blue)	
{
	// printf("SetPalette: %d %d %d\n", (int)Red, (int)Green, (int)Blue);

	palette[Color].r = Red;
	palette[Color].g = Green;
	palette[Color].b = Blue;
};

// teljes paletta be�ll�t�sa t�mb�n kereszt�l v�rakoz�s n�lk�l
void SetPaletteRegistersNoWait(	unsigned char Start,
											unsigned Number,
											void far*Table)	
{
// //	void *L1,*L2;
// 	asm {
// 	XOR BH,BH
// 	MOV BL,Start
// 	MOV CX,Number
// 	MOV DX,0x03DA
// /*L1:
// 	IN AL,DX
// 	TEST AL,8
// 	JNZ L1
// L2:
// 	IN AL,DX
// 	TEST AL,8
// 	JZ L2
// */	LES DX,Table
// 	MOV AX,0x1012
// 	INT 0x10
	// };
};

// teljes paletta be�ll�t�sa t�mb�n kereszt�l v�rakoz�ssal
void SetPaletteRegisters(unsigned char Start,unsigned Number,void far*Table)	
{
// //	void *L1,*L2;
// 	asm {
// 	XOR BH,BH
// 	MOV BL,Start
// 	MOV CX,Number
// 	MOV DX,0x03DA
// 	}
// L1:
// 	asm {
// 	IN AL,DX
// 	TEST AL,8
// 	JNZ L1
// 	}
// L2:
// 	asm {
// 	IN AL,DX
// 	TEST AL,8
// 	JZ L2
// 	LES DX,Table
// 	MOV AX,0x1012
// 	INT 0x10
// 	};
};

// a teljes sz�n paletta lek�tdez�se
void GetPaletteRegisters(unsigned char Start,unsigned Number,void far* Table)	
{
	// asm {
	// 	  XOR BH,BH
	// 	  MOV BL,Start
	// 	  MOV CX,Number
	// 	  MOV AX,0x1017
	// LES DX,Table
	// 	  INT 0x10
	// };
};
