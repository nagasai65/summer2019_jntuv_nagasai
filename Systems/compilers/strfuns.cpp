
void splitString(char *line, char *str1, char* str2, char sep)
{
	while (line[0] == ' ')
		line++;
	int index = 0;
	while (line[0] != sep && line[0] != '\0' && line[0] != ' ' && line[0] != '\n')
	{
		str1[index++] = line[0];
		line++;
	}
	str1[index] = '\0';
	if (line[0] == '\0')
	{
		str2[0] = '\0';
		return;
	}
	if (str2[0] == '\0')
		return;
	index = 0;
	while (line[0] == ' ' || line[0] == sep)
		line++;
	while (line[0] != '\n' && line[0] != '\0')
	{
		str2[index++] = line[0];
		line++;
	}

	str2[index] = '\0';
}

char check(char *str1, char *str2)
{
	while (str1[0] != '\0' && str2[0] != '\0')
	{
		if (str1[0] != str2[0])
			return 0;
		str1++;
		str2++;
	}
	if (!str1[0] && !str2[0])
		return 1;
	return 0;
}

char checkSymbolInStr(char *str, char c)
{
	while (str[0] != '\0' && str[0] != c)
		str++;
	if (str[0] == '\0')
		return 0;
	return 1;
}
void rtrim(char *str)
{
	while (str[0] != '\n'&&str[0] != ' ')str++;
	str[0] = '\0';
}