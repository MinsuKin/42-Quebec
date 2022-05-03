/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 14:47:48 by minkim            #+#    #+#             */
/*   Updated: 2021/02/27 15:14:50 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_strcpy(char *dest, char *src)
{
	unsigned long i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*s2;

	i = 0;
	while (src[i])
		i++;
	s2 = (char *)malloc(sizeof(char) * i);
	if (s2)
		ft_strcpy(s2, src);
	return (s2);
}

int main() {
	char *s1 = "hello00000001";
	char *s2 = ft_strdup(s1);
	printf("%s\n",s2);
	printf("1\n");
	char *s3 = strdup(s1);
	printf("%s\n",s3);
	printf("1\n");
}