/*******************************************************************************
				user.h
*******************************************************************************/
#ifndef _USR_H
	#define _USR_H
// a felhasználó adatai
#define USER_DAT "bin\\user.dat"
typedef struct TUserData	{
	int Level;
	long Time;
	char Name[30];
};
#endif  // _UST_H
