#include"includeheaders.h"
struct fileStruct
{
	char filename[FILE_NAME_LENGTH];
	unsigned int starting_block;
	unsigned int noofblocks;
	unsigned int filesize;
};
struct metadata
{
	int magicnum;
	struct fileStruct files[MAXFILECOUNT];
	unsigned int nooffiles;
	unsigned int nooffreeblocks;
	unsigned char freeblockvector[NOOFBLOCKS];
};