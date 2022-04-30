#include <stdio.h>               
#include <string.h>   

int main()
{
	char board[10][29] = {
		"9.ox\n",
		"...........................\n",
		"....o......................\n",
		"............o..............\n",
		"...........................\n",
		"....o......................\n", 
		"...............o...........\n",
		"...........................\n",
		"......o..............o.....\n",
		"..o.......o...............9\n"
	};

	char char_empty;
	char char_obstacle;
	char char_full;
	int char_row;

	int ex_row;
	int j = 0;
	int x = 10;

	while (board[0][j])
		j++;
	
	char_row = 0;
	ex_row = j;
	if (j > 4)
	{
		while(j >= 0)
		{
			if(ex_row - 1 == j)
			{
				if (board[0][j] != '\n')
					return 0;
			}
			if(ex_row - 2 == j)
				char_full = board[0][j];
			if(ex_row - 3 == j)
				char_obstacle = board[0][j];
			if(ex_row - 4 == j)
				char_empty = board[0][j];
			if(ex_row - 5 == j)
				char_row = board[0][j] - '0';
			if(ex_row - 6 >= j)
			{
				char_row = char_row + ((board[0][j] - '0') * x);
				x = x * 10;
			}
			j--;
		}
	}

	printf("%c\n", char_full);
	printf("%c\n", char_obstacle);
	printf("%c\n", char_empty);
	printf("%d\n", char_row);


	int i = 0;
	while (board[1][i])
		i++;
	if (i == 0)
		printf("no line\n");
	else
		printf("%d\n", i);

	int k;
	j = 1;
	while (board[j][0] == char_empty || board[j][0] == char_obstacle)
	{
		k = 0;
		while (board[j][k] == char_empty || board[j][k] == char_obstacle || board[j][k] == '\n')
		{
			k++;
		}
		printf("%s", board[j]);
		if (k != i)
			printf("%d\n", k);
		j++;
	}
	return 0;
}