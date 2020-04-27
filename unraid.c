#include "raidhelper.c"
/*  The purpose of this program is to do a RAID 5 implementation for a personal project.  Given the input arguments, it will output the necessary backup files.  This program needs a specific input, as follows.  

./a.out numberofbackupfiles

where numberofbackupfiles is the number of backupfiles that are about to be unRAIDed.  
This program is made to be run as a one-click program to unRAID any files that have been raided by raid.c
This also only works if info.txt and backupX.txt are in the same folder as this, so make sure that is true.  j
info.txt is a helper file that transfers information between the two programs to make sure they run seamlessly.  It can be deleted after the files have been unRAIDed, i.e. restored to their original value, but not before.  
Ideally, this will be fixed in the future to where info.txt isn't needed.  */
void main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("the program requires two arguments\n");
		printf("./a.out numberofbackupfiles\n");
		exit(0);
	}
	checkfiles();
	int textcount=0;
	char string[100];
	FILE *infop;
	infop=fopen("info.txt", "r");
	while(fgets(string, 100, infop))
	{
		textcount++;
	}

	fclose(infop);
	printf("%i files\n", textcount);
	FILE *op;
	FILE *inputs[atoi(argv[1])];
	int checkcount=0;
	int checker[atoi(argv[1])];
	for(int i=0; i<atoi(argv[1]); i++)
	{
		checker[i]=0;
		sprintf(string, "backup%i.txt", i);
		inputs[i]=fopen(string, "r");
		if(inputs[i]==0)
		{
			checkcount++;
			checker[i]=1;
			printf("backup%i.txt is missing\n", i);
		}
		
	}
	infop=fopen("info.txt", "r");
	int parityrover;
	int rover=0;
	int blank;
	int filecount=0;
	int bytecount;
	char filename[40];
	struct buffer answer;
	while(filecount<textcount)
	{
		fscanf(infop, "%s %i %i %i\n", filename, &bytecount, &parityrover, &blank);
		op=fopen(filename, "w");
		printf("%s\n", filename);
		while(bytecount>0 && answer.check!=-1)
		{

			if(rover>(atoi(argv[1])-1))
			{
				rover=0;
			}
			if(rover!=parityrover && checkcount==0)
			{
				answer=readin(inputs[rover], bytecount);
				answer=readin(inputs[parityrover], bytecount);
				fprintf(op, "%s", answer.string);
				bytecount-=answer.count;
				//printf("one %i\n", rover);
			}
			else if(rover!=parityrover)
			{
				if(checker[rover]==0)
				answer=readin(inputs[rover], bytecount);
				if(checker[parityrover]==0)
				answer=readin(inputs[parityrover], bytecount);
				fprintf(op, "%s", answer.string);
				bytecount-=answer.count;
				//printf("three %i\n", rover);
			}
			rover++;
		}
		fclose(op);
		filecount++;
	}
	for(int i=0; i<atoi(argv[1]); i++)
	{
		if(checker[i]==0)
		fclose(inputs[i]);
	}
	fclose(infop);
}
