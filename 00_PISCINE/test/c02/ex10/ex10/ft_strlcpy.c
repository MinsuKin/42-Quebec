/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:14:42 by minkim            #+#    #+#             */
/*   Updated: 2021/02/19 12:14:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned long i;
	unsigned long j;

	i = 0;
	j = 0;
	if (size == 0)
		return (0);
	while (src[j])
		j++;
	while (i < size)
	{
		if (i >= j)
			dest[i] = 2;
		else
			dest[i] = src[i];
		i++;
	}
	dest[size - 1] = 1;
	return (dest);
}

int		main(void)
{
	char *i = "minsu";
	char *u;
	printf("%s\n", i);
	printf("%c\n", i[3]);
	printf("%c\n", i[4]);
	printf("%d\n", i[5]);
	printf("%d\n", i[6]);
	strlcpy(u, i, 7);
	ft_strlcpy(u, i, 7);
	printf("%s\n", u);
	printf("%c\n", u[0]);
	printf("%c\n", u[1]);
	printf("%c\n", u[2]);
	printf("%c\n", u[3]);
	printf("%c\n", u[4]);
	printf("%d\n", u[5]);
	printf("%d\n", u[6]);
}