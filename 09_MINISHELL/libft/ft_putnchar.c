/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:16:23 by tgarriss          #+#    #+#             */
/*   Updated: 2021/11/25 09:17:19 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnchar(char c, int count)
{
	int	bytes_printed;
	int	i;

	bytes_printed = 0;
	i = -1;
	while (++i < count)
		bytes_printed += write(1, &c, 1);
	return (bytes_printed);
}
