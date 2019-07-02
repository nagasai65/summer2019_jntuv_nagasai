#include<stdio.h>
#include<stdlib.h>

int fib(int n,int *arr)
{
	if (n < 0)
	{
		printf("Not Possible");
		return -1;
	}
	if (arr[n] == -1)
	{
		if (n == 1 || n == 0)
			arr[n] = n;
		else
			arr[n] = fib(n - 1, arr) + fib(n - 2, arr);
	}
	return arr[n];
}
int fib_main()
{
	int *arr,n=5;
	arr = (int*)malloc(sizeof(int)*n+1);
	for (int i = 0; i <= n; i++)
		arr[i] = -1;
	printf("%d",fib(n,arr));
	return 0;
}