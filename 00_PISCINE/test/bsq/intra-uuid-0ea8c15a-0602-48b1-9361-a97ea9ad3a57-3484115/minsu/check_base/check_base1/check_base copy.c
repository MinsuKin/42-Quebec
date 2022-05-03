#include <stdlib.h>
#include <stdio.h>

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

int map[1000][1000];
int row;
int col;
int dp[1000][1000];

int board[12][16] = {
    {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,1,1,0,0,1,0,0,0,1,1,0,1,0},
    {0,0,0,1,1,0,1,1,1,1,1,1,1,0,1,0},
    {0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,0,0,1,0},
    {0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0},
    {0,0,1,0,0,0,0,1,0,0,1,1,1,0,1,0},
    {0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0}
};

int     main() 
{
    col = sizeof(board) / sizeof(board[0]);
    row = sizeof(board[0]) / sizeof(int);
    int tab[col][row];
    printf("arr의 세로길이 : %d\narr의 가로길이 : %d\n", col, row);

    int i = 1;
    while (i < col)
    {
        if (row != sizeof(board[i]) / sizeof(int))
            printf("differ");
        if (row == sizeof(board[i]) / sizeof(int))
            printf("same\n");
        i++;
    }
}