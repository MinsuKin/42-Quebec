/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_carray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:06:26 by tgarriss          #+#    #+#             */
/*   Updated: 2022/03/27 14:08:50 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_carray(char **array)
{
	int	i;

	i = -1;
	if (!(array))
		exit(EXIT_FAILURE);
	while (array[++i])
		if (array[i])
			free(array[i]);
	free(array);
}
