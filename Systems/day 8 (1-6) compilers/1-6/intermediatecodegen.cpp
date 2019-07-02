#include"includeheaders.h"
#include"structures.h"
static struct SymTabStruct **symtab;
static struct headerStruct *header;
struct instrTabStruct **instrtab;
void ERROR(char *msg)
{
	printf("%s\n", msg);
	exit(0);
}

int check(char *str1, char *str2)
{
	while (str1[0] != '\0'&&str2[0] != '\0')
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
int getRegisterCode(char *nameofreg)
{
	if (check(nameofreg, "AX"))
		return 0;
	if (check(nameofreg, "BX"))
		return 1;
	if (check(nameofreg, "CX"))
		return 2;
	if (check(nameofreg, "DX"))
		return 3;
	if (check(nameofreg, "EX"))
		return 4;
	if (check(nameofreg, "FX"))
		return 5;
	if (check(nameofreg, "GX"))
		return 6;
	if (check(nameofreg, "HX"))
		return 7;
	return -1;
}
int getOpcode(char *instr)
{
	if (check(instr, "MOV1"))
		return 1;
	if (check(instr, "MOV"))
		return 2;
	if (check(instr, "ADD"))
		return 3;
	if (check(instr, "SUB"))
		return 4;
	if (check(instr, "MUL"))
		return 5;
	if (check(instr, "JMP"))
		return 6;
	if (check(instr, "IF"))
		return 7;
	if (check(instr, "EQ"))
		return 8;
	if (check(instr, "LT"))
		return 9;
	if (check(instr, "GT"))
		return 10;
	if (check(instr, "LTEQ"))
		return 11;
	if (check(instr, "GTEQ"))
		return 12;
	if (check(instr, "PRINT"))
		return 13;
	if (check(instr, "READ"))
		return 14;
	return -1;
}
void seperateStr(char *line, char *str1, char *str2,char sep)
{
	int index = 0;
	while (line[0] != sep&&line[0]!='\0'&&line[0]!='\n')
	{
		str1[index++] = line[0];
		line++;
	}
	str1[index] = '\0';
	index = 0;
	while (line[0] == ' ' || line[0]==sep)
		line++;
	while (line[0] != '\0'&&line[0]!='\n')
	{
		if (line[0] == ']'&&sep=='[')
			break;
		str2[index++] = line[0];
		line++;
	}
	str2[index] = '\0';
}
void addNameToSymTab(char *name, int size)
{
	header->noof_symboltable_entries += 1;
	int len = header->noof_symboltable_entries;
	symtab = (struct SymTabStruct**)realloc(symtab, sizeof(struct SymTabStruct*)*len);
	symtab[len - 1] = (struct SymTabStruct*)malloc(sizeof(struct SymTabStruct));
	symtab[len-1]->address = header->current_memory_address;
	symtab[len-1]->size = size;
	sscanf(name, "%s", symtab[len-1]->name);
	header->current_memory_address += size;
	header->memory = (int*)realloc(header->memory, sizeof(int)*header->current_memory_address);

}
void buildSymbolTable(char *str)
{
	char *str1, *str2;
	str1 = (char*)malloc(30);
	str2 = (char*)malloc(30);
	seperateStr(str, str1, str2, '[');
	int size = 1;
	if (str2[0] != '\0')
	{
		sscanf(str2, "%d", &size);
	}
	addNameToSymTab(str1, size);
	free(str1);
	free(str2);
}
void processConstant(char *str)
{
	char *str1, *str2;
	int value;
	str1 = (char*)malloc(30);
	str2 = (char*)malloc(30);
	seperateStr(str, str1, str2, '=');
	sscanf(str2, "%d", &value);
	addNameToSymTab(str1, 0);
	header->memory[header->current_memory_address - 1] = value;
}
int isRegister(char *reg)
{
	if (reg[0] >= 'A' && reg[0] <= 'H')
	{
		if (reg[1] == 'X'&&reg[2] == '\0')
			return 1;
	}
	return 0;
}
unsigned int getMemAddress(char *str, unsigned int symtablen)
{
	while (symtablen--)
	{
		if (check(symtab[symtablen]->name, str))
			return symtab[symtablen]->address;
	}
	return -1;
}
void processArthmetic(char *instr, char *param)
{
	header->noof_instructions++;
	unsigned int currentInstr = header->noof_instructions;
	instrtab = (struct instrTabStruct **)realloc(instrtab,sizeof(struct instrTabStruct*)*currentInstr);
	instrtab[currentInstr - 1] = (struct instrTabStruct *)malloc( sizeof(struct instrTabStruct));
	instrtab[currentInstr - 1]->InNo = currentInstr;
	char *str1 = (char*)malloc(50);
	char *str2 = (char*)malloc(50);
	unsigned int address;
	seperateStr(param, str1, str2,',');
	if (isRegister(str1))
		instrtab[currentInstr - 1]->parameters[0] = getRegisterCode(str1);
	else
	{
		address = getMemAddress(str1, header->noof_symboltable_entries);
		instrtab[currentInstr - 1]->parameters[0] = address;
	}
	seperateStr(str2, str1, param,',');
	if (str1[0] != '\0'){
		if (isRegister(str1))
			instrtab[currentInstr - 1]->parameters[1] = getRegisterCode(str1);
		else
		{
			address = getMemAddress(str1, header->noof_instructions);
			instrtab[currentInstr - 1]->parameters[1] = address;
		}
		if (param[0] != '\0')
		{
			if (isRegister(param))
				instrtab[currentInstr - 1]->parameters[2] = getRegisterCode(param);
			else{
				address = getMemAddress(param, header->noof_instructions);
				instrtab[currentInstr - 1]->parameters[2] = address;
			}
		}
	}
	if (check(instr, "MOV") && isRegister(str1))
		instr = "MOV1";
	instrtab[currentInstr - 1]->Opcode = getOpcode(instr);

}
void processIF(char *str)
{ 
	header->noof_instructions++;
	int curr_instr=header->noof_instructions;
	char *str1, *str2;
	str1 = (char*)malloc(30);
	str2 = (char*)malloc(30);
	instrtab = (struct instrTabStruct**)realloc(instrtab, sizeof(struct instrTabStruct*));
	instrtab[curr_instr-1] = (struct instrTabStruct*)malloc(sizeof(struct instrTabStruct));
	instrtab[curr_instr - 1]->InNo = curr_instr;
	instrtab[curr_instr - 1]->Opcode = getOpcode("IF");
	seperateStr(str, str1, str2,' ');
	if (isRegister(str1))
		instrtab[curr_instr - 1]->parameters[0] = getRegisterCode(str1);
	else
		instrtab[curr_instr - 1]->parameters[0] = getMemAddress(str1,header->noof_instructions);
	seperateStr(str2, str, str1, ' ');
	if (isRegister(str))
		instrtab[curr_instr - 1]->parameters[1] = getRegisterCode(str);
	else
		instrtab[curr_instr - 1]->parameters[1] = getMemAddress(str, header->noof_instructions);
	seperateStr(str1, str, str2, ' ');
	instrtab[curr_instr - 1]->parameters[2] = getOpcode(str);
	pushToStack(curr_instr);
}
void tokenize(char *line)
{
	char *str1, *str2;
	str1 = (char*)malloc(30);
	str2 = (char*)malloc(30);
	seperateStr(line, str1, str2,' ');
	if (check(str1, "DATA"))
	{
		buildSymbolTable(str2);

	}
	if (check(str1, "CONSTANT"))
	{
		processConstant(str2);
	}
	if (check(str1, "READ") || check(str1, "MOV") || check(str1, "ADD") || check(str1, "SUB") || check(str1, "PRINT"))
	{
		processArthmetic(str1,str2);
	}
	if (check(str1,"IF"))
	{
		processIF(str2);
	}
	free(str1);
	free(str2);
}
void readInputModule(FILE *fp)
{
	char *line = (char*)malloc(50);
	while (!feof(fp))
	{
		fgets(line, 50, fp);
		tokenize(line);
	}
	free(line);
}
void init()
{
	header->current_memory_address = 0;
	header->noof_blocks = 0;
	header->noof_instructions = 0;
	header->noof_symboltable_entries = 0;
	symtab = (struct SymTabStruct**)malloc(0);
	header->memory = (int*)malloc(0);
}
void print()
{
	printf("NoofSymTabEntries:%d\nNoofInstrTab Entries:%d\n", header->noof_symboltable_entries, header->noof_instructions);
	printf("System Table :\n");
	for (int i = 0; i < header->noof_symboltable_entries; i++)
	{
		printf("%s %d %d\n", symtab[i]->name, symtab[i]->address, symtab[i]->size);
	}
	printf("Instruction Table\n");
	for (int i = 0; i < header->noof_instructions; i++)
	{
		printf("%d %d %d %d %d\n", instrtab[i]->InNo, instrtab[i]->Opcode, instrtab[i]->parameters[0], instrtab[i]->parameters[1], instrtab[i]->parameters[2]);
	}
}
int main()
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp)
	{
		ERROR("ERROR OPENING FILE\n");
	}
	symtab = (struct SymTabStruct**)malloc(0);
	header = (struct headerStruct*)malloc(sizeof(struct headerStruct));
	instrtab = (struct instrTabStruct**)malloc(0);
	init();
	readInputModule(fp);
	print();
	return 0;
}