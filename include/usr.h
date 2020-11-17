/*******************************************************************************
				user.h
*******************************************************************************/
#ifndef _USR_H
	#define _USR_H

// a felhaszn�l� adatai
#define USER_DAT "var/user.dat"

struct TUserData	{
	int Level;
	long Time;
	char Name[30];
};

#endif  // _UST_H
