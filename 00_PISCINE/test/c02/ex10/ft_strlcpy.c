/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:14:42 by minkim            #+#    #+#             */
/*   Updated: 2021/03/03 14:35:03 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
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
}

int		main(void)
{
	char *i = "bbbb";
	char u[] = "aaaaaa";
	printf("\n\n%d\n\n", ft_strlcpy(u, i, 6));
	printf("\n\n%lu\n\n", strlcpy(u, i, 6));
}
