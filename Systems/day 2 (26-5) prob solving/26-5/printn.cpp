#include <stdio.h>

void print(int a[], int pos)
{
	int zeroflag = 1;
	for (int i = 0; i < pos; i++)
	{
		if (zeroflag&&a[i] == 0)
			continue;
		if (a[i] != 0)
			zeroflag = 0;
		switch (a[i])
		{
		case 0:printf("0");
			break;
		case 1:printf("1");
			break;
		case 2:printf("2");
			break;
		case 3:printf("E");
			break;
		case 4:printf("h");
			break;
		case 5:printf("S");
			break;
		case 6:printf("9");
			break;
		case 7:printf("L");
			break;
		case 8:printf("8");
			break;
		case 9:printf("6");
			break;
		}
	}
	printf("\n");
}
void printnums(int a[], int limit,int current)
{
	if (current < limit)
	{
		for (int i = 0; i <= 9; i++)
		{
			a[current] = i;
			printnums(a, limit, current + 1);
		}
	}
	if (current == limit)
		print(a, limit);
}
int printn_main()
{
	int a[10];
	printnums(a,3,0);
	return 0;
}