#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define BUFFER_SIZE 5
void readRun(FILE *input_file, int *buffer)
{
	int index=0;
	while (fscanf(input_file, "%d", buffer+index))
	{
		index++;
		if (index == BUFFER_SIZE)
			break;
	}
}
void sortRun(int *buffer)
{
	int temp;
	for (int i = 0; i < BUFFER_SIZE - 1; i++)
	{
		for (int j = 1; j < BUFFER_SIZE - i; j++)
		{
			if (buffer[j] < buffer[j - 1])
			{
				temp = buffer[j];
				buffer[j] = buffer[j - 1];
				buffer[j - 1] = temp;
			}
		}
	}
}
void writeRun(FILE *scratchPad, int *buffer)
{
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		fprintf(scratchPad, "%d", buffer[i]);
		fputc('\n',scratchPad);
	}
	fputs(".\n", scratchPad);
}
void sortByRuns(FILE *input_file, FILE *scratchPad, int *buffer)
{
	while (!feof(input_file)){
		readRun(input_file, buffer);
		sortRun(buffer);
		writeRun(scratchPad, buffer);
	}
	fclose(scratchPad);
	fclose(input_file);
}
void merge(FILE *ptr1, FILE *ptr2, FILE *output,char *buf1,char *buf2)
{
	int num1, num2;

fscanf(ptr1, "%s", buf1);
	if (feof(ptr2))
	{
		while (buf1[0] != '.')
		{
			sscanf(buf1, "%d", &num1);
			fprintf(output, "%d", num1);
			fputc('\n', output);
			fscanf(ptr1, "%s", buf1);
		}
		return;
	}
		
		
		while (buf1[0] != '.'&&buf2[0] != '.')
		{
			sscanf(buf1, "%d", &num1);
			sscanf(buf2, "%d", &num2);
			if (num1 < num2)
			{
				fprintf(output, "%d", num1);
				fputc('\n',output);
				fscanf(ptr1, "%s", buf1);
				continue;
			}
			fprintf(output, "%d", num2);
			fputc('\n', output);
			fscanf(ptr2, "%s", buf2);
		}
		while (buf1[0] != '.')
		{
			sscanf(buf1, "%d", &num1);
			fprintf(output, "%d", num1);
			fputc('\n', output);
			fscanf(ptr1, "%s", buf1);
		}
		while (buf2[0] != '.')
		{
			sscanf(buf2, "%d", &num2);
			fprintf(output, "%d", num2);
			fputc('\n', output);
			fscanf(ptr2, "%s", buf2);
		}
		fputs(".\n", output);
}
void mergeAllRuns()
{
	FILE *output,*ptr1,*ptr2;
	char file[3][10] = { "temp.txt", "temp1.txt" };
	int comeOut = 0;
	while (1){
		ptr1 = fopen(file[0], "r");
		ptr2 = fopen(file[0], "r");
		output = fopen(file[1], "w");
		char *buf1 = (char*)malloc(10);
		char *buf2 = (char*)malloc(10);
		int first_time = 1;
		while (1){
			while (1)
			{
				fscanf(ptr2, "%s", buf2);
				if (buf2[0] == '.')
					break;
			}
			fscanf(ptr2, "%s", buf2);
			if (first_time&&feof(ptr2))
			{
				comeOut = 1;
				break;
			}
			merge(ptr1, ptr2, output, buf1, buf2);
			while (1)
			{
				fscanf(ptr1, "%s", buf1);
				if (buf1[0] == '.')
					break;
			}
			first_time = 0;
			if (feof(ptr2))
				break;

		}
		if (comeOut)
			break;
		sprintf(file[2], "%s", file[0]);
		sprintf(file[0], "%s", file[1]);
		sprintf(file[1], "%s", file[2]);
		fclose(ptr1);
		fclose(ptr2);
		fclose(output);
	}
	printf("%s", file[0]);

}
int t_main()
{
	FILE *input_file,*scratchPad1;
	input_file = fopen("C:\\Users\\Dell\\Downloads\\input.txt", "r");
	scratchPad1 = fopen("temp.txt", "w");
	int *buffer1;
	buffer1 = (int*)malloc(sizeof(int) * BUFFER_SIZE);
	sortByRuns(input_file, scratchPad1, buffer1);
	mergeAllRuns();
	
	return 0;
}