#include<stdio.h>
#include<stdlib.h>
int** transpose(int **arr, int m, int n)
{
	int **res = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++)
	{
		res[i] = (int*)malloc(sizeof(int)*m);
		for (int j = 0; j < m; j++)
		{
			res[i][j] = arr[j][i];
		}
	}
	return res;
}
int transpose_main()
{
	int m , n ;
	scanf_s("%d %d", &m, &n);
	int **arr = (int**)malloc(sizeof(int*)*m);
	for (int i = 0; i < m; i++)
	{
		arr[i] = (int*)malloc(sizeof(int)*n);
	}
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			scanf_s("%d", &arr[i][j]);
	int **res;
	res=transpose(arr, m, n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", res[i][j]);
		}
		printf("\n");
	}
	return 0;
}