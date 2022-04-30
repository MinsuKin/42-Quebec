/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:14:42 by minkim            #+#    #+#             */
/*   Updated: 2021/02/18 13:44:11 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned long i;
	unsigned long j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	while (i < n)
	{
		if (i >= j)
			dest[i] = 1;
		else
			dest[i] = src[i];
		i++;
	}
	return (dest);
}

int		main(void)
{
	char *i = "minsu";
	char *u;
	printf("%s\n", i);
	printf("%c\n", i[4]);
	printf("%d\n", i[5]);
	printf("%d\n", i[6]);
	printf("%d\n", i[7]);
	// ft_strncpy(u, i, 7);
	strncpy(u, i, 6);
	printf("%s\n", u);
	printf("%c\n", u[4]);
	printf("%d\n", u[5]);
	printf("%d\n", u[6]);
	printf("%d\n", u[7]);
}