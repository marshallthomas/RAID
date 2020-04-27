/*  The purpose of this program is to do a RAID 5 implementation for a personal project.  Given the input arguments, it will output the necessary backup files.  This program needs a specific input, as follows.  
./a.out inputfile numberofoutputs parityoutput
where:
	inputfile: the file to be distributed across other files
	numberofoiutputs:  the amount of files this is being distributed across
	parityoutput:  which file is to have the parity information, i.e. the entire input file

	This program is designed to be run by a separate program, probably bash, that will call it several times in the command line to backup entire folders in the RAID format.  
	If starting with a fresh backup, remember to delete the previous backup files, labeled backup.txt, as this program appends to the end of the files.  Also, do not delete info.txt until after the files have been recovered, otherwise they will not be recoverable from the backup files.*/
#include "raidhelper.c"
void main(int argc, char *argv[])
{
	if(argc!=4)
	{
		printf("This program needs 4 arguments\n");
		printf("./a.out inputfile numberofoutputs parityoutput\n");
		exit(0);
	}
	if(atoi(argv[2])<2)
	{
		printf("Raid needs more than two outputs.  (One is the parity)\n");
		exit(0);
	}
	
	FILE *ip;
	struct buffer buf;
	ip=fopen(argv[1], "r");
	//read in 8 bytes;
	struct buffer outfiles[atoi(argv[2])];
	FILE *outp[atoi(argv[2])];
	FILE *infop;
	infop=fopen("info.txt", "a");
	if(!ip)
	{
		printf("input file %s did not open\n", argv[1]);
		printf("nothing to do\n");
		exit(0);
	}
	int rover=0;
	int parityrover=atoi(argv[3]);
	int bytecount=0;
	for(int i=0; i<(atoi(argv[2])); i++)
	{
		outfiles[i]=outputfiles(i);
		outp[i]=fopen(outfiles[i].string, "a");
	}
	while(buf.check!=-1)
	{
		if(rover>(atoi(argv[2])-1))
		{
			rover=0;
		}
		if(rover!=parityrover)
		{
			buf=readin(ip);
			fprintf(outp[rover], "%s", buf.string);	
			fprintf(outp[parityrover], "%s", buf.string);
			bytecount+=buf.count;
		}
		rover++;
	}
	fprintf(infop, "%s %i %i %i\n", argv[1], bytecount, parityrover, atoi(argv[2]));
}
