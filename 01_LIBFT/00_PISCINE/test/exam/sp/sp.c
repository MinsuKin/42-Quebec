#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


char		**ft_split(char *str)
{
    int i;
    int j;
    int k;
    char **split;

    i = 0;
    while (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
        i++;
    if (!(split = (char **)malloc(sizeof(char *) * 256)))
        return (NULL);
    k = 0;
    while (str[i])
    {
        if (!(split[k] = (char *)malloc(sizeof(char) * 4096)))
            return (NULL);
        j = 0;
        while ((str[i] != '\t' && str[i] != '\n' && str[i] != ' '))
        {
            split[k][j] = str[i];
            i++;
            j++; 
        }
        while (str[i] == '\t' || str[i] == '\n' || str[i] == ' ')
            i++;
        split[k][j] = '\0';
        k++;
    }
    split[k] = NULL;
    return split;
}


int main()
{
    printf("\n%s\n", ft_split("    012 345  678   92342342")[2]);
}