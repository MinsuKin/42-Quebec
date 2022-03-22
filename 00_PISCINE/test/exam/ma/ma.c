  
#include <stdlib.h>
#include <stdio.h>

int		*ft_range(int min, int max)
{
	int n;
	int *s;

	n = max >= min ? max - min : min - max;
	if (!(s = (int *)malloc(sizeof(int) * (n))))
		return (NULL);
	while (max != min)
		*s++ = max > min ? min++ : min--;
	*s = min;
	return (s - n);
	
}

int main()
{
	int *i = ft_range(-3, 1);
	int j;

	j = 0;
	while(i[j])
	{
		printf("%d\n", i[j]);
		j++;
	}
}