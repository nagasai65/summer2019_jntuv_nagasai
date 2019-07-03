/*
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
struct node
{
	char filename[16];
	unsigned int offset;
	unsigned int len;
};
void get_commandNparam(char *query, char* command, char *param)
{
	int index = 0;
	while (query[0] != ' '&&query[0] != '\0')
	{
		command[index++] = query[0];
		query++;
	}
	command[index] = '\0';
	index = 0;
	while (query[0] == ' ')
		query++;
	while (query[0] != '\0')
	{
		param[index++] = query[0];
		query++;
	}
	param[index] = '\0';
}
int check(char *str1, char *str2)
{
	while (str1[0] != '\0' && str2[0] != '\0')
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
void format_data(FILE *fp,int *nooffiles)
{
	printf("%d file(s) Deleted",*nooffiles);
	*nooffiles = 0;
	fseek(fp, 0, SEEK_SET);
	fwrite(nooffiles, sizeof(int), 1, fp);
	printf("Success\n");
}
void files_list(FILE *HDDfp, int nooffiles)
{ 
	fseek(HDDfp, sizeof(int), SEEK_SET);
	struct node *met_block=(struct node*)malloc(sizeof(struct node));
	printf("Total : %d file(s)\n", nooffiles);
	while (nooffiles--)
	{
		if (!fread(met_block, sizeof(struct node), 1, HDDfp))
		{
			printf("unable to get");
			exit(0);
		}
		printf("%s - %d - %d\n", met_block->filename,met_block->offset,met_block->len);
	}
}
int make_copy_tohdd(FILE *HDDfp, int offset, char *filename)
{
	FILE *new_file = fopen(filename, "rb");
	if (new_file == NULL)
	{
		printf("File cant open");
		exit(0);
	}
	int len = 0;
	char ch;
	fseek(HDDfp, offset-1, SEEK_END);
	while (!feof(new_file))
	{
		fread(&ch, sizeof(ch), 1, new_file);
		if (!fwrite(&ch, sizeof(ch), 1, HDDfp))
		{
			printf("unable to write data to disk");
			exit(0);
		}
		len++;
		fseek(HDDfp, -2, SEEK_CUR);
	}
	return len;
}
void copy_fileToHDD(FILE *fp, int *nooffiles, char *param)
{
	int lastFileOffset=0,lastFileLength=0,len;
	char *filename = (char*)malloc(16);
	struct node *lastnode,*new_met;
	lastnode = (struct node*)malloc(sizeof(struct node));
	fseek(fp, sizeof(int), SEEK_SET);
	if (*nooffiles)
	{
		fseek(fp, sizeof(struct node)*(*nooffiles - 1), SEEK_CUR);
		if (!fread(lastnode, sizeof(struct node), 1, fp))
		{
			printf("unable to get data");
			exit(0);
		}
		lastFileOffset = lastnode->offset;
		lastFileLength = lastnode->len;
		fseek(fp, sizeof(struct node), SEEK_CUR);
	}
	new_met = (struct node*)malloc(sizeof(struct node));
	new_met->offset = lastFileOffset+lastFileLength;
	sprintf(new_met->filename, "%s", param);
	len=make_copy_tohdd(fp, new_met->offset, new_met->filename);

	new_met->len = len;

	fseek(fp, sizeof(int), SEEK_SET);
	fseek(fp, sizeof(struct node)*(*nooffiles), SEEK_CUR);
	if (!fwrite(new_met, sizeof(struct node), 1, fp))
	{
		printf("unable to put data");
		exit(0);
	}
	*nooffiles = *nooffiles + 1;
	fseek(fp, 0, SEEK_SET);
	
	if (!fwrite(nooffiles, sizeof(int), 1, fp))
	{
		printf("unable to put data");
		exit(0);
	}
}
void make_copyToOut(FILE *HDDfp, int offset, int len, char *filename)
{
	FILE *new_file = fopen(filename, "wb");
	if (!new_file)
	{
		printf("Error opening destination file");
		exit(0);
	}
	char ch;
	fseek(HDDfp, offset-1, SEEK_END);
	while (len!=0)
	{
		len--;
		if (!fread(&ch, sizeof(ch), 1, HDDfp))
		{

			printf("unable to copy from disk to buffer\n");
			exit(0);
		}
		printf("%c", ch);
		if (fwrite(&ch, sizeof(ch), 1, new_file))
		{
			printf("Error in copy from buffer to file");
			exit(0);
		}
		fseek(HDDfp, -2, SEEK_CUR);
	}
	fclose(new_file);
}
void copy_fileFromHDD(FILE *HDDfp, int nooffiles, char *param)
{
	char file1[16], file2[16];
	get_commandNparam(param, file1, file2);
	fseek(HDDfp, sizeof(int), SEEK_SET);
	struct node *curr_met = (struct node*)malloc(sizeof(struct node));
	while (nooffiles--)
	{
		if (!fread(curr_met, sizeof(struct node), 1, HDDfp))
		{
			printf("Error Reading Structure");
		}
		if (check(curr_met->filename, file1))
		{
			make_copyToOut(HDDfp, curr_met->offset, curr_met->len, file2);
			printf("%s", curr_met->filename);
			break;
		}
	}
}
int main()
{
	FILE *fp;
	fp = fopen("harddisk.hdd","rb+");
	if (fp == NULL)
	{
		printf("Error opening File\n");
		return 0;
	}
	char *query=(char*)malloc(50);
	char *command = (char*)malloc(10);
	char *param = (char*)malloc(40);
	int nooffiles=0;
	
	if (!fread(&nooffiles, sizeof(int), 1, fp))
	{
		fwrite(&nooffiles, sizeof(int), 1, fp);
	}

	while (1)
	{
		printf(">");
		gets(query);
		get_commandNparam(query, command, param);
		if (check(command, "format"))
		{
			format_data(fp,&nooffiles);
			continue;
		}
		if (check(command, "list"))
		{
			files_list(fp,nooffiles);
			continue;
		}
		if (check(command, "copyToDisk"))
		{
			copy_fileToHDD(fp, &nooffiles, param);
			printf("FILE Copied\n");
			continue;
		}
		if (check(command, "copyFromDisk"))
		{
			copy_fileFromHDD(fp, nooffiles, param);
			continue;
		}
		if (check(command, "exit"))
			break;
	}
	fclose(fp);
}
*/