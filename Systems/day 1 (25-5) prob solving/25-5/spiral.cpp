#include<stdio.h>
#include<stdlib.h>
#define ROW 4
#define COL 4
int get_top(int arr[ROW][COL], int *res, int res_i,int x, int y, int n)
{
	for (int i = y; i < n; i++)
	{
		res[res_i++] = arr[x][i];
	}
	return res_i;
}
int get_right(int arr[ROW][COL], int *res, int res_i, int x, int m, int n)
{
	for (int i = x; i < m; i++)
		res[res_i++] = arr[i][n];
	return res_i;
}
int get_bottom(int arr[ROW][COL], int *res, int res_i, int m, int n, int y)
{
	for (int i = n; i >= y; i--)
		res[res_i++] = arr[m][i];
	return res_i;
}
int get_left(int arr[ROW][COL], int *res, int res_i, int m, int x, int y)
{
	for (int i = m; i >= x; i--)
		res[res_i++] = arr[i][y];
	return res_i;
}
int* get_spiral_list(int arr[ROW][COL],int m,int n)
{
	int *res = (int*)malloc(sizeof(int)*m*n);
	int x=0, y=0,i,j,res_i=0;
	while (x < m||y < n)
	{
		res_i=get_top(arr,res,res_i, x, y, n);
		res_i=get_right(arr,res,res_i, x+1, m, n-1);
		res_i=get_bottom(arr,res,res_i, m - 1, n - 2, y);
		res_i=get_left(arr,res,res_i, m - 2, x + 1, y);
		x++; y++; m--; n--;
	}
	return res;
}
int spiral_main()
{
	int arr[][COL] = {
		{1,2,3,10},
		{4,5,6,11},
		{7,8,9,12},
		{13,14,15,16}
	};
	int *res=get_spiral_list(arr,ROW,COL);
	for (int i = 0; i < ROW*COL; i++)
		printf("%d ", res[i]);
		
	return 0;
}