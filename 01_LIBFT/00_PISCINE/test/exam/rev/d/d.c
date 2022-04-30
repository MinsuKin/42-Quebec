#include <unistd.h>
#include <string.h>
#include <stdio.h>

void    ft_swap_char(char *a, char *b)
{
    char c;

    c = *a;
    *a = *b;
    *b = c;
}

char    *ft_strrev(char *str)
{
    int     index;
    int     size;

    size = 0;
    while (str[size])
        size++;
    index = 0;
    while (index < size / 2)
    {
        ft_swap_char(&str[index], &str[size - 1 - index]);
        index++;
    }
    return (str);
}




int main()
{
    char i[] = "minsum";
    
    ft_strrev(i);
    printf("%s", i);
}