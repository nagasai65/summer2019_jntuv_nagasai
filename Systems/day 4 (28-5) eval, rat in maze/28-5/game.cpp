#include<stdio.h>
void get_nextPos(int curr_i,int curr_j,int *new_i,int *new_j,int direction)
{
	switch (direction)
	{
	case 0:*new_i = curr_i+1; *new_j = curr_j; break;
	case 1:*new_i = curr_i; *new_j = curr_j+1; break;
	case 2:*new_i = curr_i-1; *new_j = curr_j ; break;
	case 3:*new_i = curr_i ; *new_j = curr_j-1;
	}
}
void print(char matrix[5][5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}
int is_validMove(int new_i,int new_j,int m,int n)
{
	if (new_i < m&&new_i >= 0 && new_j >= 0 && new_j < n)
		return 1;
	return 0;
}

int solve(char matrix[][5], int start_i, int start_j, int end_i, int end_j,char visited[][5], int m, int n)
{
	if (start_i == end_i&&start_j == end_j)
	{
		visited[start_i][start_j] = 1;
		return 1;
	}
	int new_i=0, new_j=0,sol=0;
	if (matrix[start_i][start_j]){
		visited[start_i][start_j] = 1;
		for (int direction = 0; direction < 4; direction++)
		{
			get_nextPos(start_i, start_j, &new_i, &new_j, direction);
			if (is_validMove(new_i,new_j,m,n)&&!visited[new_i][new_j]&&matrix[new_i][new_j])
				sol=solve(matrix, new_i, new_j, end_i, end_j, visited, m, n);
			if (sol)
				return 1;
		}
		visited[start_i][start_j] = 0;
	}
	return 0;
}
int game_main()
{
	char matrix[5][5] = {
		{1,1,1,1,1},
		{1,0,1,1,1},
		{1,1,0,1,1},
		{0,0,0,0,1},
		{1,1,1,1,1}
	};
	int m = 5, n = 5;
	char visited[5][5] = { 0 };
	if (solve(matrix, 0, 0, 4, 0, visited, m, n))
		print(visited);
	else
		printf("Not Possible");
	return 0;
}