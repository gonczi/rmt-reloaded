//******************************************************************************
// main
//******************************************************************************
long _SpeedNum=0;               
#include "typedef.cpp"
#include "error.cpp"
#include "scancode.cpp"
#include "graph13.cpp"
#include "timer.cpp"
#include "intro.cpp"
#include "obj.cpp"
#include "pic_serv.cpp"
#include "init.cpp"
#include "fileinsp.cpp"
#include "gameover.cpp"
// Global:
	int GLevel=1;
main()	{
	if ( !FileInspecor() ) return -1;
//*************************************************************** INIT *********
	Init13();
	InitMainPal();
	InitScan();
	InstallTimer();
//*************************************************************** INTRO ********
	TIntro *Intro=new TIntro();
	delete Intro;
//**************************************************************** GAME ********
	do	{
		TMenu *Menu=new TMenu();
		delete Menu;
		GLevel=1;
		while ( GLevel>0 )	{
			new TInit( GLevel );
			GLevel=TLoop::Start();
			FlushTimer();
			PicServer::FreeAll();
		};
		if ( GLevel==-1 ) GameOver();
	}	while ( GLevel==-1 );
//**************************************************************** END *********
	ResumeTimer();
	DoneScan();
	Done13();
	return 0;
};