/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:05:58 by tgarriss          #+#    #+#             */
/*   Updated: 2022/04/01 14:52:40 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isint(char *str)
{
	long	nbr;

	nbr = ft_atol(str);
	if (ft_isnbr(str) && nbr >= INT_MIN && nbr <= INT_MAX)
		return (1);
	return (0);
}
