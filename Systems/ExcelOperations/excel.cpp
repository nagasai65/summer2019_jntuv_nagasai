#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
void copy(char *src, char* dest)
{
	int i = 0;
	while (src[0] != '\0')
	{
		dest[i++] = src[0];
		src++;
	}
	dest[i] = '\0';
}
int check(char *cmd, char *str)
{
	while (cmd[0] == str[0] && cmd[0] != '\0'&& str[0] != '\0')
	{
		cmd++;
		str++;
	}
	if (cmd[0] == '\0'&&str[0] == '\0')
		return 1;
	return 0;
}
void seperate_cmd_param(char *cmd,char *cmd1, char *param)
{
	int i = 0,param_i=0;
	while (cmd[i] != ' ')
	{
		cmd1[i] = cmd[i];
		i++;
	}
	cmd1[i++] = '\0';
	while (cmd[i] != '\0')
	{
		param[param_i++] = cmd[i++];
	}
	param[param_i] = '\0';
}
int has_only_val(char *res)
{
	while (res[0] != '\0')
	{
		if (!(res[0] >= '0'&&res[0] <= '9'))
			return 0;
		res++;
	}
	return 1;
}
int has_operators(char *res)
{
	while (res[0] != '\0')
	{
		if (res[0] == '+' || res[0] == '-' || res[0] == '*' || res[0] == '/')
			return 1;
		res++;
	}
	return 0;
}
int is_operator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/')
		return 1;
	return 0;
}
void copyDatanOperators(char *str, char *operand1, char *operand2, char *oper)
{
	int o_i = 0;
	while (str[0] == ' ')
		str++;
	while (!is_operator(str[0])&&str[0]!='\0')
	{
		operand1[o_i++] = str[0];
		str++;
	}
	operand1[o_i] = '\0';
	while (str[0] == ' ')
		str++;

	*oper = str[0];
	o_i = 0;
	if (str[0] == '\0')
	{
		operand2[o_i] = '\0';
		return;
	}
	str++;
	while (str[0] != ' '&& str[0] != '\0')
	{
		operand2[o_i++] = str[0];
		str++;
	}
	operand2[o_i] = '\0';
}
void copyOperands(char *operand1,char* operand2,int *v1,int *v2)
{
	while (operand1[0] != '\0')
	{
		*v1 = *v1 * 10 + operand1[0] - '0';
		operand1++;
	}
	while (operand2[0] != '\0')
	{
		*v2 =*v2 * 10 + operand2[0] - '0';
		operand2++;
	}
}
char* get(char* sheet[10][10], char param[])
{
	char *res=(char*)malloc(50);
	copy(sheet[param[1] - '0'-1][param[0] - 'a'],res);
	if (has_only_val(res))
		return res;
	if (has_operators(res))
	{
		char operand1[50], operand2[50], oper;
		copyDatanOperators(res,operand1,operand2,&oper);
		if (has_operators(operand1)||!has_only_val(operand1))
			copy(get(sheet,operand1),operand1);
		if (has_operators(operand2) || !has_only_val(operand2))
			copy(get(sheet,operand2),operand2);
		int v1 = 0, v2 = 0;
		copyOperands(operand1, operand2, &v1, &v2);
		
		switch (oper)
		{
		case '+':sprintf(res, "%d", v1 + v2); break;
		case '-':sprintf(res, "%d", v1 - v2); break;
		case '*':sprintf(res, "%d", v1*v2); break;
		case '/':sprintf(res, "%d", v1 / v2); break;
		}
		return res;
	}
	else
		return get(sheet,res);
}
int is_makeCycle(char *str, char *sheet[10][10], char *cell)
{

	char operand1[50], operand2[50], oper; 
	int status=0;
	copyDatanOperators(str, operand1, operand2, &oper);
	if (!has_only_val(operand1))
	{
		if (check(cell,operand1))
			return 1;
		status=is_makeCycle(sheet[operand1[1]-'0'-1][operand1[0]-'a'], sheet, cell);
	}
	if (status == 1)
		return 1;
	if (oper == '\0')
		return 0;
	
	if (!has_only_val(operand2))
	{
		if (check(cell, operand2))
			return 1;
		status = is_makeCycle(sheet[operand2[1] - '0' - 1][operand2[0] - 'a'], sheet, cell);
	}
	return status;
}
void set(char* sheet[10][10], char param[])
{
	int i , j ;
	char *cell=(char*)malloc(3); 
	cell[1] = param[1]; cell[0] = param[0]; cell[2] = '\0';
	param += 3;
	int val_i = 0;
	char val[50];
	while (param[0] != '\0')
	{
		val[val_i++] = param[0];
		param++;
	}
	val[val_i] = '\0';
	if (is_makeCycle(val, sheet,cell))
		printf("cant insert this - has cycle\n");
	else
		copy(val, sheet[cell[1]-'0'-1][cell[0]-'a']);
}
void print(char *sheet[10][10])
{
	char cell[3];
	printf("%5c", ' ');
	for (int i = 0; i < 10; i++)
		printf("%5c", i + 'A');
	printf("\n\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%3d |", i + 1);
		for (int j = 0; j < 10; j++)
		{
			cell[0] = j + 'a';
			cell[1] = i + 1 + '0';
			printf("%5s", get(sheet,cell));
			//printf("%5s ", sheet[i][j]);
		}
		printf("\n");
	}
}
void write_to_file(FILE *fp, char* sheet[10][10])
{
	char val[6];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			copy(sheet[i][j],val);
			fputs(val, fp);
			fputc(',', fp);
		}
		fputc('\n', fp);
	}
}
void load_row(FILE *fp, char *sheet[10][10],int row_val)
{
	char c,val[6];
	int cell_i=0,val_i=0;
	while ((c = fgetc(fp)) != '\n')
	{
		if (c == ',')
		{
			val[val_i] = '\0';
			copy(val, sheet[row_val][cell_i]);
			val_i = 0;
			cell_i++;
			continue;
		}
		val[val_i++] = c;
	}
	
}
void load_excel(FILE *fp, char *sheet[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		load_row(fp, sheet, i);
	}
}

void make_all_zero(char *sheet[10][10])
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
		{
			sheet[i][j] = (char*)malloc(6);
			copy("0", sheet[i][j]);
		}
}
void to_lower(char *str)
{
	while (str[0] != '\0'){
	if (str[0] >= 65 && str[0] <= 90)
		str[0] = str[0] + 32;
	str++;
	}
}
int main()
{
	char *cmd,cmd1[10],param[10],file_name[32];
	file_name[0] = '\0';
	cmd = (char *)malloc(10);
	char *sheet[10][10];
	make_all_zero(sheet);
	FILE *fp_export, *fp_imp;
	while (1)
	{
		printf(">");
		gets(cmd);
		to_lower(cmd);
		//remove_extra_space(cmd);
		if (check(cmd, "print"))
		{
			print(sheet);
			continue;
		}
		if (check(cmd, "exit"))
			break;
		if (check(cmd, "save"))
		{
			if (file_name[0]=='\0')
			{
				printf("No file Exists\n");
				continue;
			}
			fp_export = fopen(file_name, "w");
			write_to_file(fp_export, sheet);
			fclose(fp_export);
			continue;
		}
		seperate_cmd_param(cmd,cmd1,param);

		if (check(cmd1, "export"))
		{
			if (file_name[0]=='\0')
				copy(param,file_name);
			fp_export = fopen(file_name, "w");
			write_to_file(fp_export, sheet);
			fclose(fp_export);
			continue;
		}
		if (check(cmd1, "import"))
		{
			if (file_name[0] == '\0')
				copy(param, file_name);
			fp_imp=fopen(file_name, "r");
			load_excel(fp_imp, sheet);
			fclose(fp_imp);
			continue;
		}
		if (check(cmd1, "get"))
		{
			printf("%s\n",get(sheet,param));
			continue;
		}
		else if (check(cmd1, "set"))
		{
			set(sheet, param);
			continue;
		}
	}
	return 0;
}