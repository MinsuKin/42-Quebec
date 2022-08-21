/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:58:48 by minkim            #+#    #+#             */
/*   Updated: 2022/07/18 14:04:02 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_sign(long long is_negative, const char *str)
{
	if ((*str == '+' || *str == '-'))
	{
		if (*str == '-')
			is_negative *= -1;
	}
	return (is_negative);
}

int	bigger_than_llong(const char *str)
{
	long long	is_negative;
	long long	result;
	int			check_next;

	result = 0;
	is_negative = check_sign(1, str);
	str++;
	check_next = 0;
	while (*str >= 48 && *str <= 57)
	{
		if (result > LLONG_MAX / 10)
			return (1);
		if (result == LLONG_MAX / 10)
			check_next = 1;
		if (check_next == 1)
		{
			if (is_negative == 1 && *str > '7')
				return (1);
			if (is_negative == -1 && *str > '8')
				return (1);
		}
		result = result * 10 + *str - 48;
		str++;
	}
	return (0);
}
