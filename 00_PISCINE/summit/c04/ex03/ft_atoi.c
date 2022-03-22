/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:07:12 by minkim            #+#    #+#             */
/*   Updated: 2021/02/23 10:24:01 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
