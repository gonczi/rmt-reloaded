//******************************************************************************
// gameover.cpp
//******************************************************************************
#ifndef _GAMEOVER_CPP
	#define _GAMEOVER_CPP
// a "v�ge a j�t�knak" felirat kirajzol� elj�r�sa
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
