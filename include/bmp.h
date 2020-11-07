#ifndef _BMP_CPP
# define _BMP_CPP

#include "typedef.h"

#define BMP_FLAG ".bmp"

// hibak�dok
enum TError{ 
    ERR_OK,
    ERR_TWICE, 
    ERR_NO_MEM, 
    ERR_NO_OPEN,
	ERR_NO_READ, 
    ERR_REALLOC
};

// egy sz�n RGB strukt�r�ja
struct TColor	{
	uint8_t B;
	uint8_t G;
	uint8_t R;
	uint8_t L;
};

// BMP256 f�jl fejl�ce
struct THeader
{
	uint8_t NOTINP_1 [18];
	uint32_t X;
	uint32_t Y;
	uint8_t NOTINP_2	[0x1c];
	TColor Pal[256];
}  __attribute__((packed));

class TBmp
{
public:
	char *Fname;                   // f�jl n�v
	char *Pic;                     // a k�p adatter�lete
	int X,Y;                       // m�retei
	unsigned Size;                 // adta ter�let m�rete
	char DeadColor;                // transzparens sz�n
	RECT  Rect;                    // m�retek ism�t
	int ErrNo;                     // a bet�lt�s hibak�dja
	TBmp();
	~TBmp();
	int Load(const char * );
	void Perror();                 // hiba kiirat�sa
	void Draw( int , int );        // k�p kirajzol�sa
	void RPaint(int wx,int wy,int R)	;      // k�p kirajzol�s forgatva
	void RDPaint(int wx,int wy,int R);      // k�p kirajzol�s forgatva transzparens sz�nnel
	void RPaint(int wx,int wy,int R,float s); // k�p kirajzol�s forgatva ny�jt�ssal
};

#endif
