#include"headers.h"
#include"diskio.h"
#include"commands.h"
void seperate_command_parameters(char *query, char *command, char *param)
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
void seperate_parameters(char *param, char *param1, char *param2)
{
	int index = 0;
	while (param[0] == ' ')
		param++;
	while (param[0] != ' ')
	{
		param1[index++] = param[0];
		param++;
	}
	param1[index] = '\0';
	index = 0;
	while (param[0] == ' ')
		param++;
	while (param[0] != '\0')
	{
		param2[index++] = param[0];
		param++;
	}
	param2[index] = '\0';
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
int main()
{
	unsigned int noofblocks;
	char*str1 = (char*)malloc(50);
	char *str2 = (char*)malloc(50);
	char* str3 = (char*)malloc(50);
	int i;
	while (1){
		printf(">");
		gets(str1);
		seperate_command_parameters(str1,str2,str3);
		if (check(str2, "MOUNT"))
		{
			seperate_parameters(str3, str1,str2);
			sscanf(str2, "%d", &i);
			mountCommand(str1,i);
			continue;
		}
	}

}