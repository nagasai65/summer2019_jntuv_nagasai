#include"headers.h"
#include"structures.h"
#include"diskio.h"
void readNFileStructures(int nooffiles,unsigned int blocksize,int block_id)
{
	void* block = malloc(blocksize);
	struct fileRecord **rec = (struct fileRecord**)malloc(sizeof(struct fileRecord)*nooffiles);
	readBlock(block, block_id);
	int size = sizeof(struct fileRecord);
	for (int i = 0; i < nooffiles; i++)
	{
		memcpy(rec[i], (char*)block + size*i, size);
	}

}
void format(unsigned int blocksize,char *filename)
{
	struct metadata *met = (struct metadata*)malloc(sizeof(struct metadata));
	met->blocksize = blocksize;
	met->magicnum = MAGICNUM;
	met->noofblocks = init(filename, blocksize);
	met->noofemptyblocks = met->noofblocks - 16;
	for (int i = 0; i < met->noofblocks; i++)
	{
		met->bytevector[i] = 1;
	}
	void *buffer = malloc(blocksize);
	if (sizeof(met)<)
	memcpy(buffer, met, sizeof(met));
	writeBlock(buffer, 0);

}
void mountCommand(char *str1, unsigned int blocksize)
{
	init(str1, blocksize);
	void *buffer = malloc(blocksize);
	readBlock(buffer, 0);
	char c;
	struct metadata *met = (struct metadata*)malloc(sizeof(struct metadata));
	if (blocksize >= sizeof(struct metadata))
	{
		memcpy(met, buffer, sizeof(struct metadata));
	}
	else
	{
		memcpy(met, buffer,blocksize );
		readBlock(buffer, 1);
		memcpy(met + blocksize, buffer, sizeof(struct metadata) - blocksize);

	}
	if (met->magicnum != MAGICNUM)
	{
		printf("Data Corrupted\nDo you want to format y/n:");
		c=getch();
		if (c == 'y')
			format(blocksize,str1);
		else
			exit(0);
	}
	if (met->blocksize != blocksize)
	{
		printf("Block Size is changed do you want to format y/n:");
		c = getch();
		if (c == 'y')
			format(blocksize,str1);
		else
			return;
	}
	int nooffiles;
	int remaining_buff =sizeof(met) - 2 * blocksize;
	if (remaining_buff&&remaining_buff>=4)
	{
		memcpy(&nooffiles,(char*)buffer+remaining_buff , 4);
	}
	readNFileStructures(nooffiles,blocksize,2);
}
