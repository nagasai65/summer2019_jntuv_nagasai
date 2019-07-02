#include <stdio.h>
void print_perm(int res[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d", res[i]);
	}
	printf("\n");
}
int remove(int available[], int location)
{
	int data = available[location];
	available[location] = -1;
	return data;
}
void add(int arr[], int location, int data)
{
	arr[location] = data;
}
void permutation(int available[],int available_len,int prevchoice[],int current,int limit)
{
	if (current == limit)
	{
		print_perm(prevchoice,current);
		return;
	}
	int temp;
	for (int i = 0; i < available_len; i++)
	{
		if (available[i] == -1)
			continue;
		temp = remove(available, i);
		add(prevchoice, current, temp);
		permutation(available, available_len, prevchoice, current + 1,limit);
		add(available, i, temp);
	}
}
int permutation_main()
{
	int available[] = { 4, 3, 6 };
	int prevchoice[3];

	permutation(available,3, prevchoice,0,3);
	return 0;
}