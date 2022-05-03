/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:07:38 by minkim            #+#    #+#             */
/*   Updated: 2021/02/23 10:23:43 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_atoi(char *str)
{
	int result;
	int sign;

	result = 0;
	sign = 1;
	if (*str)
	{
		while ((*str >= 9 && *str <= 13) || (*str == ' '))
			str++;
		while ((*str == '+' || *str == '-'))
		{
			if (*str == '-')
				sign = sign * -1;
			str++;
		}
		while (*str >= '0' && *str <= '9')
		{
			result = result * 10 + (*str - '0');
			str++;
		}
		return (result * sign);
	}
	return (0);
}

int		main(void)
{
	printf("%d", ft_atoi(" ---+--+1234ab567"));
}

// str is not null 
// you handle the +  -
// you handle the space and tabs etc 
// you handle the numbers 