/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:57:04 by minkim            #+#    #+#             */
/*   Updated: 2021/02/18 17:40:09 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		if (j == nb)
			break ;
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		main(void)
{
	char i[10] = "min";
	char u[] = "SUK";
	printf("%s\n", ft_strncat(i, u, 5));
	// printf("%s\n", strncat(i, u, 5));
	printf("%d\n", i[0]);
	printf("%d\n", i[1]);
	printf("%d\n", i[2]);
	printf("%d\n", i[3]);
	printf("%d\n", i[4]);
	printf("%d\n", i[5]);
	printf("%d\n", i[6]);
	printf("%d\n", i[7]);
}
