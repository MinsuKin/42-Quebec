/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:38:12 by minkim            #+#    #+#             */
/*   Updated: 2021/02/18 16:00:12 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_strupcase(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z') ||
		(str[i] >= 'a' && str[i] <= 'z')))
			return (0);
		i++;
	}
	return (1);
}

int		main(void)
{
	char *i = "0";
	printf("%d\n", ft_strupcase(i));
}
