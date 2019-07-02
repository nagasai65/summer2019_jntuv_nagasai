#include <stdio.h>
void mul(int A[2][2], int n)
{
	int res[2][2];
	while (n--){
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				res[i][j] = 0;
				for (int k = 0; k < 2; k++)
				{
					res[i][j] += A[i][k] * A[k][j];
				}
			}
		}
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
				A[i][j] = res[i][j];
		}
	}
}
int nthfib_main()
{
	int A[][2] = {
		{0,1},
		{1,1}
	};
	int x0[2][1] = {
		{ 0 }, {1}
	};
	int res[2][1];
	mul(A, 5);
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 1; j++)
		{ 
			res[i][j] = 0;
			for (int k = 0; k < 2; k++)
			{
				res[i][j] += A[i][k] * x0[k][j];
			}
		}
	}
	printf("%d", res[0][0]);
	return 0;
}