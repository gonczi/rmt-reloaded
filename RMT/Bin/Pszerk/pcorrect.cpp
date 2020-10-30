#include <io.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>

#include <fcntl.h>
#include <sys\stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "globals.cpp"

typedef char table[SIZEX][SIZEY];

/*
	ez csak azért lett meg írva mert baromi lusta vagyok ...
*///-----------------------globals:---------------------------------------
table tableH,tableV;
char Fname[100],str_tbl[100];
char bill=0;
int OID=0,NID=0;
int f;

void main ()	{
	cout << "file name:";
	cin >> Fname;

	strcpy(str_tbl,Fname);
	strcat(str_tbl,".tbl");

	f=open(str_tbl,O_BINARY);
	if ( f!=-1 )
	{
		cout << "open OK\n";
		cout << "read H: " << read(f , tableH,sizeof(table)) << " bytes\n";
		cout << "read v: " << read(f , tableV,sizeof(table)) << " bytes\n";
		cout << " tbl read ok\n ";
	 }	else 	{
			cout <<" tbl read error\n";
			return;
		}
	close(f);

	cout << "Horizontal or vertical correcting ? ";
	bill=getch();

	cout << "\nold Id: ";
	cin >> OID;
	cout << "old Id:" << OID << '\n';
	cout << "new Id: ";
	cin >> NID;
	cout << "new Id:" << NID << '\n';

	for ( long x=0 ; x<SIZEX ; x++ )	{
		for ( long y=0 ; y<SIZEY ; y++ )	{

			if ( tableH[x][y] || tableV[x][y] )
				cout << (int)tableH[x][y] << (int)tableV[x][y] << ' ' ;

			if ( bill=='h' )	{
				if ( (int)tableH[x][y] == OID ) 	{
					tableH[x][y] = NID;
					cout << "change H :" << x << ' ' << y << '\n';
				}
			} 	else	{
					if ( (int)tableV[x][y] == OID ) {
						tableV[x][y] = NID;
						cout << "change V :" << x << ' ' << y << '\n';
					}
				}
		}
		cout << " -\n";
	}

	if ( (f=open(str_tbl , O_RDWR | O_BINARY , S_IWRITE  ))!=-1 )	{
		cout << f << " open OK\n";
		cout << "write H: " << write(f , tableH , sizeof(table) ) << " bytes errno: " << errno << '\n' ;
		cout << "write V: " << write(f , tableV , sizeof(table) ) << " bytes errno: " << errno << '\n';
		cout << EACCES	<< ": Permission denied\n";
		cout << EBADF	<< ": Bad file number\n";
		cout << " tbl write ok\n ";
	}	else 	{
			cout <<" tbl write error\n";
			return;
		}

	close(f);
	getch();
}
