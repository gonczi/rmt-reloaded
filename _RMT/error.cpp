/******************************************************************************
												error.cpp
*******************************************************************************/

#ifndef _ERRORS
	#define _ERRORS

#include "typedef.cpp"
#include <stdio.h>
#include <conio.h>
void Perror( char *str );
void _Perror( char *str, ... );

#include "scancode.cpp"

void Perror( char *str )	{        // egy soros hiba�zenet
	_Perror( str , NULL );
};

void _Perror( char *str, ... )	{  // �sszetett hiba�zenet
	char * *arg=&str;
	int n=0;
	printf("Error: ");
	n=0;
	while ( arg[n]!=NULL ) 		{
		printf("%s ", arg[n++] );
	}
	printf("\n");

#ifdef _SCANCODE_CPP                // ha a DOS pillenty�zet szolg�latat�sai
	if ( _ScanOn ) {                 // nem el�rhet�ek
			printf(" press: ESC !!! ");
			while ( !ESC );
			while ( ESC );
	}	else
#endif //_SCANCODE_CPP              // k�l�nben a szok�sos
		getch();
}
#endif // _ERRORS
