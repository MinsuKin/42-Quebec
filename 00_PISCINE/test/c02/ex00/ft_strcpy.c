/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:38:12 by minkim            #+#    #+#             */
/*   Updated: 2021/03/04 10:44:33 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

int		main(void)
{
	char *i = "minsu";
	char *u ;
	printf("%s\n", i);
	ft_strcpy(u, i);
	// strcpy(u, i);
	printf("%s\n", u);
	printf("%s\n", i);
	printf("%c\n", i[3]);
	printf("%c\n", i[4]);
	printf("%d\n", i[5]);
	printf("%d\n", i[6]);

	printf("%s\n", u);
	printf("%c\n", u[0]);
	printf("%c\n", u[1]);
	printf("%c\n", u[2]);
	printf("%c\n", u[3]);
	printf("%c\n", u[4]);
	printf("%d\n", u[5]);
	printf("%d\n", u[6]);
	printf("%d\n", u[7]);
}
