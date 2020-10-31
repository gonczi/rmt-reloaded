#include <iostream.h>
#include <fstream.h>
#include <conio.h>
#include <string.h>
#include <dir.h>
#include <stdlib.h>

void main()	{
	clrscr();
	cout << "  ***************************************************************************  \n";
	cout << " **                                                                         ** \n";
	cout << "**                 -  Udvozli ont a Mouse Trap telepitoje  -                 **\n";
	cout << " **                                                                         ** \n";
	cout << "  ***************************************************************************  \n\n";
	char telepit[255],path[255];
	do	{
		cout << "Valoban telepiteni szeretne a Mouse Trap programot [Igen\\Nem]:";
		cin >> telepit;
	} while (strlen(telepit)!=1);
	if ( (telepit[0]!='i') && (telepit[0]!='I') )return;
	cout << "Kerem adja meg annak a konyvtarnak a teljes eleresi utvonalat ahova\n";
	cout << "telepiteni szeretne a programot.     Pl.: [C:\\Games\\M_Trap] vagy [A:]\n";
	cout << "(A telepitest barmikor megszakithatja a CTRL+C billentyuk lenyomasaval)\n";
	int ok=0;
	char cdir[256],fullname[255]="";
	fullname[0]=(getdisk()+'A');
	fullname[1]=':';
	fullname[2]='\\';
	fullname[3]=0;
	getcurdir(getdisk()+1,cdir);
	strcat( fullname , cdir );
	if ( strlen(cdir)!=0 )	{
		strcat( fullname , "\\" );
	}
	do {
		cin >> path;
		if ( chdir(path)!=0 )	{
			if ( mkdir(path)!=0 )
				cout << "\nErvenytelen konyvtar, kerem ismetelje meg ujra a bevitelt:\n";
			if ( chdir(path)==0 ) ok=1;
		}	else ok=1;
	} while( ok==0 );
	cout << "konyvtar: OK\n";
	char alibs[256];
	strcpy( alibs, fullname );
	strcat( alibs ,"libs.dat" );
	cout << "open: " << alibs <<'\n';
	fstream libs( alibs , ios::in );
	while ( !libs.eof() )	{
		char newdir[256],ndfull[256];
		libs >> newdir;
		strcpy( ndfull , path );
		strcat( ndfull , "\\" );
		strcat( ndfull , newdir );
		if ( strlen(newdir)>0 )	{
			cout << "NEW DIR: " << ndfull << '\n';
			if ( mkdir( ndfull )==0 )	{
				char mcopy[256];
				strcpy( mcopy , "copy " );
				strcat( mcopy , fullname );
				strcat( mcopy , newdir );
				strcat( mcopy , "\\*.* " );
				strcat( mcopy , ndfull );
				cout << mcopy <<'\n';
				system( mcopy );
			}	else {
					cout << "hiba a telepites folyamataban";
					return;
				}
		}
	}
	libs.close();
	char xlib[256];
	strcpy( xlib, fullname );
	strcat( xlib ,"xfiles.dat" );
	cout << "open: " << xlib <<'\n';
	fstream xfiles( xlib , ios::in );
	cout << "chdir: " << path << '\n';
	chdir(path);
	while ( !xfiles.eof() )	{
		char nxf[256];
		xfiles >> nxf;
		if ( strlen(nxf)>0 )	{
			char mcopy[256];
			strcpy( mcopy , "copy " );
			strcat( mcopy , fullname );
			strcat( mcopy , nxf );
			strcat( mcopy , " " );
			strcat( mcopy , path );
			cout << mcopy <<'\n';
			system( mcopy );
		}
	};
	xfiles.close();
	cout << "\nA telepites befejezodott, a jatekot a START.BAT -al tudja elinditani.";
}
