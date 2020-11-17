#ifndef _TME_CPP
	#define _TME_CPP

// // a j�t�kost reprezent�l� objektum defin�ci�ja
// #include <math.h>
// #include <time.h>
// #include "globals.cpp"
// #include "scancode.cpp"
#include "obj.h"
#include "grobj.h"
#include "timer.h"
#include "motor.h"
// #include "pic_serv.cpp"
#include "scrobj.h"
#include "energy.h"
// #include "bang.cpp"
// #include "bonus.cpp"
#include "rmt_map.h"
#include "counter.h"

// billenyt� k�dok
// typedef enum CKeyNum{ 	C_FORW , C_BACKW  , C_TLEFT ,
// 								C_TRIGHT , C_LEFT , C_RIGHT , C_FIRE };

// alap�rtelmez�s szerinti billenty� be�ll�t�sok a scan k�d alapj�n:
extern int CKey[7];

// #define  NMAX  10         // az orr mozg�s�nak maxim�lis �rt�ke

// int  K		=20;		// fordul�si sz�g   (166 MHz)
extern int  STEP;		// l�p�s t�vols�g
// long Rsize	=0;		//(SCR/10);
// int  MIN=	143; 		// minim�lis falmegk�zel�t�si t�vols�g

// #define MAXFLOWERS 7 // az �sszegy�jtend� vir�gok sz�ma

// #include "Tomato.cpp"

// #define GUN_Tomato 0  // l�ved�k t�pus t�mb azonos�t�ja
#define GUN_NUM 1     // l�ved�k t�pusok sz�ma

class	TMe: TObj , TTimer ,public TPozition
{
	TMap * Map;                   // t�rk�p mutat�
	TMotor *Motor;                // motor  mutat�ja
	TScrObj * Head;               // a fej Screen obj. mutat�ja
	TScrObj * Nozi;               // az orr Screen obj. mutat�ja
	TScrObj * FlowPic;            // a vir�gok sz�m�t jelz� Screen obj.-ok mutat�ja
	TScrObj * Mission;            // a k�ldet�s teljes�t�s�t jelz� Screen obj. mutat�ja
	TCounter *Counter;            // a l�ved�k sz�m kijelz� mutat�ja
	TEnergy * Energy;             // az energia kijelz� muta�ja
	void Left()		;              // fordul balra
	void Right()	;              // fordul jobbra
	void Forward() ;              // egy l�p�s el�re
	void Backward();              // egy l�p�s h�tra
	POINT HeadPoz;                // a fej pozici�ja a k�perny�n
	int HeadTop;                  // a fej aktu�lis emel�se
	POINT NoziPoz;                // az orr pozici�ja a k�perny�n
	int NoziTop,NoziShift;        // az orr eltol�sai vizszintes ill. f�gg. ir�nyban
	BOOL Shuting;                 // l�v�s folyamatban jelz�
	long LastTime;                // a legut�bbi l�ved�k indu�sakor m�rt id�
	int Gun[ GUN_NUM ];           // a fegyverek t�pusai
	int GunNow;                   // a jelenlegi fegyver azonos�t�
	int Flowers;                  // az �sszegy�jt�tt vir�gok sz�ma
	int MissionCounter;           // sz�ml�l� a p�lya befelyez�s�t�l az j�t�k v�g�ig
	BOOL TimeSet;                 // seg�d v�ltoz� az id�z�t� megsz�ntet�s�hez
	BOOL Protection;              // v�delem a p�lya teljes�t�sekor
	int Level;                    // az aktu�lis p�lya sz�ma
	int ShutCount;                // a legut�bbi l�ved�k indu�s�t�l m�rt id�
	long Time; // :)              // a j�t�k kezdetekort m�rt id�
public:
	static char UserName[];       // a j�t�kos megadott neve
	static long UserTime;         // a j�t�kos �lltal teljes�tett id�
	int Trapp;                    //
	virtual void Proc();
	virtual void MsgProc ( void * , unsigned Msg , unsigned long, unsigned long );
	TMe( int );
	~TMe();
	virtual void TimerProc( int );
};

#endif // _TME_CPP
