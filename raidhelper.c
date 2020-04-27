#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>


typedef struct buffer{
	char string[40];
	int check;
	int count;
}buffer;
struct buffer readin(FILE *);
struct buffer outfiles(int);
struct buffer outputfiles(int i)
{
	char string[20];
	sprintf(string, "backup%i.txt", i);
	struct buffer answer;
	strcpy(answer.string, string);
	return answer;
}

struct buffer readin(FILE *fp)
{
	struct buffer answer;
	int check;
	int i;
	for(i=0; i<1; i++)
	{
		check=fscanf(fp, "%c", &answer.string[i]);
		if(check==-1)
		break;
	}
	answer.check=check;
	answer.count=i;
	answer.string[i]='\0';
	return answer;
}
