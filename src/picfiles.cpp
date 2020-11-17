#include "picfiles.h"

#include <stdio.h>
#include <string.h>

PicFile::PicFile ( TMainPicType iPType , int iId , char * iFName)	{
	PType=iPType;
	Id=iId;
	FName = iFName;
	Bmp=NULL;
	Users=0;
};

PicFile::PicFile ( TMainPicType iPType , int iId , char * iFName[])	{
	PType=iPType;
	Id=iId;

	int n = 0;
	while (iFName[n]) n++;

	FNameArray = new char*[n+1];

	for (int z = 0 ; z < n ; z++) {
		char* fname = iFName[z];
		FNameArray[z] = (char *)calloc(strlen(fname) + 1, 1);
		strcpy(FNameArray[z], fname);
	}

	FNameArray[n] = NULL;
	Bmp=NULL;
	Users=0;
};


// a falkak sz�ma az adott p�ly�n
int WallNum[3]={ 8 , 5 , 0 };

// Pic id kezdete pl : W_Tegla=WallOffset+n...
int WallOffset[3]={ 3000 , 4000 , 5000 };

//******************************************************************************
// a f�jl nevek list�ja:
PicFile Pic_Files[] = {
	PicFile( TPICTURE  , TSC_TICKV , "dashboard/tick_v2" ),
	PicFile( TPICTURE  , TSC_TICKH,  "dashboard/tick_h2"  ),
	PicFile( TPICTURE  ,	TSC_HEAD  , "dashboard/head4"   ),
	PicFile( TPICTURE  , TSC_NOZI  ,  "dashboard/nozi"    ),
	PicFile( TPICTURE  , TSC_EN_ROWS ,   "dashboard/energy" ),
	PicFile( TPICTURE  , TSC_EN_BACK ,   "dashboard/en_bck" ),
	PicFile( TPICTURE  , TSC_POT  ,	"dashboard/pot_ala2" ),
	PicFile( TPICTURE  , TSC_FLOW  ,	"dashboard/flowers" ),
	PicFile( TPICTURE  , TSC_MISSION  ,	"dashboard/mission" ),
	PicFile( TPICTURE  , TSC_BONUS  ,	"dashboard/bonus" ),
	PicFile( TBMP      , TSC_GAMEOVER  ,	"dashboard/gameover" ),

	PicFile( TBMP      , AIR      ,   "walls/galaxis" ),
	PicFile( TPICCLASS , CAT ,	(char*[]) { "player/cat1","player/cat2","player/cat3",
										"player/scat1","player/scat2",NULL } ),
	PicFile( TPICTURE  , CHEESE  ,  "player/ch"  ),
	PicFile( TPICTURE  , BASKET  , "player/kosar3" ),
	PicFile( TPICTURE  , FLOWER  ,	"player/virag" ),
	PicFile( TPICCLASS , TOMATO   ,  (char*[]) { "player/tom2" , "player/tom_plac" , NULL } ) ,

	PicFile( TPICCLASS , MOUSE_CUR , (char*[]) { "cursor/b1" ,"cursor/b2" ,"cursor/b3" , NULL } ),
	PicFile( TBMP      , CHARS      ,   "menu/chars" ),

	PicFile( TPICCLASS , MBUTT_NEW ,
		(char*[]) { "menu/b_new","menu/b_new_a","menu/b_new_b",NULL } ),
	PicFile( TPICCLASS , MBUTT_START ,
		(char*[]) { "menu/b_star","menu/b_star_a","menu/b_star_b",NULL } ),
	PicFile( TPICCLASS , MBUTT_CON ,
		(char*[]) { "menu/b_con","menu/b_con_a","menu/b_con_b",NULL } ),
	PicFile( TPICCLASS , MBUTT_EXI ,
		(char*[]) { "menu/b_exi","menu/b_exi_a","menu/b_exi_b",NULL } ),
	PicFile( TPICCLASS , MBUTT_TOP5 ,
		(char*[]) { "menu/b_top","menu/b_top_a","menu/b_top_b",NULL } ),

	PicFile( TPICCLASS , MBUTT_LEFT ,
		(char*[]) { "menu/b_left","menu/b_left_a","menu/b_left_b",NULL }),
	PicFile( TPICCLASS , MBUTT_RIGHT ,
		(char*[]) { "menu/b_right","menu/b_rig_a","menu/b_rig_b",NULL }),
	PicFile( TPICCLASS , MBUTT_TLEFT ,
		(char*[]) { "menu/b_tleft","menu/b_tlef_a","menu/b_tlef_b",NULL }),
	PicFile( TPICCLASS , MBUTT_TRIGHT ,
		(char*[]) { "menu/b_tright","menu/b_trig_a","menu/b_trig_b",NULL }),
	PicFile( TPICCLASS , MBUTT_BACK ,
		(char*[]) { "menu/b_back","menu/b_back_a","menu/b_back_b",NULL }),
	PicFile( TPICCLASS , MBUTT_FORW ,
		(char*[]) { "menu/b_forw","menu/b_forw_a","menu/b_forw_b",NULL }),
	PicFile( TPICCLASS , MBUTT_FIRE ,
		(char*[]) { "menu/b_fire","menu/b_fire_a","menu/b_fire_b",NULL }),
	PicFile( TPICCLASS , MBUTT_BACKM ,
		(char*[]) { "menu/b_bac","menu/b_bac_a","menu/b_bac_b",NULL }),

	PicFile( TPICCLASS , MBUTT_YES ,
		(char*[]) { "menu/b_yes","menu/b_yes_a","menu/b_yes_b",NULL }),
	PicFile( TPICCLASS , MBUTT_NO  ,
		(char*[]) { "menu/b_no" ,"menu/b_no_a" ,"menu/b_no_b" ,NULL }),
	PicFile( TPICCLASS , MPIC_AYS	, (char*[]) { "menu/butt_ays" , NULL }),
	PicFile( TPICCLASS , MPIC_ENT	, (char*[]) { "menu/ent" , NULL }),
	PicFile( TPICCLASS , MPIC_LEVMAP	, (char*[]) { "menu/levmap" , NULL }),

	PicFile( TBMP ,  MPIC_NYIL	, "menu/nyil"  ),
	PicFile( TBMP ,  MPIC_JELEK	, "menu/jelek" ),
	PicFile( TPICCLASS , MPIC_POINT ,
		(char*[]) { "menu/point_3","menu/point_2","menu/point_1","menu/point_0",NULL }),

	PicFile( TBMP 	, W_TEGLA	,"walls/tegla"    ),
	PicFile( TBMP 	, W_TEGLA2	,"walls/tegla2"  ),
	PicFile( TBMP 	, W_KO		,"walls/ko"       ),
	PicFile( TBMP	, W_KO2		,"walls/ko2"     ),
	PicFile( TBMP	, W_KOTEG	,"walls/koteg"    ),
	PicFile( TBMP	, W_KOTEG2	,"walls/koteg2"  ),
	PicFile( TBMP	, W_RACS	,"walls/racs"    ),
	PicFile( TBMP	, W_RACS2	,"walls/racs2"  ),

	PicFile( TBMP 	, W2_TREE	,"walls/tree"    ),
	PicFile( TBMP 	, W2_TREE2	,"walls/tree2"  ),
	PicFile( TBMP 	, W2_KO		,"walls/ko"       ),
	PicFile( TBMP	, W2_KO2		,"walls/ko2"     ),
	PicFile( TBMP	, W2_BLACK	,"walls/racs"    ),

	PicFile( NOTHING , NOTHING_PID , (char*)NULL )     // z�r� k��d
};
