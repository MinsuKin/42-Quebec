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

    char char_row;
    char char_empty;
    char char_obstacle;
    char char_full;
    int j = 0;
    while(board[0][j])
    {
        if (j == 0)
            char_row = board[0][j];
        if (j == 1)
            char_empty = board[0][j];
        if (j == 2)
            char_obstacle = board[0][j];
        if (j == 3)
            char_full = board[0][j];
        if (j == 4 && board[0][j] != '\n')
            printf("\\n missing\n");
        j++;
    }
    if (j != 5)
        printf("something missing\n");




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