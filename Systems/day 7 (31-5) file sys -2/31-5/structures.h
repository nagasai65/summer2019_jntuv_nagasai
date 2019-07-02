struct metadata
{
	unsigned int magicnum;
	unsigned int blocksize;
	unsigned int noofblocks;
	unsigned int noofemptyblocks;
	char bytevector[0];
};
struct fileRecord
{
	char name[FILENAMELEN];
	unsigned int filesize;
	unsigned int noofblocks;
	unsigned int starting_block;
};