/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:38:12 by minkim            #+#    #+#             */
/*   Updated: 2021/02/17 18:49:58 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strcapitalize(char *str)
{
	int i;

	i = 1;
	if (str[0] >= 'a' && str[0] <= 'z')
		str[0] = str[0] - 32;
	while (str[i])
	{
		if ((!(str[i - 1] >= 'A' && str[i - 1] <= 'Z')) ||
		(!(str[i - 1] >= 'a' && str[i - 1] <= 'z')))
		{
			if (str[i] >= 'a' && str[i] <= 'z')
				str[i] = str[i] - 32;
		}
		if ((str[i - 1] >= 'A' && str[i - 1] <= 'Z') ||
		(str[i - 1] >= 'a' && str[i - 1] <= 'z') ||
		(str[i - 1] >= '0' && str[i - 1] <= '9'))
		{
			if (str[i] >= 'A' && str[i] <= 'Z')
				str[i] = str[i] + 32;
		}
		i++;
	}
	return (str);
}

int		main(void)
{
	char text1[] = "salut, comment tu vas ? 42mots quarante-deux; cinquante+et+un";
	printf("%s\n", ft_strcapitalize(text1));
	return (0);
}