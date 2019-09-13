#define NAMELEN 20
struct SymbolTable
{
	char name[NAMELEN];
	int address;
	int size;
	struct SymbolTable *next;
};
struct LabelTable
{
	char blockname[NAMELEN];
	int address;
	struct LabelTable *next;
};
struct Stack
{
	int instruction_num;
	struct Stack *next;
};
struct ConstValues
{
	int address;
	int value;
	struct ConstValues *next;
};
struct Collection
{
	struct SymbolTable *symboltable;
	struct ConstValues *const_values;
	int noofconstantvalues;
	int noofinstructions;
	int **instrtab;
	int current_memory_address;
	struct LabelTable *labeltable;
	struct Stack *stack;
};
struct PreserveOnFile
{
	int noof_instructions;
	int noof_constant_values;
	int current_memory_address;
};
struct ExecCollection
{
	int **instrtab;
	struct ConstValues *const_values;
	struct PreserveOnFile *pof;
	int registers[8];
	int *memory;
};