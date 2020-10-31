#define STEP 9
#define R    2
#define SIZEX 50
#define SIZEY 50

#include <graphics.h>
//#define  point  pointtype

#include "mouse.cpp"

#include <io.h>
#include <stdio.h>
#include <conio.h>
#include <iostream.h>

#include <fcntl.h>
#include <stdlib.h>
#include <dir.h>

#include "list.cpp"

typedef char table[SIZEX][SIZEY];

//-----------------------globals:---------------------------------------
	char filename[20];
	char str_tbl[20];
	char str_oty[20];
	char str_otb[20];
	int obid=0;
	char paintc=0;
	table tableH,tableV,tableO;

//----------------------------------------------------------------------
char upcase(char in)
{
	return (((in>='a') && (in<='z'))?(in+('A'-'a')):in);
};
void showtable(table t,int tx,int ty)
{
	for ( int x=0 ; x<SIZEX ; x++ )
		for ( int y=0 ; y<SIZEY ; y++ )
		{
			putpixel( tx+x, ty+y, t[x][y]);
		}
}
int Oabs(int num)
{	return( (num>0)?num:(-num) ); };

int Opolar(int num)
{	return( num?((num>=0)?1:-1 ):0); };

struct o_type
{
	char name[40];
	int id;
	char c;
	o_type* next;
}* othead=NULL;

void getmousepoz(point &poz)
{
	poz.x=MouseX();
	poz.y=MouseY();
};

int instep(int poz)
{	return ((poz/STEP)*STEP)+(STEP/2); };

int Oputsign(point poz,char c,char r)
{
	if ( (poz.x<((SIZEX * STEP-(STEP>>1))-1)) && (poz.y<(SIZEY * STEP-(STEP>>1))) )
	{
		setcolor(c);
		HideMouse();
		circle(instep(poz.x),instep(poz.y), r );
		ShowMouse();
		return 1;
	} else return 0;
};


void rowcat(elem *output,o_type* wt,elem *next)
{
	strcpy(output->szov,"id:");
	char sid[4];
	itoa(wt->id,sid,10);
	strcat(output->szov,sid);

	strcat(output->szov," c:");
	char sc[4];
	itoa(wt->c,sc,10);
	strcat(output->szov,sc);

	strcat(output->szov," ");
	strcat(output->szov,wt->name);

	output->id=wt->id;
	output->next=next;
};
#define NUM 0
#define STR 1
void readline(int mode,char *str,int length,int y)
{
	char bill=0;
	int l=0;
	while( ( ((bill=getch())!=13) & (l<length) ) | (l==0) )
	{
		bar(	(SIZEX * STEP),
				(getmaxy()/2)+y,
				getmaxx(),
				(getmaxy()/2)+y+8 );
		if (	( (bill>='0') & (bill<='9') & (mode==NUM) ) |
				( (bill>='a') & (bill<='z') & (mode==STR) ) |
				( (bill>='A') & (bill<='Z') & (mode==STR) )  )
		{
			str[l++]=bill;
		};
		if (	bill==8  )
		{
				str[l?--l:0]=0;
		};
		outtextxy( 	(SIZEX * STEP),
						(getmaxy()/2)+y,
						str );
	}
}

list* otlist;
elem* ohead=NULL;

void showconsol()
{
	setfillstyle(1,1);
	bar(	(SIZEX * STEP),
			(getmaxy()/2)+70,
			getmaxx(),
			getmaxy() );
};
void hideconsol()
{
	setfillstyle(0,1);
	bar(	(SIZEX * STEP),
			(getmaxy()/2)+70,
			getmaxx(),
			getmaxy() );
};
void newtype()
{
	showconsol();
	setcolor(WHITE);
	outtextxy( 	(SIZEX * STEP),
					(getmaxy()/2)+72,
					" new type's name:(q)" );

	char str[40];
	for ( int l=0 ;  l<40 ; str[l++]=0 );
	readline(STR,str,40,82);
	if ( (upcase(str[0])=='Q') && (str[1]==0) )
	{
		hideconsol();
		return;
	};
	outtextxy( 	(SIZEX * STEP),
					(getmaxy()/2)+92,
					"   new type's id: " );
	char sid[10];
	for ( l=0 ;  l<10 ; sid[l++]=0 );
	readline(NUM,sid,6,102);


	outtextxy( 	(SIZEX * STEP),
					(getmaxy()/2)+112,
					"new type's color: " );
	char sc[4];
	for ( l=0 ;  l<4 ; sc[l++]=0 );
	readline(NUM,sc,2,122);

	o_type* wt=new o_type;
	strcpy(wt->name,str);
	wt->id=atoi(sid);
	wt->c=atoi(sc);
	wt->next=othead;
	othead=wt;

	elem* uj=new elem;
	rowcat(uj,wt,ohead);
	ohead=uj;

	otlist->refresh(ohead);
	hideconsol();
};
void delelem(int id)
{
	if ( id )
	{
		elem* puff=ohead;
		if ( puff->id==id )
		{
			puff=ohead->next;
			delete ohead;
			ohead=puff;
		}	else
			{
				while ( (puff->next!=NULL) && (puff->next->id!=id) ) puff=puff->next;
				elem* puff2=puff->next->next;
				delete puff->next;
				puff->next=puff2;
			};
	}
};
void deltype(int id)
{
	if ( id )
	{
		o_type* puff=othead;
		if ( puff->id==id )
		{
			puff=othead->next;
			delete othead;
			othead=puff;
		}	else
			{
				while ( (puff->next!=NULL) && (puff->next->id!=id) ) puff=puff->next;
				o_type* puff2=puff->next->next;
				delete puff->next;
				puff->next=puff2;
			};
	}
}
char getpaintc(int id)
{
	o_type *puff=othead;
	while ( (puff!=NULL) & (puff->id!=id) ) puff=puff->next;
	return ( (puff==NULL)?0:puff->c );
};

void refresh()
{

	for ( int x=0 ; x<(SIZEX * STEP) ; x+=STEP )
		for ( int y=0 ; y<(SIZEY * STEP) ; y+=STEP )
		{
			setcolor((tableV[x/STEP][y/STEP]));
			line(x,y+1,x,y+STEP-1);

			setcolor((tableH[x/STEP][y/STEP]));
			line(x+1,y,x+STEP-1,y);

			point poz;
			poz.x=x;
			poz.y=y;

			Oputsign(poz,getpaintc(tableO[x/STEP][y/STEP]),R);
			putpixel(x,y,LIGHTGRAY);
		};
};

void main()
{
	othead=new o_type;
	strcpy(othead->name,"- CLEAR -");
	othead->id=obid;
	othead->c=paintc;
	othead->next=NULL;

	ohead=new elem;
	rowcat(ohead,othead,NULL);
	for ( int tx=0 ; tx<SIZEX ; tx++ )
		for ( int ty=0 ; ty<SIZEY ; ty++ )
		{
			tableH[tx][ty]=tableO[tx][ty]=tableV[tx][ty]=0;
		}

	clrscr();
	for ( int b=0 ; b<80 ; b++ )putch('*');
	cout << "\n\tOWL  objects \n\n";
	for ( b=0 ; b<80 ; b++ )putch('*');
	int f=0;
	do
	{
		cout <<"\nfiles' name: ",
		cin  >> filename ;
		if ( (filename[0]=='q') & (filename[1]==0) ) return;
		strcpy(str_tbl,filename);
		strcat(str_tbl,".tbl");
		strcpy(str_oty,filename);
		strcat(str_oty,".oty");
		strcpy(str_otb,filename);
		strcat(str_otb,".otb");
	} while ( (f=open(str_tbl,O_BINARY))==-1 );
	if ( 	(read(f,tableH,sizeof(table))==sizeof(table)) &
			(read(f,tableV,sizeof(table))==sizeof(table)) )
		cout << " tbl read ok\n ";
		else cout <<" tbl read error\n";
	close(f);

	if ( (f=open(str_oty,O_BINARY | O_CREAT))!=-1 )
	{
		cout << "open oty ok\n";
		o_type  * puff=new o_type;
		while ( read(f,puff,sizeof( o_type ))==sizeof( o_type ) )
		{
			printf("%s\n",puff->name);
			puff->next=othead;
			othead=puff;
			puff=new o_type ;
		}
		delete puff;
		close(f);
		puff=othead;
		while ( puff->next!=NULL )
		{
			elem* uj=new elem;
			rowcat(uj,puff,ohead);
			ohead=uj;
			puff=puff->next;
		};
		cout << " wty ok\n ";
	}	else
		{
			cout<<" error open .oty ";
			return;
		};

	if ( (f=open(str_otb,O_BINARY | O_CREAT | O_RDWR))!=-1 )
	{
		if ( read(f,tableO,sizeof(table)) ==sizeof(table) )
		{
			cout<< " read tableO ok \n" ;
			close(f);
		}	else
				{
					cout<< " read tableO default \n" ;
					if ( write(f,tableO,sizeof(tableO)) ==sizeof(table) )
					{
						cout<< " write tableO ok \n" ;
						close(f);
					}	else return;
				};
	} else
		{
			cout<<" error open .otb ";
			return;
		};

	getch;

	int gr=DETECT , md;
	initgraph( &gr , &md , "C:\\bc45\\bgi" );


	refresh();
	otlist=new list(	(SIZEX * STEP),
							0,
							getmaxx()-(SIZEX * STEP),
							getmaxy()/2,
							ohead	);
	ShowMouse();

	int exit=1;

	mouse_x_limit(0,(SIZEX-1) * STEP);
	mouse_y_limit(0,(SIZEY-1) * STEP);
	while ( exit )
	{
		if ( kbhit() )
		{
			char bill=getch();
			if ( bill )
			{
				switch(upcase(bill))
				{
					case 'S' :
									int f;
							if ( filename[0]==0 )
							{
									showconsol();
									outtextxy( 	(SIZEX * STEP),
													(getmaxy()/2)+72,
													"- save (else q) -" );
									outtextxy( 	(SIZEX * STEP),
													(getmaxy()/2)+82,
													"files name:" );
									for ( int l=0 ;  l<40 ; filename[l++]=0 );
									readline(STR,filename,40,92);
									if ( (upcase(filename[0])=='Q') && (filename[1]==0) )
									{
										hideconsol();
										return;
									};
							};
									strcpy(str_otb,filename);
									strcat(str_otb,".otb");
									strcpy(str_oty,filename);
									strcat(str_oty,".oty");
									if ( (f=open(str_otb,O_BINARY | O_CREAT | O_TRUNC | O_RDWR))==-1 )
									{
										showconsol();
										outtextxy( 	(SIZEX * STEP),
													(getmaxy()/2)+72,
													"- oty open error ... -" );
										getch();
									}	else
										{
											if ( write(f,tableO,sizeof(table)) != sizeof(table) )
											{
												showconsol();
												outtextxy( 	(SIZEX * STEP),
																(getmaxy()/2)+72,
																"- otb write error ... -" );
												getch();
											}	else close(f);
										}
									if ( (f=open(str_oty,O_BINARY | O_CREAT | O_TRUNC | O_RDWR))==-1 )
									{
										showconsol();
										outtextxy( 	(SIZEX * STEP),
													(getmaxy()/2)+72,
													"- oty open error ... -" );
										getch();
									 }	else
											{
												o_type *puff=othead;
												while( puff!=NULL )
												{
													if ( puff->id!=0 )
														write(f,puff,sizeof(o_type));
													puff=puff->next;
												}
												close(f);
											};
									hideconsol();
					case 'Q' :
									showconsol();
									outtextxy( 	(SIZEX * STEP),
													(getmaxy()/2)+72,
													"- exit without save -" );
									outtextxy( 	(SIZEX * STEP),
													(getmaxy()/2)+82,
													"are you sure ? (y/n)" );
									if ( upcase(getch())=='Y' )
									exit=0;
									hideconsol();
									break;
					case 'N':
									newtype();
									break;
					case 'D':
									showconsol();
									setcolor(WHITE);
									outtextxy( 	(SIZEX * STEP),
													(getmaxy()/2)+72,
													"- delete this type -" );
									outtextxy( 	(SIZEX * STEP),
													(getmaxy()/2)+82,
													"are you sure ? (y/n)" );
									if ( upcase(getch())=='Y' )
									{
										deltype(obid);
										delelem(obid);
										otlist->refresh(ohead);
									};
									hideconsol();
									break;
				}
			}	else
				{
					bill=getch();
					switch(bill)
					{
						case 72: otlist->up();
									break;
						case 80: otlist->down();
									break;
						default: ;
					};
				};
			paintc=getpaintc(obid=otlist->getid());
		};
		if ( MouseClick()!=0 )
		{
			point poz;
			getmousepoz(poz);
			if ( Oputsign(poz,getpaintc(obid),R) )
				tableO[poz.x/STEP][poz.y/STEP]=obid;
		}
	}
}