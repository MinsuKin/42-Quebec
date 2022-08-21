/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:06:45 by tgarriss          #+#    #+#             */
/*   Updated: 2022/03/27 14:08:50 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// function that frees a variable number of addresses
// it might be safer to typecast every pointer to (void *)
void	ft_free(int argnum, ...)
{
	int		i;
	va_list	ap;

	i = -1;
	va_start(ap, argnum);
	while (++i < argnum)
		free(va_arg(ap, void *));
	va_end(ap);
}
