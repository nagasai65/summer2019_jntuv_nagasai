#include<stdio.h>
int sum(int a[], int len)
{
	if (len == 1)
		return a[0];
	return sum(a+1, len - 1) + a[0];

}
int sum_main()
{
	int a[] = { 1, 2, 3, 4, 5 };
	printf("%d",sum(a, 5));
	return 0;
}