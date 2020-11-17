#include "pic_serv.h"
#include "error.h"

void PicServer::FreeAll()	{
	int f=0;
	while ( Pic_Files[f].PType!=NOTHING )	{
		if ( Pic_Files[f].Bmp )	{
			while ( Free( Pic_Files[f].Id ));
		}
		f++;
	}
}
//***********************************************
void * PicServer::GetPic( int iId )	{
	int f=0;
	int cret=0;
	void *ret=NULL;
	while ( Pic_Files[f].PType!=NOTHING )	{
		if ( Pic_Files[f].Id==iId )	{
			if ( Pic_Files[f].Users )	{
				Pic_Files[f].Users++;
				return &(Pic_Files[f].Bmp);
			}	else	{
				switch ( Pic_Files[f].PType )	{
					case TBMP:	{
						if ( (Pic_Files[f].Bmp=new TBmp())!=NULL )	{
							cret=Pic_Files[f].Bmp->Load( Pic_Files[f].FName );
							if ( !cret ) ret= &(Pic_Files[f].Bmp);
						}
					}	break;
					case TPICTURE:	{
						if ( (Pic_Files[f].Picture=new TPicture())!=NULL )	{
							cret=Pic_Files[f].Picture->Load( Pic_Files[f].FName );
							if ( !cret ) ret= &(Pic_Files[f].Picture);
						}
					}	break;
					case TPICCLASS:	{
						if ( (Pic_Files[f].PicClass=new TPicClass())!=NULL )	{
							cret=Pic_Files[f].PicClass->Load( Pic_Files[f].FNameArray );
							if ( !cret ) ret= &(Pic_Files[f].PicClass);
						}
					}	break;
					default :
						_Perror( "hib�s t�pus azonos�t�" ,NULL);
				}
				Pic_Files[f].Users++;
				return ret;
			}
		}
		f++;
	}
	return ret;
};
//***********************************************
TMainPicType PicServer::GetType( int iId )	{
	int f=0;
	while ( Pic_Files[f].PType!=NOTHING )	{
		if ( Pic_Files[f].Id==iId ) return Pic_Files[f].PType;
		f++;
	}
	return NOTHING;
};
//***********************************************
int PicServer::Free( int iId )	{
	int f=0;
	while ( Pic_Files[f].PType!=NOTHING )	{
		if ( Pic_Files[f].Id==iId )	{
			if ( Pic_Files[f].Users<=1 )	{
				if (( Pic_Files[f].Bmp!=NULL ) || ( Pic_Files[f].Picture!=NULL ) ||
						( Pic_Files[f].PicClass!=NULL ))	{
					switch ( Pic_Files[f].PType )	{
						case TBMP:	{
							delete Pic_Files[f].Bmp;
							Pic_Files[f].Bmp=NULL;
						}	break;
						case TPICTURE:	{
							delete Pic_Files[f].Picture;
							Pic_Files[f].Picture=NULL;
						}	break;
						case TPICCLASS:	{
							delete Pic_Files[f].PicClass;
							Pic_Files[f].PicClass=NULL;
						}	break;
						default :
							_Perror( "hib�s t�pus azonos�t�" ,NULL);
					}
					Pic_Files[f].Users=0;
				}
			}	else Pic_Files[f].Users--;
			return Pic_Files[f].Users;
		}
		f++;
	}
	return 0;
};
//***********************************************
void PicServer::FreeDirect( int iId )	{
	int f=0;
	while ( Pic_Files[f].PType!=NOTHING )	{
		if ( Pic_Files[f].Id==iId )	{
			if (( Pic_Files[f].Bmp!=NULL ) || ( Pic_Files[f].Picture!=NULL ) ||
						( Pic_Files[f].PicClass!=NULL ))	{
				switch ( Pic_Files[f].PType )	{
					case TBMP:	{
						delete Pic_Files[f].Bmp;
						Pic_Files[f].Bmp=NULL;
					}	break;
					case TPICTURE:	{
						delete Pic_Files[f].Picture;
						Pic_Files[f].Picture=NULL;
					}	break;
					case TPICCLASS:	{
						delete Pic_Files[f].PicClass;
						Pic_Files[f].PicClass=NULL;
					}	break;
					default :
						_Perror( "hib�s t�pus azonos�t�" ,NULL);
				}
				return;
			}
		}
		f++;
	}
};
//***********************************************
void PicServer::LoadPicDirect( int iId )	{
	int f=0;
	while ( Pic_Files[f].PType!=NOTHING )	{
		if ( Pic_Files[f].Id==iId )	{
			switch ( Pic_Files[f].PType )	{
				case TBMP:	{
					if ( (Pic_Files[f].Bmp=new TBmp())!=NULL )	{
						Pic_Files[f].Bmp->Load( Pic_Files[f].FName );
					}
				}	break;
				case TPICTURE:	{
					if ( (Pic_Files[f].Picture=new TPicture())!=NULL )	{
						Pic_Files[f].Picture->Load( Pic_Files[f].FName );
					}
				}	break;
				case TPICCLASS:	{
					if ( (Pic_Files[f].PicClass=new TPicClass())!=NULL )	{
						Pic_Files[f].PicClass->Load( Pic_Files[f].FNameArray );
					}
				}	break;
				default :
					_Perror( "hib�s t�pus azonos�t�" ,NULL);
			}
			return;
		}
		f++;
	}
};
