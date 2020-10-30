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

void Perror( char *str )	{        // egy soros hibaüzenet
	_Perror( str , NULL );
};

void _Perror( char *str, ... )	{  // összetett hibaüzenet
	char * *arg=&str;
	int n=0;
	printf("Error: ");
	n=0;
	while ( arg[n]!=NULL ) 		{
		printf("%s ", arg[n++] );
	}
	printf("\n");

#ifdef _SCANCODE_CPP                // ha a DOS pillentyüzet szolgálatatásai
	if ( _ScanOn ) {                 // nem elérhetõek
			printf(" press: ESC !!! ");
			while ( !ESC );
			while ( ESC );
	}	else
#endif //_SCANCODE_CPP              // különben a szokásos
		getch();
}
#endif // _ERRORS
