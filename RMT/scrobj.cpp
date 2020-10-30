/******************************************************************************
			scrobj.cpp
******************************************************************************/
#ifndef _ScrObj_CPP
	#define _ScrObj_CPP
// Screen objektumok
#include "typedef.cpp"
#include "pic_serv.cpp"
class TScrObj	{
	BOOL Registered;                  // biztonsági regisztrálás jelzõ
	int MId;                          // kép azonosító
protected:
	void Register();
	void Delete();
public:
	int Num;                          // fedési sorrend jelzõje
	TScrObj * Next;                   // következõ elem
	union {                           // kép
		TPicture * Pic;
		TPicClass * PicClass;
	};
	POINT Poz;                        // pzició a képernyõn
	TScrObj(  int iNum , int Id );
	~TScrObj();
	void Hide()	{ if ( Registered )  Delete(); };
	void Show() { if ( !Registered ) Register(); };
} * ScrObjList=NULL;
//*****************************************************************************
TScrObj::TScrObj( int iNum , int Id )	{
	MId=Id;
	switch( PicServer::GetType( Id )	){
		case TPICTURE :{
			if ( (Pic=*((TPicture **)PicServer::GetPic(Id)))==NULL ) _Perror("sorry... ") ;
		}	break;
		case TPICCLASS :{
			if ( (PicClass=*((TPicClass **)PicServer::GetPic(Id)))==NULL ) _Perror("sorry... ");
		}	break;
		default:	{
			char ize[20];
			itoa( Id , ize , 10  );
			_Perror( "TScrObj: Not an allowed type", ize ,NULL );
		}
	};
	Num=iNum;
	Registered=FALSE;
	Next=NULL;
};
//******************************************************************************
TScrObj::~TScrObj()	{
	Hide();
	PicServer::Free( MId );
};
//*****************************************************************************
void TScrObj::Register()	{
	register TScrObj *Puff=ScrObjList;
	int N=0;
	if ( Puff )	{
		while ( Puff->Next && (N++ < Num) )
			Puff=Puff->Next;
		Next = Puff->Next;
		Puff->Next = this;
	}	else	{
			ScrObjList=this;
			Next=NULL;
		}
	Registered=TRUE;
};
//*****************************************************************************
void TScrObj::Delete()	{
	register TScrObj *Puff=ScrObjList;
	if ( Puff==this )	{
		ScrObjList = Next;
	}	else	{
			while	( Puff->Next!= this ) 	{
				if ( !Puff->Next ) {
					Registered=FALSE;
					return;
				}
				Puff=Puff->Next;
			};
			Puff->Next = Next;
		}
	Registered=FALSE;
};
//*****************************************************************************
#endif // _ScrObj_CPP
