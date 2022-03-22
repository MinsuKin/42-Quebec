unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int i;

	i = 0;
	while (*dest && i < size)
	{
		++i;
		++dest;
	}
	while (*src && i + 1 < size)
	{
		*dest = *src;
		++dest;
		++src;
		++i;
	}
	if (i < size)
		*dest = 0;
	while (*src)
	{
		++i;
		++src;
	}
	return (i);
}


unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (dest[i] && i < size)
		i++;
	while (src[j] && i + j + 1 < size)
	{
		dest[i] = src[j];
		j++;
	}
	if (i < size)
		dest[i + j] = '\0';
	j = 0;
	while(src[j])
		j++;
	return (i + j);
}




#include <stdio.h>
#include <string.h>

int		main(void)
{
	char i[7] = "min";
	char u[] = "SUuuu";
	// printf("%u\n\n\n", ft_strlcat(i, u, 5));
	printf("%lu\n\n\n", strlcat(i, u, 5));
	printf("%s\n", i);
	printf("%c\n", i[0]);
	printf("%c\n", i[1]);
	printf("%c\n", i[2]);
	printf("%c\n", i[3]);
	printf("%c\n", i[4]);
	printf("%d\n", i[5]);
	printf("%d\n", i[6]);
}






