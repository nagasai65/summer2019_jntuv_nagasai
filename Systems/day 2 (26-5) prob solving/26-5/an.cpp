#include<stdio.h>
long an(int a, int n)
{
	if (n == 1)
		return a;
	long temp = an(a,n / 2);
	if (n%2==1)
		return temp*temp*a;
	return temp*temp;
}
int an_m()
{
	long res = an(10, 9);
	printf("%ld", res);
	return 0;
}