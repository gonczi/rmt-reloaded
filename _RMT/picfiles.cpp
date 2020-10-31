/******************************************************************************
				picfiles.cpp
******************************************************************************/
#ifndef _PICFILES_CPP
	#define _PICFILES_CPP
// a kép kiszolgáló által használt kép fájlok nevei, formátumai

//  kép típusok, és a lista záró kód:
typedef enum TMainPicType{ TBMP , TPICTURE , TPICCLASS , NOTHING=-1 };
class PicFile	{     // fájlnév és betöltési tulajdonságainak leírója
public:
	TMainPicType PType;      // típus
	int Id;                  // azonosító
	int Users;               // felhasználók száma
	union {
		char * *FNameArray;     // fájl nevek
		char *  FName;          // vagy fájl név
	};
	union {
		TBmp  		*Bmp;         // kép címe különbözõ formátumban
		TPicture  	*Picture;
		TPicClass 	*PicClass;
	};
	PicFile ( TMainPicType iPType , int iId , char * iFName, ... );
	~PicFile ()	{
	};
};
//******************************************************************************
PicFile::PicFile ( TMainPicType iPType , int iId , char * iFName, ... )	{
	PType=iPType;
	Id=iId;
	if ( PType==TPICCLASS )	{
		int n=0;
		while ( (&iFName)[n] )n++;
		FNameArray =(char **)calloc(sizeof(char *) , n+1 );
		for ( int z=0 ; z<n ; z++ )	{
			FNameArray[z]=(char *)calloc(strlen((&iFName)[z])+1,1);
			strcpy(FNameArray[z],(&iFName)[z]);
		}
		FNameArray[z]=NULL;
	}	else {
			FName = iFName;
		}
	Bmp=NULL;
	Users=0;
};
//*****************************************************************************
// a falkak száma az adott pályán
const int WallNum[3]={ 8 , 5 , 0 };
// Pic id kezdete pl : W_Tegla=WallOffset+n...
const int WallOffset[3]={ 3000 , 4000 , 5000 };
// kép azoonosító számok kiosztása, nevesítése:
typedef enum PicId{  NOTHING_PID=-1,
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
//******************************************************************************
// a fájl nevek listája:
static PicFile Pic_Files[]={
	PicFile( TPICTURE  , TSC_TICKV , "consol\\tick_v2" ),
	PicFile( TPICTURE  , TSC_TICKH,  "consol\\tick_h2"  ),
	PicFile( TPICTURE  ,	TSC_HEAD  , "consol\\head4"   ),
	PicFile( TPICTURE  , TSC_NOZI  ,  "consol\\Nozi"    ),
	PicFile( TPICTURE  , TSC_EN_ROWS ,   "consol\\energy" ),
	PicFile( TPICTURE  , TSC_EN_BACK ,   "consol\\en_BCK" ),
	PicFile( TPICTURE  , TSC_POT  ,	"consol\\pot_ala2" ),
	PicFile( TPICTURE  , TSC_FLOW  ,	"consol\\flowers" ),
	PicFile( TPICTURE  , TSC_MISSION  ,	"consol\\MISSION" ),
	PicFile( TPICTURE  , TSC_BONUS  ,	"consol\\BONUS" ),
	PicFile( TBMP      , TSC_GAMEOVER  ,	"consol\\GAMEOVER" ),

	PicFile( TBMP      , AIR      ,   "Walls\\galaxis" ),
	PicFile( TPICCLASS , CAT ,	"gamer\\cat1","gamer\\cat2","gamer\\cat3",
										"gamer\\scat1","gamer\\scat2",NULL),
	PicFile( TPICTURE  , CHEESE  ,  "gamer\\ch"  ),
	PicFile( TPICTURE  , BASKET  , "gamer\\kosar3" ),
	PicFile( TPICTURE  , FLOWER  ,	"gamer\\virag" ),
	PicFile( TPICCLASS , TOMATO   ,  "gamer\\tom2" , "gamer\\tom_plac" , NULL ) ,

	PicFile( TPICCLASS , MOUSE_CUR , "cursor\\b1" ,"cursor\\b2" ,"cursor\\b3" , NULL ),
	PicFile( TBMP      , CHARS      ,   "menu\\chars" ),

	PicFile( TPICCLASS , MBUTT_NEW ,
		"menu\\b_New","menu\\b_New_a","menu\\b_New_b",NULL ),
	PicFile( TPICCLASS , MBUTT_START ,
		"menu\\b_STAR","menu\\b_STAR_a","menu\\b_STAR_b",NULL ),
	PicFile( TPICCLASS , MBUTT_CON ,
		"menu\\b_Con","menu\\b_Con_a","menu\\b_Con_b",NULL ),
	PicFile( TPICCLASS , MBUTT_EXI ,
		"menu\\b_Exi","menu\\b_Exi_a","menu\\b_Exi_b",NULL ),
	PicFile( TPICCLASS , MBUTT_TOP5 ,
		"menu\\b_top","menu\\b_top_a","menu\\b_top_b",NULL ),

	PicFile( TPICCLASS , MBUTT_LEFT ,
		"menu\\b_left","menu\\b_left_a","menu\\b_left_b",NULL ),
	PicFile( TPICCLASS , MBUTT_RIGHT ,
		"menu\\b_right","menu\\b_rig_a","menu\\b_rig_b",NULL ),
	PicFile( TPICCLASS , MBUTT_TLEFT ,
		"menu\\b_tleft","menu\\b_tlef_a","menu\\b_tlef_b",NULL ),
	PicFile( TPICCLASS , MBUTT_TRIGHT ,
		"menu\\b_tright","menu\\b_trig_a","menu\\b_trig_b",NULL ),
	PicFile( TPICCLASS , MBUTT_BACK ,
		"menu\\b_BACK","menu\\b_BACK_a","menu\\b_BACK_b",NULL ),
	PicFile( TPICCLASS , MBUTT_FORW ,
		"menu\\b_FORW","menu\\b_FORW_a","menu\\b_FORW_b",NULL ),
	PicFile( TPICCLASS , MBUTT_FIRE ,
		"menu\\b_FIRE","menu\\b_FIRE_a","menu\\b_FIRE_b",NULL ),
	PicFile( TPICCLASS , MBUTT_BACKM ,
		"menu\\b_bac","menu\\b_bac_a","menu\\b_bac_b",NULL ),

	PicFile( TPICCLASS , MBUTT_YES ,
		"menu\\b_yes","menu\\b_yes_a","menu\\b_yes_b",NULL ),
	PicFile( TPICCLASS , MBUTT_NO  ,
		"menu\\b_no" ,"menu\\b_no_a" ,"menu\\b_no_b" ,NULL ),
	PicFile( TPICCLASS , MPIC_AYS	, "menu\\butt_ays" , NULL ),
	PicFile( TPICCLASS , MPIC_ENT	, "menu\\ent" , NULL ),
	PicFile( TPICCLASS , MPIC_LEVMAP	, "menu\\LEVMAP" , NULL ),

	PicFile( TBMP ,  MPIC_NYIL	, "menu\\nyil"  ),
	PicFile( TBMP ,  MPIC_JELEK	, "menu\\jelek"  ),
	PicFile( TPICCLASS , MPIC_POINT ,
		"menu\\point_3","menu\\point_2","menu\\point_1","menu\\point_0",NULL ),

	PicFile( TBMP 	, W_TEGLA	,"walls\\tegla"    ),
	PicFile( TBMP 	, W_TEGLA2	,"walls\\tegla2"  ),
	PicFile( TBMP 	, W_KO		,"walls\\ko"       ),
	PicFile( TBMP	, W_KO2		,"walls\\ko2"     ),
	PicFile( TBMP	, W_KOTEG	,"walls\\koteg"    ),
	PicFile( TBMP	, W_KOTEG2	,"walls\\koteg2"  ),
	PicFile( TBMP	, W_RACS	,"walls\\RACS"    ),
	PicFile( TBMP	, W_RACS2	,"walls\\RACS2"  ),

	PicFile( TBMP 	, W2_TREE	,"walls\\tree"    ),
	PicFile( TBMP 	, W2_TREE2	,"walls\\tree2"  ),
	PicFile( TBMP 	, W2_KO		,"walls\\ko"       ),
	PicFile( TBMP	, W2_KO2		,"walls\\ko2"     ),
	PicFile( TBMP	, W2_BLACK	,"walls\\racs"    ),

	PicFile( NOTHING , NOTHING_PID , NULL )     // záró kóód
};
#endif // _PICFILES_CPP
