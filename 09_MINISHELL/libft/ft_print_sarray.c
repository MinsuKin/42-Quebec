/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_sarray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 13:52:17 by tgarriss          #+#    #+#             */
/*   Updated: 2022/08/25 13:52:47 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

void	ft_print_sarray(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		ft_printf(STDOUT_FILENO, "%s\n", array[i]);
}
