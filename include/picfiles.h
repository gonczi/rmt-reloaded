#ifndef _PICFILES_CPP
	#define _PICFILES_CPP

#include "bmp.h"
#include "picture.h"
#include "picclass.h"

//  k�p t�pusok, �s a lista z�r� k�d:
enum TMainPicType{ TBMP , TPICTURE , TPICCLASS , NOTHING=-1 };

class PicFile	{     // f�jln�v �s bet�lt�si tulajdons�gainak le�r�ja
public:
	TMainPicType PType;      // t�pus
	int Id;                  // azonos�t�
	int Users;               // felhaszn�l�k sz�ma
	union {
		char * *FNameArray;     // f�jl nevek
		char *  FName;          // vagy f�jl n�v
	};
	union {
		TBmp  		*Bmp;         // k�p c�me k�l�nb�z� form�tumban
		TPicture  	*Picture;
		TPicClass 	*PicClass;
	};
	
	PicFile (TMainPicType iPType , int iId , char *iFName);
	PicFile (TMainPicType iPType , int iId , char *iFName[]);
	~PicFile ()	{ ; };
};

//*****************************************************************************

// a falkak sz�ma az adott p�ly�n
extern int WallNum[3];
// Pic id kezdete pl : W_Tegla=WallOffset+n...
extern int WallOffset[3];
// a f�jl nevek list�ja:
extern PicFile Pic_Files[];

// k�p azoonos�t� sz�mok kioszt�sa, neves�t�se:
enum PicId{  NOTHING_PID=-1,
							TSC_TICKV=0 , TSC_TICKH , TSC_HEAD ,
							TSC_NOZI , TSC_EN_ROWS , TSC_EN_BACK ,
							TSC_POT , TSC_FLOW , TSC_MISSION , TSC_GAMEOVER ,
							TSC_BONUS,

							AIR=1000 , CAT , CHEESE , BASKET , FLOWER , TOMATO ,

							MOUSE_CUR=1500 ,CHARS,

							MBUTT_NEW=2000 , MBUTT_CON , MBUTT_EXI , MBUTT_YES , MBUTT_NO ,
							MPIC_AYS , MPIC_NYIL , MBUTT_LEFT , MBUTT_RIGHT , MBUTT_FORW , MBUTT_BACK ,
							MBUTT_FIRE , MBUTT_TLEFT , MBUTT_TRIGHT , MBUTT_BACKM ,
							MBUTT_START, MPIC_ENT , MPIC_POINT , MBUTT_TOP5 ,
							MPIC_JELEK , MPIC_LEVMAP ,

							W_TEGLA=3000 , W_TEGLA2, W_KO, W_KO2, W_KOTEG ,
									W_KOTEG2 , W_RACS , W_RACS2,

							W2_TREE=4000 , W2_TREE2 , W2_KO , W2_KO2 , W2_BLACK ,

							};

#endif // _PICFILES_CPP
