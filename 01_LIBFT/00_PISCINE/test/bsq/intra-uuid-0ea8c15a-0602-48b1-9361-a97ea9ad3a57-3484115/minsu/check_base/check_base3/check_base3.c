#include <stdio.h>               
#include <string.h>   

int main()
{
    char board[10][29] = {
        "9.ox",
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

    int i = 0;

    char char_row = board[0][0];
    char char_empty = board[0][1];
    char char_obstacle = board[0][2];
    char char_full = board[0][3];


    while (board[1][i])
        i++;
    if (i == 0)
        printf("no line\n");
    else
        printf("%d\n", i);

    int k;
    int j = 1;
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