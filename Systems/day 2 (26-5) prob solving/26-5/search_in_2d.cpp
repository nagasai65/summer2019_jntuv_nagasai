#include <stdio.h>
void set_row_col(int *cr, int *cc, int row, int col, int direction)
{
	switch (direction)
	{
	case 0:*cr = row ; *cc = col - 1; break;
	case 1:*cr = row - 1; *cc = col-1; break;
	case 2:*cr = row - 1; *cc = col ; break;
	case 3:*cr = row-1; *cc = col + 1; break;
	case 4:*cr = row ; *cc = col + 1; break;
	case 5:*cr = row + 1; *cc = col+1; break; 
	case 6:*cr = row + 1; *cc = col ; break;
	case 7:*cr = row+1; *cc = col - 1; break;
	}
}
void find_next(char table[][5], char str[], int char_pos,int row,int col, int direction,int start_i,int start_j,int noofrows,int noofcols)
{
	
	if (str[char_pos] == '\0')
	{
		printf("(%d %d)-(%d %d)-%s\n", start_i,start_j,row,col,str);
		return;
	}
	int cur_row, cur_col;
	set_row_col(&cur_row, &cur_col,row,col, direction);
	if (cur_row < 0 || cur_col < 0 || cur_col >= noofcols || cur_row >= noofrows)
		return;
	if (str[char_pos] == table[cur_row][cur_col])
		find_next(table, str, char_pos + 1, cur_row, cur_col, direction,start_i,start_j,noofrows,noofcols);
}
void search(char table[][5], char str[],int char_pos,int start_i,int start_j,int noofrows,int noofcols)
{

	for (int i = start_i; i < 5; i++)
	{
		for (int j = start_j; j < 5; j++)
		{
			if (table[i][j] == str[char_pos])
			{
				for (int direction = 0; direction < 8; direction++)
					find_next(table, str, char_pos + 1, i, j, direction,i,j,noofrows,noofcols);

				//search(table, str, 0, i, j + 1,noofrows,noofcols);
			}
		}
	}
}
void find(char table[][5], char strings[][6])
{
	for (int i = 0; i < 4; i++)
	{
		search(table, strings[i],0,0,0,5,5);
	}
}
int search2d_main()
{
	char table[][5] = {
		'h','i','h','i','i',
		'e','e','a','h','t',
		'a','r','l','t','g',
		't','t','u','l','v',
		'w','x','y','z','o'
	};
	char strings[][6] = {
		"hi",
		"eat",
		"hello",
		"zure"
	};
	find(table, strings);
	return 0;
}