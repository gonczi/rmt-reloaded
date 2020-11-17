#include "bmp.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// #include <alloc.h>
// #include <mem.h>
// #include <math.h>

#include "graph13.h"
#include "error.h"
// #include "typedef.cpp"

TBmp::TBmp()	
{
	Fname = Pic = NULL;
	ErrNo = -2;
	X = Y = 0;
	DeadColor = 0;
}

TBmp::~TBmp()	
{
	if (NULL != Fname) {
		free(Fname);
	}

	if (NULL != Pic) {
		free(Pic);
	}
	Pic = (char *)0xFFFF; // ???! 
	ErrNo = -1;
	X = Y = 0;
	DeadColor = 0;
}

int TBmp::Load(const char *iFname)	
{
	THeader Header;

	if (Pic) {
		return ERR_TWICE;
	}

	Fname = (char *)malloc(60);
	if (!Fname) {
		return ERR_NO_MEM;        // hiba: nics mem�ria
	}
	strcpy(Fname, "img/");         // f�jl n�v �ssze�ll�t�sa
	strcat(Fname, iFname);
	strcat(Fname, BMP_FLAG);
	
	int File = open(Fname, O_BINARY);
	if (File == -1)	{
		return ErrNo = ERR_NO_OPEN;
	}

	memset(&Header, 0, sizeof(Header));
	if (read(File, &Header, sizeof(THeader)) != sizeof(THeader)) {
		close(File);
		return ErrNo = ERR_NO_READ;
	}

	Rect.Sx = X = int(Header.X);
	Rect.Sy = Y = int(Header.Y);

	int RSize = (X % 4) ? (((X >> 2) + 1) << 2) : (X);

	unsigned FullSize = unsigned(RSize) * unsigned(Y);
	Pic = (char *)malloc(FullSize);
	if (!Pic) {
		close(File);
		return ErrNo = ERR_NO_MEM;
	}

	if (read(File ,Pic ,FullSize ) != FullSize)	{
		close(File);          // hiba: k�tszeres bet�lt�s
		free (Pic);
		Pic = NULL;
		return ErrNo = ERR_NO_READ;
	}

	close (File);

	char *Puff = (char *)malloc(unsigned(RSize));
	if (!Puff)	{
		free (Pic);
		Pic = NULL;
		return ErrNo = ERR_NO_MEM;
	}

	for (int Py = 0 ; Py < (Y >> 1); Py++)	{   // k�p sorainak rendez�se, z�m�t�se
		memcpy(Puff, &Pic[Py * RSize], unsigned(RSize));
		memcpy(&Pic[Py * X ], &Pic[(Y - Py - 1) * RSize], unsigned(X) );
		memcpy(&Pic[(Y - Py - 1) * RSize], Puff, unsigned(RSize));
	}

	free (Puff);

	for (int Py = (Y >> 1); Py < Y; Py++)	{
		memcpy(&Pic[Py * X], &Pic[Py * RSize], unsigned(X));
	}

	Size = unsigned(X) * unsigned(Y);
	Pic = (char *)realloc(Pic, Size );
	if (!Pic)	{
		return ErrNo = ERR_REALLOC;
	}

	DeadColor = Pic[0];
	return ERR_OK;
};

void TBmp::Draw( int X , int Y )	
{
	PutImage(X, Y, Pic ,Rect.Sx, Rect.Sy);
}

void TBmp::Perror()	
{
	switch( ErrNo )	{
		case ERR_OK: return;
		case ERR_NO_OPEN:
			_Perror( "Unable to open" , Fname ,  NULL );
			return;
		case ERR_NO_READ:
			_Perror( "Can't read" , Fname , NULL );
			return;
		case ERR_NO_MEM:
		case ERR_REALLOC:
			_Perror( "Can't read" , Fname , "not enought memory" , NULL );
			return;
		default :
			_Perror( Fname ); // ?
			return;
	}
}

void TBmp::RPaint(int wx, int wy, int R)	
{
	int Ra = (sqrt(pow(Rect.Sx, 2) + pow(Rect.Sy, 2)) / 2.0);
	
	for (int x = -Ra; x < Ra ; x++) {
		for (int y = -Ra; y < Ra; y++)	{
			float Rb = sqrt(pow(x,2) + pow(y,2));
			float gamma = (Rb == 0.0) ? 0 : asin(y / Rb);
			if (x < 0) {
				gamma = (M_PI - gamma);
			}
			gamma += ((M_PI / 180.0) * R);
			int rx = (cos(gamma) * Rb);
			int ry = (sin(gamma) * Rb);
			if ((abs(rx) <= (Rect.Sx / 2)) && (abs(ry) < (Rect.Sy / 2))) {
				PutPixel(
					wx + x, 
					wy + y, 
					Pic[(rx + Rect.Sx / 2) + (ry + Rect.Sy / 2) * Rect.Sx]
				);
			}
		}
	}
}

void TBmp::RDPaint(int wx, int wy, int R)	
{
	int Ra = (sqrt(pow(Rect.Sx, 2) + pow(Rect.Sy, 2)) / 2.0);
	for (int x = -Ra; x < Ra; x++) {
		for (int y = -Ra; y < Ra; y++) {
			float Rb = sqrt(pow(x, 2) + pow(y, 2));
			float gamma = (Rb == 0.0) ? 0 : asin(y / Rb);
			if (x<0) {
				gamma = (M_PI - gamma);
			}
			gamma += ((M_PI / 180.0) * R);
			int rx = (cos(gamma) * Rb);
			int ry = (sin(gamma) * Rb);
			if ((abs(rx) <= (Rect.Sx / 2)) && (abs(ry) < (Rect.Sy / 2))) {
				register char col = Pic[(rx + Rect.Sx / 2) + (ry + Rect.Sy / 2) * Rect.Sx];
				if (col != DeadColor) {
					PutPixel(wx + x, wy + y, col) ;
				}
			}
		}
	}
}

void TBmp::RPaint(int wx, int wy, int R, float s)	
{
	int Ra = ((sqrt(pow(Rect.Sx, 2) + pow(Rect.Sy, 2)) / 2.0) / s);
	for (int x = -Ra; x < Ra; x++) {
		for (int y = -Ra; y < Ra; y++) {
			float Rb = sqrt(pow(x, 2) + pow(y, 2));
			float gamma = (Rb == 0.0) ? 0 : asin(y / Rb);
			if (x < 0) {
				gamma = (M_PI - gamma);
			}
			gamma += ((M_PI / 180.0) * R);
			int rx = (cos(gamma) * Rb);
			int ry = (sin(gamma) * Rb);
			if ((abs((rx * s)) <= (Rect.Sx / 2)) && (abs((ry * s)) < (Rect.Sy / 2))) {
				PutPixel(
					wx + x, 
					wy + y,
					Pic[(int(rx * s) + Rect.Sx / 2) + (int(ry * s) + Rect.Sy / 2) * Rect.Sx]
				);
			}
		}
	}
}
