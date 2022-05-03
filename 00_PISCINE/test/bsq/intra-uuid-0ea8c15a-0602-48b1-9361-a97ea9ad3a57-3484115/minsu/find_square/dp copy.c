#include <stdlib.h>
#include <stdio.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int map[1000][1000];
int row;
int col;
int dp[1000][1000];
//int min(int A, int B) { if (A < B) return A; return B; }

int board[12][16] = {
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,1,1,0,0,1,0,0,0,1,1,0,1,0},
    {0,0,0,1,1,0,1,1,1,0,1,1,1,0,1,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,0},
    {0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,0},
    {0,0,1,0,0,0,0,1,0,0,1,1,1,0,1,0},
    {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0}
};

int     main() 
{
	int i;
	int k;

	row = 16;
	col = 12;
	i = 0;
	while(i < row)
	{
		k = 0;
		while(k < col)
		{
			map[i][k] = board[i][k];
			dp[i][k] = board[i][k];
		}
	}
	for (int i = 0; i < row; i++) {
		for (int k = 0; k < col; k++) {
			map[i][k] = board[i][k];
			dp[i][k] = board[i][k];
		}
	}
	int answer = map[0][0];


	for (int i = 1; i < row; i++) {
		for (int k = 1; k < col; k++) {
			if (map[i][k] == 1) {
				dp[i][k] = MIN(dp[i - 1][k - 1], MIN(dp[i - 1][k] ,dp[i][k - 1])) + 1;
				if (answer < dp[i][k])
					answer = dp[i][k];
			}
		}
	}

	printf("%d", answer*answer);
}
