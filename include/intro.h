#ifndef _INTRO_CPP
# define _INTRO_CPP

#include "typedef.h"
#include "timer.h"

class TIntro: TTimer
{
	BOOL Quit;
public:
	static const char *IntroFiles[];
	TIntro();
};

#endif // _INTRO_CPP