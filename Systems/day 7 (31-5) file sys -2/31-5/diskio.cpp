#include<stdio.h>
#include<stdlib.h>
#define FILENAMELEN 20
char diskfilename[FILENAMELEN];
static unsigned int block_size,noofblocks,filesize;
static FILE *fp;
int getNoofBlocks(FILE *fp,int block_size)
{
	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	noofblocks = filesize / block_size;
	if (!(filesize % block_size))
		noofblocks++;
	return noofblocks;
}
unsigned int init(char *filename, unsigned int block_size)
{
	fp = fopen(filename, "r");
	if (!fp)
	{
		printf("File Cant be open\n");
		exit(0);
	}
	sprintf(diskfilename, "%s", filename);
	int noofblocks = getNoofBlocks(fp, block_size);

	fclose(fp);
	return noofblocks;
}
void readBlock(void *buffer, unsigned int block_id)
{
	fseek(fp, block_id*block_size, SEEK_SET);
	if (!fread(buffer, block_size, 1, fp))
	{
		printf("Error while reading block from disk\n");
		exit(0);
	}
}
void writeBlock(void *buffer, unsigned int block_id)
{
	fseek(fp, block_id*block_size, SEEK_SET);
	if (!fwrite(buffer, block_size, 1, fp))
	{
		printf("Error while Writing block to disk\n");
		exit(0);
	}
}