#include <string.h>

struct listtag
{
	listtag *prev,* next;
	char str[40];
	int  id;
};

struct elem
{
	char szov[40];
	int id;
	elem * next;
};

class list
{
protected:
	int x,y,width,height;
	int max;
	int line;
	listtag *head,* now;
	int row;
	char color,tcolor;
	int fonttop;
	int fontwidth;
	void puttext(int rows,char *str);
	void activeline();
	void inactiveline();
public:
	list(int ix,int iy,int iwidth,int iheight,elem *ihead);
	void refresh(elem *ihead);
	void up();
	void down();
	int  getid();
};

int list::getid()
{
	return now->id ;
};

list::list(int ix,int iy,int iwidth,int iheight,elem *ihead)
{
	x=ix;
	y=iy;
	width=iwidth;
	height=iheight;
	color=	2;
	tcolor=	15;
	fonttop= (2+textheight("bla"));
	fontwidth= textwidth("W");
	head=NULL;
	refresh(ihead);
};
void list::puttext(int rows,char *str)
{
		char strout[40];
		strcpy(strout,str);
		if ( textwidth(strout)>width )
			strout[width/fontwidth]='\0';
		outtextxy(x+2,y+2+rows*fonttop,strout);
};
void list::refresh(elem *ihead)
{
	while ( head!=NULL )
	{
		listtag *next=head->next;
		delete head;
		head=next;
	};

	setfillstyle(SOLID_FILL,color);
	bar(x,y,x+width,y+height);

	listtag *prev=NULL;
	while ( ihead!=NULL )
	{
		head=new listtag;
		head->prev=prev;
		head->id=ihead->id;
		strcpy(head->str,ihead->szov);
		if ( prev!=NULL ) prev->next=head;
		prev=head;
		ihead=ihead->next;
	};
	if (head!=NULL)
	{
		head->next=NULL;
		while( head->prev ) head=head->prev;
	};
	listtag *one=head;

	setcolor(tcolor);
	for ( int rows=0; (one!=NULL) && (rows<(height/fonttop)) ; rows++ )
	{
		puttext(rows,one->str);
		one=one->next;
	};
	now=head;
	row=0;
	activeline();
};
void list::inactiveline()
{
	setfillstyle(SOLID_FILL,color);
	bar(x,y+row*fonttop,x+width,y+(row+1)*fonttop);
	setcolor(tcolor);
	puttext(row,now->str);
};
void list::activeline()
{
	setfillstyle(SOLID_FILL,tcolor);
	bar(x,y+row*fonttop,x+width,y+(row+1)*fonttop);
	setcolor(color);
	puttext(row,now->str);
	setcolor(tcolor);
};
void list::down()
{
	if ( now->next!=NULL )
	{
		if ( ((row+2)*fonttop)<height )
		{
			inactiveline();
			row++;
			now=now->next;
			activeline();
		}	else
			{
				listtag *nowpuff=now->next;
				int rowpuff=row;
				while( row-- )
				{
					inactiveline();
					now=now->prev;
				};
				now=nowpuff;
				row=rowpuff;
				activeline();
			};
	};
};
void list::up()
{
	if ( now->prev!=NULL )
	{
		if ( row>0 )
		{
			inactiveline();
			row--;
			now=now->prev;
			activeline();
		}	else
			{
				listtag *nowpuff=now->prev;
				int rowpuff=row;
				while( (((row++)+2)*fonttop)<height )
				{
					inactiveline();
					now=now->next;
				};
				now=nowpuff;
				row=rowpuff;
				activeline();
			};
	};
};
