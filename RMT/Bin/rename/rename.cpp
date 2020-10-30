#include <dos.h>
#include <stdio.h>
#include <dir.h>
#include <string.h>
void main ()	{
	printf("   *** RENAME BMP to BIN ***\n path: ");
	char path[80];
	scanf("%s",path);
	chdir(path);

	struct ffblk ffblk;
	int done;
	printf("Directory listing of *.bmp\n");
	done = findfirst("*.bmp",&ffblk,0);
	while (!done)
	{
		char nname[80];
		strcpy( nname , ffblk.ff_name );
		int len=strlen( nname );
		nname[len-3]='b';
		nname[len-2]='i';
		nname[len-1]='n';
		printf("  %s -> %s\n", ffblk.ff_name,nname);
		rename( ffblk.ff_name , nname );
		done = findnext(&ffblk);
	}
	getchar();

}