#include "includeheaders.h"
#include "structures.h"
#include "strfuns.h"
static void error(char *msg)
{
	printf("ERROR: %s\n", msg);
	exit(1);
}

short int getRegCode(char *reg)
{
	return reg[0] - 'A';
}
char isReg(char *str)
{
	if (str[0] >= 'A'&&str[0] <= 'H'&&str[1] == 'X' && str[2] == '\0')
		return 1;
	return 0;
}
short int getOpcode(char *str,char *param)
{
	if (check("MOV", str))
		if (isReg(param))
			return 2;//memory to register MOV AX,A
		else
			return 1;//register to memory MOV A,AX
	if (check("ADD", str))
		return 3;
	if (check("SUB", str))
		return 4;
	if (check("MUL", str))
		return 5;
	if (check("JMP", str))
		return 6;
	if (check("IF", str))
		return 7;
	if (check("EQ", str))
		return 8;
	if (check("LT", str))
		return 9;
	if (check("GT", str))
		return 10;
	if (check("LTEQ", str))
		return 11;
	if (check("GTEQ", str))
		return 12;
	if (check("PRINT", str))
		return 13;
	if (check("READ", str))
		return 14;
}
int getMemAddress(char *str,int index, struct Collection *collection)
{
	struct SymbolTable *symbtab = collection->symboltable;
	while (symbtab != NULL)
	{
		if (check(symbtab->name, str))
		{
			if (index<symbtab->size || symbtab->size == 0)
				return symbtab->address+index;
			return -1;
		}
		symbtab = symbtab->next;
	}
	return -1;
}
int getIndexName(char *str)
{
	int index = 0, size = 0;
	while (str[index++] != '[');

	str[index++] = '\0';
	while (str[index] != ']')
	{
		size = size * 10 + str[index++] - '0';
	}
	return size;
}
void addSymbToSymbTab(char *str, int size, struct Collection *collection)
{
	struct SymbolTable *symbtab = (struct SymbolTable*)malloc(sizeof(struct SymbolTable));
	if (symbtab == NULL)
		error("Unable to allocate memory at addsymbtosymbtab()");
	symbtab->address = collection->current_memory_address;
	symbtab->size = size;
	sprintf(symbtab->name, "%s", str);
	symbtab->next = NULL;
	collection->current_memory_address += size;
	if (collection->symboltable != NULL)
		symbtab->next = collection->symboltable;
	collection->symboltable = symbtab;
}
void processDATA(char *str, struct Collection *collection)
{
	if (!checkSymbolInStr(str, '['))
	{
		addSymbToSymbTab(str,1,collection);
		return;
	}
	int size = getIndexName(str);
	addSymbToSymbTab(str, size, collection);
}
static int getNoofLocationsUsingOpcode(int opcode)
{
	if (opcode == -1)
		return 2;
	if (opcode == 1 || opcode == 2)
		return 4;
	if (opcode >= 3 && opcode <= 5)
		return 5;
	if (opcode == 6 || opcode == 13 || opcode == 14)
		return 3;
	if (opcode == 7)
		return 6;
}
void addAddressValueToConstStruct(struct Collection *collection, int value)
{
	struct ConstValues *constvalue = (struct ConstValues*)malloc(sizeof(struct ConstValues));
	constvalue->address = collection->current_memory_address;
	constvalue->value = value;
	constvalue->next = NULL;
	if (collection->const_values != NULL)
		constvalue->next = collection->const_values;
	collection->const_values = constvalue;
}
void processCONST(char *str, struct Collection *collection)
{
	char *str1, *str2;
	int value = 0;
	str1 = (char*)malloc(100);
	str2 = (char*)malloc(100);
	if (!str1 || !str2)
		error("Unable to allocate memory at processConst()");
	splitString(str, str1, str2, '='); 
	addSymbToSymbTab(str1, 0, collection);
	sscanf(str2, "%d", &value);
	addAddressValueToConstStruct(collection, value);
	collection->current_memory_address++;
	collection->noofconstantvalues++;
	free(str1);
	free(str2);
}
void processREAD(char *str, struct Collection *collection)
{
	collection->noofinstructions++;
	int noofinstr = collection->noofinstructions;
	collection->instrtab = (int**)realloc(collection->instrtab, sizeof(int*)*noofinstr);
	collection->instrtab[noofinstr - 1] = (int*)malloc(3 * sizeof(int));
	collection->instrtab[noofinstr - 1][0] = noofinstr;
	collection->instrtab[noofinstr - 1][1] = getOpcode("READ",'\0');
	collection->instrtab[noofinstr - 1][2] = getRegCode(str);
}
void processMOV(char *str, struct Collection *collection)
{
	char *str1 = (char*)malloc(100);
	char *str2 = (char*)malloc(100);
	if (!str1 || !str2)
		error("Unable to allocate memory at processMov()");
	splitString(str, str1, str2, ',');
	collection->noofinstructions++;
	int noofinstr = collection->noofinstructions;
	collection->instrtab = (int**)realloc(collection->instrtab, noofinstr * sizeof(int*));
	collection->instrtab[noofinstr - 1] = (int*)malloc(4 * sizeof(int));
	collection->instrtab[noofinstr - 1][0] = noofinstr;
	collection->instrtab[noofinstr - 1][1] = getOpcode("MOV",str1);
	if (isReg(str1))
		collection->instrtab[noofinstr - 1][2] = getRegCode(str1);
	else if (!checkSymbolInStr(str1, '['))
	{
		collection->instrtab[noofinstr - 1][2] = getMemAddress(str1, 0, collection);
	}
	else
	{
		int index = getIndexName(str1);
		collection->instrtab[noofinstr - 1][2] = getMemAddress(str1, index, collection);
	}
	if (isReg(str2))
		collection->instrtab[noofinstr - 1][3] = getRegCode(str2);
	else if (!checkSymbolInStr(str2, '['))
	{
		collection->instrtab[noofinstr - 1][3] = getMemAddress(str2, 0, collection);
	}
	else
	{
		int index = getIndexName(str2);
		collection->instrtab[noofinstr - 1][3] = getMemAddress(str2, index, collection);
	}
	free(str1);
	free(str2);
}
void processADD(char *str, struct Collection *collection)
{
	collection->noofinstructions++; 
	int noofinstr = collection->noofinstructions;
	collection->instrtab = (int**)realloc(collection->instrtab,sizeof(int*)*noofinstr);
	collection->instrtab[noofinstr - 1] = (int*)malloc(sizeof(int) * 5);
	collection->instrtab[noofinstr - 1][0] = noofinstr;
	collection->instrtab[noofinstr - 1][1] = getOpcode("ADD", '\0');
	char *str1, *str2;
	str1 = (char*)malloc(100);
	str2 = (char*)malloc(100);
	if (!str1 || !str2)
		error("Unable to allocate memory at processADD()");
	splitString(str, str1, str2, ',');
	collection->instrtab[noofinstr - 1][2] = getRegCode(str1);
	if (checkSymbolInStr(str2, ','))
	{
		splitString(str2, str, str1, ',');
		collection->instrtab[noofinstr - 1][3] = getRegCode(str);
		collection->instrtab[noofinstr - 1][4] = getRegCode(str1);
	}
	else
	{
		collection->instrtab[noofinstr - 1][3] = getRegCode(str2);
		collection->instrtab[noofinstr - 1][4] = -1;
	}

	free(str1);
	free(str2);
}
void addBlockToLabelTab(char *str, struct Collection *collection)
{
	struct LabelTable *labeltable = (struct LabelTable*)malloc(sizeof(struct LabelTable));
	if (!labeltable)
		error("Unable to allocate memory at addBlockToLabelTab()");
	sprintf(labeltable->blockname, "%s", str);
	labeltable->address = collection->noofinstructions;
	labeltable->next = NULL;
	if (collection->labeltable)
		labeltable->next = collection->labeltable;
	collection->labeltable = labeltable;
}
void processBlock(char *str, struct Collection *collection)
{
	char *str1 = (char*)malloc(100);
	if (str1 == NULL)
		error("Unable to allocate Memory at processBlock()");
	splitString(str, str1, "\0", ':');
	if (check(str1, "START"))
	{
		//printf("Program starts:\n");
		return;
	}
	addBlockToLabelTab(str1, collection);
	free(str1);
}
void addInstrToStack(struct Collection *collection)
{
	struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
	stack->instruction_num = collection->noofinstructions;
	stack->next = NULL;
	if (collection->stack)
		stack->next = collection->stack;
	collection->stack = stack;
}
void processIF(char *str, struct Collection *collection)
{
	collection->noofinstructions++;
	int noofinstr = collection->noofinstructions;
	collection->instrtab = (int**)realloc(collection->instrtab, noofinstr * sizeof(int*));
	collection->instrtab[noofinstr - 1] = (int*)malloc(6 * sizeof(int));
	collection->instrtab[noofinstr - 1][0] = collection->noofinstructions;
	collection->instrtab[noofinstr - 1][1] = getOpcode("IF", "\0");
	char *str1, *str2;
	str1 = (char*)malloc(100);
	str2 = (char*)malloc(100);
	if (!str1 || !str2)
		error("Unable to allocate memory at processIF()");
	splitString(str, str1, str2, ' ');
	collection->instrtab[noofinstr - 1][2] = getRegCode(str1);
	splitString(str2, str, str1, ' ');
	collection->instrtab[noofinstr - 1][4] = getOpcode(str, "\0");
	splitString(str1, str, str2, ' ');
	collection->instrtab[noofinstr - 1][3] = getRegCode(str);
	collection->instrtab[noofinstr - 1][5] = -1;
	addInstrToStack(collection);
	free(str1);
	free(str2);
}
int getInstrFromStack(struct Collection *collection)
{
	int instr = collection->stack->instruction_num;
	collection->stack = collection->stack->next;
	return instr;
}
void processELSE(char *str, struct Collection *collection)
{
	collection->noofinstructions++;
	int noofinstr = collection->noofinstructions;
	collection->instrtab = (int**)realloc(collection->instrtab, noofinstr * sizeof(int*));
	collection->instrtab[noofinstr - 1] = (int*)malloc(3 * sizeof(int));
	collection->instrtab[noofinstr - 1][0] = collection->noofinstructions;
	collection->instrtab[noofinstr - 1][1] = getOpcode("JMP","\0");
	collection->instrtab[noofinstr - 1][2] = -1;
	collection->instrtab[getInstrFromStack(collection) - 1][5] = noofinstr;
	addBlockToLabelTab("ELSE",collection);

}
int getAddressFromLabelTab(struct Collection *collection, char *str)
{
	int instr = -1;
	struct LabelTable *labeltable, *prev = NULL;
	labeltable = collection->labeltable;
	while (labeltable && !check(labeltable->blockname,str))
	{
		prev = labeltable;
		labeltable = labeltable->next;
	}
	if (labeltable)
	{
		if (!prev)
		{
			instr = collection->labeltable->address;
			collection->labeltable = collection->labeltable->next;
			return instr;
		}
		instr = labeltable->address;
		prev->next = labeltable->next;
	}
	return instr;
}
void processENDIF(char *str, struct Collection *collection)
{
	int instr = getAddressFromLabelTab(collection,"ELSE");
	if (instr == -1)
	{
		instr = getInstrFromStack(collection);
		collection->instrtab[instr - 1][5] = collection->noofinstructions + 1;
	}
	else
		collection->instrtab[instr - 1][2] = collection->noofinstructions + 1;
}
void processJMP(char *str, struct Collection *collection)
{
	collection->noofinstructions++;
	int noofinstr = collection->noofinstructions;
	collection->instrtab = (int**)realloc(collection->instrtab, noofinstr*sizeof(int*));
	collection->instrtab[noofinstr - 1] = (int*)malloc(3 * sizeof(int));
	collection->instrtab[noofinstr - 1][0] = noofinstr;
	collection->instrtab[noofinstr - 1][1] = getOpcode("JMP", "\0");
	collection->instrtab[noofinstr - 1][2] = getAddressFromLabelTab(collection, str);

}
void processPRINT(char *str, struct Collection *collection)
{
	collection->noofinstructions++;
	int noofinstr = collection->noofinstructions;
	collection->instrtab = (int**)realloc(collection->instrtab, sizeof(int*) * noofinstr);
	collection->instrtab[noofinstr - 1] = (int*)malloc(3 * sizeof(int));
	collection->instrtab[noofinstr - 1][0] = noofinstr;
	collection->instrtab[noofinstr - 1][1] = getOpcode("PRINT", "\0");
	if (isReg(str))
		collection->instrtab[noofinstr - 1][2] = getRegCode(str);
	else
		collection->instrtab[noofinstr - 1][2] = getMemAddress(str,0,collection);
}
void processEND(struct Collection *collection)
{
	collection->noofinstructions++;
	collection->instrtab = (int**)realloc(collection->instrtab, sizeof(int*)*collection->noofinstructions);
	collection->instrtab[collection->noofinstructions - 1] = (int*)malloc(2 * sizeof(int));
	collection->instrtab[collection->noofinstructions - 1][0] = collection->noofinstructions;
	collection->instrtab[collection->noofinstructions - 1][1] = -1;
}

void callFun(char *str1, char *str2, struct Collection *collection)
{

	if (check(str1, "DATA"))
	{
		processDATA(str2,collection);
		return;
	}
	if (check(str1, "CONST"))
	{
		processCONST(str2,collection);
		return;
	}
	if (check(str1, "READ"))
	{
		processREAD(str2, collection);
		return;
	}
	if (check(str1, "MOV"))
	{
		processMOV(str2, collection);
		return;
	}
	if (check(str1, "ADD"))
	{
		processADD(str2, collection);
		return;
	}
	if (check(str1, "IF"))
	{
		processIF(str2, collection);
		return;
	}
	if (check(str1, "ELSE"))
	{
		processELSE(str2, collection);
		return;
	}
	if (check(str1, "ENDIF"))
	{
		processENDIF(str2, collection);
		return;
	}
	if (check(str1, "JMP")||check(str1,"JUMP"))
	{
		processJMP(str2, collection);
		return;
	}
	if (check(str1, "PRINT"))
	{
		processPRINT(str2, collection);
		return;
	}
	if (checkSymbolInStr(str1, ':'))
	{
		processBlock(str1, collection);
		return;
	}
	if (check(str1, "END"))
	{
		processEND(collection);
		return;
	}

}
void processLine(char *line, struct Collection *collection)
{
	char *str1,*str2;
	str1 = (char*)malloc(100);
	str2 = (char*)malloc(100);
	if (str1 == NULL || str2 == NULL)
		error("Unable to allocate memory at processLine()");
	splitString(line, str1, str2, ' ');
	callFun(str1, str2,collection);
	free(str1);
	free(str2);
}
void readInpFile(FILE *inpfile, struct Collection *collection)
{
	char *line = (char*)malloc(100);
	if (line == NULL)
		error("Unable to allocate Memory at readInpFile()");
	while (!feof(inpfile))
	{
		fgets(line, 100, inpfile);
		if (line[0] != '\n')
			processLine(line,collection);
	}
	free(line);
}

void initCollection(struct Collection *collection)
{
	collection->symboltable = NULL;
	collection->const_values = NULL;
	collection->noofconstantvalues = 0;
	collection->noofinstructions = 0;
	collection->instrtab = (int**)malloc(0);
	collection->current_memory_address = 0;
	collection->labeltable = NULL;
	collection->stack = NULL;
}

void printInstrTab(int **instrtab, int noofinstr)
{
	for (int i = 0; i < noofinstr; i++)
	{
		for (int j = 0; j < getNoofLocationsUsingOpcode(instrtab[i][1]); j++)
		{
			printf("%d ", instrtab[i][j]);
		}
		printf("\n");
	}
}
void writeInstructionsToFile(FILE *file, int **instrtab, int noofinstructions)
{
	int *line = (int*)malloc(sizeof(int) * 6);
	if (line == NULL)
		error("Unable To Allocate Memory in writeInstructionsTOoFile()");
	for (int i = 0; i < noofinstructions; i++)
	{
		int noofparam = getNoofLocationsUsingOpcode(instrtab[i][1]);
		for (int j = 0; j < 6; j++)
		{
			if (j < noofparam)
				line[j] = instrtab[i][j];
			else
				line[j] = -1;
		}
		fwrite(line, sizeof(int), 6, file);
	}
	free(line);
}
void writeConstantValuesToFile(FILE *file, struct ConstValues *constvalues)
{
	int *values = (int*)malloc(sizeof(int)*2);
	if (values == NULL)
		error("Unable to allocate memory at writeConstantValuesToFile()");
	while (constvalues != NULL)
	{
		values[0] = constvalues->address;
		values[1] = constvalues->value;
		fwrite(values, sizeof(int), 2, file);
		constvalues = constvalues->next;
	}
	free(values);
}
void writeICToFile(FILE *file, struct Collection *collection)
{
	struct PreserveOnFile *preservestruct = (struct PreserveOnFile*)malloc(sizeof(struct PreserveOnFile));
	if (preservestruct == NULL)
		error("Unable to allocate memory for struct in writeICToFile()");
	preservestruct->noof_instructions = collection->noofinstructions;
	preservestruct->noof_constant_values = collection->noofconstantvalues;
	preservestruct->current_memory_address = collection->current_memory_address;
	fwrite(preservestruct, sizeof(struct PreserveOnFile), 1, file);
	writeInstructionsToFile(file, collection->instrtab, collection->noofinstructions);
	writeConstantValuesToFile(file, collection->const_values);
	free(preservestruct);
}
void freeInstrTab(int **instrtab,int noofinstrs)
{
	while (noofinstrs--)
	{
		free(instrtab[noofinstrs]);
	}
	free(instrtab);
}
void freeConstValues(struct ConstValues *constvalue){
	if (constvalue == NULL)
		return;
	freeConstValues(constvalue->next);
	free(constvalue);
}
void freeLabelTab(struct LabelTable *labtab)
{
	if (labtab == NULL)
		return;
	freeLabelTab(labtab->next);
	free(labtab);
}
void freeStack(struct Stack *stack)
{
	if (stack == NULL)
		return;
	freeStack(stack->next);
	free(stack);
}
void freeSymbTab(struct SymbolTable *symb)
{
	if (symb == NULL)
		return;
	freeSymbTab(symb->next);
	free(symb);
}
void freeCollection(struct Collection *collection)
{
	freeInstrTab(collection->instrtab,collection->noofinstructions);
	freeConstValues(collection->const_values);
	freeLabelTab(collection->labeltable);
	freeStack(collection->stack);
	freeSymbTab(collection->symboltable);
}
char* setOutputFileName(char *str,int n)
{
	char *res;
	if (str[n] == '.')
	{
		res = (char*)malloc(n + 5);
		res[n] = '.';
		res[n + 1] = 'n';
		res[n + 2] = 'a';
		res[n + 3] = 'g';
		res[n + 4] = '\0';
		return res;
	}
	res = setOutputFileName(str, n + 1);
	res[n] = str[n];
	return res;
}
int compile(char *filename)
{
	FILE *inpfile = fopen(filename, "r");
	if (inpfile == NULL)
		error("Unable to open Input File");
	struct Collection *collection = (struct Collection*)malloc(sizeof(struct Collection));
	if (collection == NULL)
		error("Unable to allocate memory for Collection at main()");
	initCollection(collection);
	readInpFile(inpfile,collection);
	fclose(inpfile);
	//printInstrTab(collection->instrtab, collection->noofinstructions);
	char *opname = setOutputFileName(filename,0);
	FILE *outfile = fopen(opname, "wb");
	if (outfile == NULL)
		error("Unable to open Output File");
	writeICToFile(outfile, collection);
	printf("Compiled Successful!!!\n");
	free(opname);
	fclose(outfile);
	freeCollection(collection);
	free(collection);
	return 0;
}