#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <unistd.h>

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
void checkfolders(int i)
{
	char filename[20];
	sprintf(filename, "backdir%i", i);
	DIR *dir=opendir(filename);
	if(dir)
	{
		closedir(dir);
	}
	else if(ENOENT == errno)
	{
		printf("folder %s doesn't exist\n", filename);
		exit(0);
	}
}
void checkfiles()
{
	char filename[20];
	sprintf(filename, "info.txt");
	if(access(filename, F_OK)==-1)
	{
		printf("file %s does not exist\n", filename);
		printf("data unrecoverable\n");
		exit(0);
	}
}
struct buffer readin(FILE *fp, int bytes)
{
	struct buffer answer;
	answer.check=0;
	int x;
	if(bytes>8)
	{
		x=8;
	}
	else
	{
		x=bytes;
	}
	int check=0;
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
