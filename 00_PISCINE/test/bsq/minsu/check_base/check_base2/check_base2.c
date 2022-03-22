#include <stdio.h>               
#include <string.h>   

int main()
{
    char board[10][28] = {
        "9.ox",
        "...........................", 
        "....o......................", 
        "............o..............", 
        "...........................", 
        "....o......................",  
        "...............o...........", 
        "...........................", 
        "......o..............o.....", 
        "..o.......o...............9"
    };

    int i = 0;

    char char_row = board[0][0];
    char char_empty = board[0][1];
    char char_obstacle = board[0][2];
    char char_full = board[0][3];


    while (board[1][i])
        i++;
    printf("%d\n", i);

    int k;
    int j = 1;
    while (board[j][0] == char_empty || board[j][0] == char_obstacle)
    {
        k = 0;
        while (board[j][k] == char_empty || board[j][k] == char_obstacle)
        {
            printf("%c", board[j][k]);
            k++;
        }
        printf("\n");
        if (k != i)
            printf("%d\n", k);
        j++;
    }
    return 0;
}