/*#define _CRT_SECURE_NO_WARNINGS
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
char* get(char* sheet[10][10], char param[])
{
	return sheet[param[0] - 'a'][param[1] - '0'-1];
}
void set(char* sheet[10][10], char param[])
{
	int i = param[0] - 'a', j = param[1] - '0'- 1;
	param += 3;
	int val_i = 0;
	char val[6];
	while (param[0] != '\0')
	{
		val[val_i++] = param[0];
		param++;
	}
	val[val_i] = '\0';
	copy(val, sheet[i][j]);
}
void print(char *sheet[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			printf("%s ", sheet[i][j]);
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
	}*/