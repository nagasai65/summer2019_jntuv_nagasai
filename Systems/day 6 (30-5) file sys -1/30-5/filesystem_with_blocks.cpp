#include"includeheaders.h"
#include"structures.h"
void get_commandNparam(char *query, char* command, char *param)
{
	int index = 0;
	while (query[0] != ' '&&query[0] != '\0')
	{
		command[index++] = query[0];
		query++;
	}
	command[index] = '\0';
	index = 0;
	while (query[0] == ' ')
		query++;
	while (query[0] != '\0')
	{
		param[index++] = query[0];
		query++;
	}
	param[index] = '\0';
}
int check(char *str1, char *str2)
{
	while (str1[0] != '\0' && str2[0] != '\0')
	{
		if (str1[0] != str2[0])
			return 0;
		str1++;
		str2++;
	}
	if (str1[0] == '\0'&&str2[0] == '\0')
		return 1;
	return 0;
}


void readBlock(FILE *hdptr, void *block, int blocknum)
{
	fseek(hdptr,0, SEEK_SET);

	if (!fread(block, BLOCK_SIZE, 1, hdptr))
	{
		printf("Error Reading block\n");
		exit(0);
	}
}
void writeBlock(FILE *hdptr, void *block, int blocknum)
{

	fseek(hdptr,0, SEEK_SET);
	if (blocknum)
		fseek(hdptr,( BLOCK_SIZE * blocknum), SEEK_CUR);
	if (!fwrite(block, BLOCK_SIZE, 1, hdptr))
	{
		printf("Error Writing Block\n");
		exit(0);
	}
	//fflush(hdptr);
}
void writeMetaData(FILE *hdptr, struct metadata* met)
{
	void *block = malloc(BLOCK_SIZE);
	memcpy(block, met, sizeof(struct metadata));
	writeBlock(hdptr, block, 0);
	free(block);
}
struct metadata* readMetaData(FILE *hdptr)
{
	void *block = malloc(BLOCK_SIZE);
	readBlock(hdptr, block, 0);
	struct metadata *met = (struct metadata*)malloc(sizeof(struct metadata));
	memcpy(met, block, sizeof(struct metadata));
	free(block);
	return met;
}
void format(FILE *hdptr)
{
	struct metadata *met = (struct metadata*)malloc(sizeof(struct metadata));
	met->nooffiles = 0;
	met->magicnum = MAGICNUM;
	met->nooffreeblocks = NOOFBLOCKS-META_BLOCKS;
	for (int i = 0; i < META_BLOCKS; i++)
	{
		met->freeblockvector[i] = 0;
	}
	for (int i = META_BLOCKS; i < NOOFBLOCKS; i++)
	{
		met->freeblockvector[i] = 1;
	}
	writeMetaData(hdptr, met);
	free(met);
}
void check_magicNum(FILE *hdptr)
{
	void *block = malloc(BLOCK_SIZE);
	readBlock(hdptr, block, 0);
	struct metadata *met = (struct metadata*)malloc(sizeof(struct metadata));
	memcpy(met, block, sizeof(struct metadata));
	if (met->magicnum != MAGICNUM)
	{
		printf("do you want to format:y/n:");
		char choice;
		scanf("%c", &choice);
		if (choice == 'y')
		{
			format(hdptr);
			return;
		}
		exit(0);
	}
	free(block);
	free(met);
}
void debugCommand(FILE *hdptr)
{
	struct metadata *met = readMetaData(hdptr);
	printf("Total Files:%d\n", met->nooffiles);
	for (int i = 0; i < met->nooffiles; i++)
	{
		printf("%s\n", met->files[i].filename);
	}

}
int getHowManyBlocksRequired(int filesize)
{
	int blocks = filesize / BLOCK_SIZE;
	if (filesize%BLOCK_SIZE!=0)
		return blocks + 1;
	return blocks;
}
int getStartingFreeBlock(int noofblocksreq,FILE *hdptr)
{
	struct metadata *met = readMetaData(hdptr);
	if (met->nooffreeblocks < noofblocksreq)
		return -1;
	for (int i = META_BLOCKS; i < NOOFBLOCKS; i++)
	{
		if (met->freeblockvector[i] == 1)
		{
			int j;
			for (j = i + noofblocksreq - 1; j > i; j--)
				if (met->freeblockvector[j] != 1)
					break;
			return i;
		}
	}
	free(met);
}
void updateMetadata(FILE *hdptr, char *filename, int starting_block, int noofblocks, int filesize)
{
	struct metadata *met = readMetaData(hdptr);
	
	sprintf(met->files[met->nooffiles].filename, "%s", filename);
	met->files[met->nooffiles].filesize = filesize;
	met->files[met->nooffiles].noofblocks = noofblocks;
	met->files[met->nooffiles].starting_block = starting_block;
	met->nooffiles = met->nooffiles + 1;
	void *block = malloc(BLOCK_SIZE);
	if (!block)
	{
		printf("Cant allocate memory");
		exit(1);
	}
	fseek(hdptr, 0, SEEK_SET);
	memcpy(block, met, sizeof(struct metadata));
	writeBlock(hdptr, block, 0);
	free(block);
}
void copyFileToDiskByBlocks(FILE *hdptr, FILE *fileptr, int filesize, char *dest_filename)
{
	void *block = malloc(BLOCK_SIZE);
	if (!block)
	{
		printf("Cant Alllocate memory\n");
		exit(1);
	}
	unsigned int size,blockNum,noofblocks;
	noofblocks = getHowManyBlocksRequired(filesize);
	blockNum = getStartingFreeBlock(noofblocks,hdptr);
	if (blockNum == -1)
	{
		printf("Hardisk is FULL");
		exit(0);
	}
	fseek(fileptr, 0, SEEK_SET);
	while (filesize != 0)
	{
		size = BLOCK_SIZE;
		if (filesize < size)
			size = filesize;
		if (!fread(block,size, 1, fileptr))
		{
			printf("Error while reading Src File\n");
			exit(0);
		}
		filesize -= size;

		writeBlock(hdptr, block, blockNum);
	}
	fseek(fileptr, 0, SEEK_END);
	filesize = ftell(fileptr);
	updateMetadata(hdptr, dest_filename, blockNum, noofblocks, filesize);
	free(block);
}
void copyToDiskCommand(FILE *hdptr, char *src, char *dest)
{
	FILE *srcFilePtr = fopen(src, "rb");
	if (!srcFilePtr)
	{
		printf("unable to open file");
		exit(0);
	}
	int filesize = 0;
	fseek(srcFilePtr, 0, SEEK_END);
	filesize=ftell(srcFilePtr);
	copyFileToDiskByBlocks(hdptr, srcFilePtr, filesize,dest);
	fclose(srcFilePtr);
}
void copyDiskdataToBlocks(FILE *hdptr, int starting_block, int noofblocks, int filesize,char* dest)
{
	FILE *fptr = fopen(dest, "wb");
	void *block = malloc(BLOCK_SIZE);
	unsigned int size;
	while (filesize != 0)
	{
		size = BLOCK_SIZE;
		if (filesize < size)
			size = filesize;
		readBlock(hdptr, block, starting_block);
		if (!fwrite(block, size, 1, fptr))
		{
			printf("Error While writing blocks to file");
			exit(0);
		}
		filesize -= size;
	}
	fclose(fptr);
	free(block);
}
void copyFromDiskCommand(FILE *hdptr, char *src, char *dest){
	struct metadata *met = readMetaData(hdptr);
	unsigned int starting_block, noofblocks, filesize;
	for (int i = 0; i < met->nooffiles; i++)
	{
		if (check(met->files[i].filename, src))
		{
			starting_block = met->files[i].starting_block;
			noofblocks = met->files[i].noofblocks;
			filesize = met->files[i].filesize;
			copyDiskdataToBlocks(hdptr, starting_block, noofblocks, filesize,dest);
			break;
		}
	}
	free(met);
}
void deleteRecord(struct metadata *met, int kthrecord)
{
	met->files[kthrecord] = met->files[met->nooffiles - 1];
	met->nooffiles = met->nooffiles - 1;
}
void deleteCommand(FILE *hdptr, char *filename)
{
	
	struct metadata *met = readMetaData(hdptr);
	for (int i = 0; i < met->nooffiles; i++)
	{
		if (check(met->files[i].filename, filename))
		{
			deleteRecord(met, i);
			writeMetaData(hdptr, met);
			return;
		}
	}
	printf("There is no Such File\n");
}
int main()
{
	FILE *hdptr;
	hdptr = fopen("harddisk.hdd", "rb+");
	if (hdptr == NULL)
	{
		printf("Error opening File\n");
		return 0;
	}
	check_magicNum(hdptr);
	char *query = (char*)malloc(50);
	char *command = (char*)malloc(10);
	char *param = (char*)malloc(40);

	while (1)
	{
		printf(">");
		gets(query);
		get_commandNparam(query, command, param);
		if (check(command, "format"))
		{
			format(hdptr);
			continue;
		}
		
		if (check(command, "debug"))
		{
			debugCommand(hdptr);
			continue;
		}
		
		if (check(command, "copyToDisk"))
		{
			get_commandNparam(param, query, command);
			copyToDiskCommand(hdptr,query,command);
			printf("FILE Copied\n");
			continue;
		}
		
		if (check(command, "copyFromDisk"))
		{
			get_commandNparam(param, query, command);
			copyFromDiskCommand(hdptr, query,command);
			continue;
		}
		if (check(command, "delete"))
		{
			deleteCommand(hdptr, param);
		}
		if (check(command, "exit"))
			break;
	}
	
	fclose(hdptr);
	
}