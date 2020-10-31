#include <fstream.h>
#include <iostream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <io.h>


char com[256],filen[256];

void rfopen( char *fname )	{
	fstream file( fname , ios::in );
	while ( !file.eof() )	{
		file >> com;
		file >> filen;
		if ( com[0]=='#' && com[1]=='i' && com[2]=='n' )	{
			cout << filen << '\n';
		}
	}
}

void main ()	{
	rfopen ("rmt.cpp");
	getch();
}