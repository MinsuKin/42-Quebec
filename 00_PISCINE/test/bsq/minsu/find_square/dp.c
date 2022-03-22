#include <stdlib.h>
#include <stdio.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int map[1000][1000];
int row;
int col;
int dp[1000][1000];

int board[12][16] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1},
    {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1}
};

int     main() 
{
	int i;
	int k;
	int x;
	int y;

	col = 12;
	row = 16;
	i = 0;
	while(i < col)
	{
		k = 0;
		while(k < row)
		{
			map[i][k] = board[i][k];
			dp[i][k] = board[i][k];
			k++;
		}
		i++;
	}
	int answer = map[0][0];

	i = 1;
	while(i < col)
	{
		k = 1;
		while(k < row)
		{
			if (map[i][k] == 1) {
				dp[i][k] = MIN(dp[i - 1][k - 1], MIN(dp[i - 1][k] ,dp[i][k - 1])) + 1;
				if (answer < dp[i][k])
				{
					answer = dp[i][k];
					x = i;
					y = k;
				}
			}
			k++;
		}
		i++;
	}

	i = 0;
	while(i < col)
	{
		k = 0;
		while(k < row)
		{
			if (i >= (x - answer + 1) && i <= x &&
			k >= (y - answer + 1) && k <= y)
				dp[i][k] = 9;
			printf("%d ", dp[i][k]);
			k++;
		}
		printf("\n");
		i++;
	}
	printf("%d", answer*answer);
}
