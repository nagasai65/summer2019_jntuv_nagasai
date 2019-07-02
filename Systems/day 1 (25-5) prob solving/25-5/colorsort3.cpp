#include<stdio.h>

void sort(int *a, int n)
{
	int k = 0, i = 0, j;
	while (i < n)
	{
		while (a[i] == k)
		{
			i++;
		}
		j = i + 1;
		while (j < n)
		{
			if (a[j] == k)
			{
				int t = a[i];
				a[i] = a[j];
				a[j] = t;
				i++;
			}
			j++;
		}
		k++;
	}
}
int colorsort3_main()
{
	int a[] = { 0,2,2,1,0,0,1,2 ,0, 1, 1 };
	int n = 11;
	sort(a, n);
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	return 0;
}