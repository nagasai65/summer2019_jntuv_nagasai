#define NAMELEN 32
struct SymTabStruct
{
	char name[NAMELEN];
	unsigned int address;
	unsigned int size;
};
struct BlockAddresses
{
	char blockname;
	unsigned int address;
};
struct headerStruct
{
	unsigned int current_memory_address;
	unsigned int noof_symboltable_entries;
	unsigned int noof_instructions;
	unsigned int noof_blocks;
	int *memory;
};
struct instrTabStruct
{
	unsigned int InNo;
	int Opcode;
	int parameters[6];
};
struct stack
{

};