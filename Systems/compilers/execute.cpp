#include "includeheaders.h"
#include "structures.h"
void processLine(int*, struct ExecCollection*);
static void error(char *str)
{
	printf("Error: %s\n", str);
	exit(0);
}
void print(struct ExecCollection *collection)
{
	for (int i = 0; i < collection->pof->noof_instructions; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			printf("%d ", collection->instrtab[i][j]);
		}
		printf("\n");
	}
	struct ConstValues *cv = collection->const_values;
	while (cv)
	{
		printf("%d %d\n", cv->address, cv->value);
		cv = cv->next;
	}
}

void loadConstValues(FILE *inpfile, struct ExecCollection *collection)
{
	int noofvalues = collection->pof->noof_constant_values;
	collection->const_values = NULL;
	while (noofvalues--)
	{
		struct ConstValues *constvalues = (struct ConstValues*)malloc(sizeof(struct ConstValues));
		fread(constvalues, sizeof(struct ConstValues), 1, inpfile);
		constvalues->next = collection->const_values;
		collection->const_values = constvalues;
	}
}

void loadInstrtab(FILE *inpfile, struct ExecCollection *collection)
{
	int noof_instr = collection->pof->noof_instructions;
	collection->instrtab = (int**)malloc(sizeof(int*)*noof_instr); //need to be free
	if (collection->instrtab == NULL)
		error("Unable to allocate memory at loadInstrtab()");
	for (int i = 0; i < noof_instr; i++)
	{
		collection->instrtab[i] = (int*)malloc(sizeof(int) * 6); //need to be free
		fread(collection->instrtab[i], sizeof(int), 6, inpfile);
	}
}
void readICFromFile(FILE *inpfile,struct ExecCollection *collection)
{
	struct PreserveOnFile *pof = (struct PreserveOnFile*)malloc(sizeof(struct PreserveOnFile)); // need to be free
	fread(pof, sizeof(struct PreserveOnFile), 1, inpfile);
	collection->pof = pof;
	loadInstrtab(inpfile, collection);
	loadConstValues(inpfile, collection);
}

void processMOV(int *line, int type, struct ExecCollection *collection)
{
	switch (type){
	case 1:collection->memory[line[0]] = collection->registers[line[1]]; return;
	case 2:collection->registers[line[0]] = collection->memory[line[1]]; return;

	}
}

void processADD(int *line, struct ExecCollection *collection)
{
	if (line[2] == -1)
		collection->registers[line[0]] = collection->registers[line[0]] + collection->registers[line[1]];
	else
		collection->registers[line[0]] = collection->registers[line[1]] + collection->registers[line[2]];
}

void processSUB(int *line, struct ExecCollection *collection)
{
	if (line[2] == -1)
		collection->registers[line[0]] = collection->registers[line[0]] - collection->registers[line[1]];
	else
		collection->registers[line[0]] = collection->registers[line[1]] - collection->registers[line[2]];
}
void processMUL(int *line, struct ExecCollection *collection)
{
	if (line[1] == -1)
		collection->registers[0] = collection->registers[0] * collection->registers[line[0]];
	else if (line[2] == -1)
		collection->registers[line[0]] = collection->registers[line[0]] * collection->registers[line[1]];
}
void processREAD(int *line, struct ExecCollection *collection)
{
	int value;
	printf("Enter Value:");
	scanf("%d", &value);
	collection->registers[line[0]] = value;
}
void processPRINT(int *line, struct ExecCollection *collection)
{
	printf("Print value at address(%d):%d\n", line[0], collection->memory[line[0]]);
}
void processLine(int *line, struct ExecCollection *collection)
{
	switch (line[1]) 
	{
	case 1:processMOV(line + 2, 1,collection); return;
	case 2:processMOV(line + 2, 2,collection); return;
	case 3:processADD(line + 2,collection); return;
	case 4:processSUB(line + 2,collection); return;
	case 5:processMUL(line + 2,collection); return;
	case 13:processPRINT(line + 2,collection); return;
	case 14:processREAD(line + 2,collection); return;
	}
}
int processJMP(int *line, struct ExecCollection *collection)
{
	return line[2] - 1;
}
int processIF(int *line, struct ExecCollection *collection)
{
	switch (line[4])
	{
	case 8:
		if (collection->registers[line[2]] == collection->registers[line[3]])
			return 0;
		break;
	case 9:
		if (collection->registers[line[2]] < collection->registers[line[3]])
			return 0;
		break;
	case 10:
		if (collection->registers[line[2]] > collection->registers[line[3]])
			return 0;
		break;
	case 11:
		if (collection->registers[line[2]] <= collection->registers[line[3]])
			return 0;
		break;
	case 12:
		if (collection->registers[line[2]] >= collection->registers[line[3]])
			return 0;
		break;
	}
	return line[5] - 1;
}
int getNextInstruction(struct ExecCollection *collection, int IR)
{
	int opcode = collection->instrtab[IR][1];
	switch (opcode)
	{
	case -1:return -1;
	case 6:return processJMP(collection->instrtab[IR], collection);
	case 7:int instrno = processIF(collection->instrtab[IR], collection);
		if (instrno)
			return instrno;
	}
	return IR + 1;
}
void loadConstantvaluesToMemory(struct ExecCollection *collection)
{
	struct ConstValues *cv = collection->const_values;
	while (cv)
	{
		collection->memory[cv->address] = cv->value;
		cv = cv->next;
	}
}
void startProcess(struct ExecCollection *collection,int PC)//PC->program counter
{
	//need to be free
	collection->memory = (int*)malloc(sizeof(int)*collection->pof->current_memory_address);
	loadConstantvaluesToMemory(collection);
	for (int i = 0; i < 8; i++)
		collection->registers[i] = 0;
	int IR;
	while (PC != -1){
		IR = PC;
		processLine(collection->instrtab[IR-1], collection);
		PC = getNextInstruction(collection, IR);
	}
}

void freeConstantValues(struct ConstValues *cv)
{
	if (!cv)
		return;
	freeConstantValues(cv->next);
	free(cv);
}
void freeCollection(struct ExecCollection *collection)
{
	free(collection->memory);
	for (int i = 0; i < collection->pof->noof_instructions; i++)
	{
		free(collection->instrtab[i]);
	}
	free(collection->instrtab);
	freeConstantValues(collection->const_values);
	free(collection->pof);
}
int execute(char *filename)
{
	FILE *inpfile = fopen(filename, "rb");
	if (!inpfile)
		error("Cant open inpfile in execute()");
	struct ExecCollection *collection = (struct ExecCollection*)malloc(sizeof(struct ExecCollection));
	readICFromFile(inpfile,collection);
	//print(collection);
	//printf("-------------------\n");
	startProcess(collection,1);
	freeCollection(collection);
	free(collection);
	fclose(inpfile);
	return 0;
}