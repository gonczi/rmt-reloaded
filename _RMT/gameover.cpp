//******************************************************************************
// gameover.cpp
//******************************************************************************
#ifndef _GAMEOVER_CPP
	#define _GAMEOVER_CPP
// a "vége a játéknak" felirat kirajzoló eljárása
#include "pic_Serv.cpp"
void GameOver()	{
	TBmp *Pic=*(TBmp **)PicServer::GetPic( TSC_GAMEOVER );
	Pic->Draw( 160-Pic->X/2 , 100-Pic->Y/2 );
	while (  KbHit() );
	while ( !KbHit() );
	while (  KbHit() );
	PicServer::Free( TSC_GAMEOVER );
}
#endif // _GAMEOVER_CPP
