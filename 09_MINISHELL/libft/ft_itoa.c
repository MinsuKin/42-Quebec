/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 12:14:15 by tgarriss          #+#    #+#             */
/*   Updated: 2021/09/22 14:41:10 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// if number is <= 0, it must have at least one digit
// the variable gets re-used if the following check is true
static size_t	get_len(int n)
{
	size_t	num_digits;

	num_digits = 0;
	if (n <= 0)
		num_digits = 1;
	while (n != 0)
	{
		n /= 10;
		num_digits++;
	}
	return (num_digits);
}

static char	*make_string(char *string, long int num, size_t len)
{
	while (num > 0)
	{
		string[len--] = 48 + (num % 10);
		num = num / 10;
	}
	return (string);
}

char	*ft_itoa(int n)
{
	char		*string;
	size_t		len;
	long int	num;

	num = n;
	len = get_len(num);
	string = malloc(sizeof(char) * (len + 1));
	if (!string)
		return (NULL);
	string[len--] = '\0';
	if (num == 0)
	{
		string[0] = '0';
		return (string);
	}
	if (num < 0)
	{
		string[0] = '-';
		num = num * -1;
	}
	string = make_string(string, num, len);
	return (string);
}
