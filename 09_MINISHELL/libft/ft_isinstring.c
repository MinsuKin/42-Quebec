/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:08:02 by tgarriss          #+#    #+#             */
/*   Updated: 2022/08/19 15:08:53 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	ft_isinstring(char *string, char c)
{
	int	i;

	i = -1;
	while (string[++i])
		if (string[i] == c)
			return (1);
	return (0);
}
