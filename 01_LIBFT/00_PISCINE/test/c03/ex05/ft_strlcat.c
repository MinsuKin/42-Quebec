/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:50:39 by minkim            #+#    #+#             */
/*   Updated: 2021/02/23 12:38:35 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int i;
	unsigned int j;
	unsigned int y;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	if (i > size)
		y = size;
	else
		y = i;
	while (src[j] && i < size - 1)
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	j = 0;
	while (src[j])
		j++;
	return (y + j);
}

int		main(void)
{
	char i[4] = "min";
	char u[] = "SUuuu";
	printf("%u\n\n\n", ft_strlcat(i, u, 4));
	// printf("%lu\n\n\n", strlcat(i, u, 4));
	printf("%s\n", i);
	printf("%c\n", i[0]);
	printf("%c\n", i[1]);
	printf("%c\n", i[2]);
	printf("%c\n", i[3]);
	// printf("%c\n", i[4]);
	// printf("%d\n", i[5]);
	// printf("%d\n", i[6]);
}
