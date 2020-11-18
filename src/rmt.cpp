// #include "typedef.h"
// #include "error.cpp"
#include "scancode.h"
#include "graph13.h"
#include "timer.h"
#include "intro.h"
#include "rmt_menu.h"

// #include "obj.cpp"
// #include "pic_serv.cpp"
#include "init.h"
#include "fileinsp.h"
// #include "gameover.cpp"

#include <stdio.h>
#include <unistd.h>

int GLevel = 1;

int main()
{
	if (!FileInspecor()) {
        return -1;
    }
//*************************************************************** INIT *********
	Init13();
	InitMainPal();
	InitScan();
	InstallTimer();
//*************************************************************** INTRO ********
	TIntro *Intro = new TIntro();
	delete Intro;
//**************************************************************** GAME ********
	do	{
		TMenu *Menu = new TMenu( 0 );
		delete Menu;
		GLevel=1;
		while ( GLevel>0 )	{
			new TInit( GLevel );
			GLevel=TLoop::Start();
			FlushTimer();
			PicServer::FreeAll();
		};
		// if ( GLevel==-1 ) GameOver();
	}	while ( GLevel==-1 );
//**************************************************************** END *********
	ResumeTimer();
	DoneScan();
	Done13();

	return 0;
}
