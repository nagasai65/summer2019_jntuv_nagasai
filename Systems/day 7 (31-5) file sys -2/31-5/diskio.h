unsigned int init(char *filename, unsigned int block_size);

void readBlock(void *buffer, unsigned int block_id);

void writeBlock(void *buffer, unsigned int block_id)
