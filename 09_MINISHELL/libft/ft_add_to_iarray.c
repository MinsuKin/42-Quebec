/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_iarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:39:50 by tgarriss          #+#    #+#             */
/*   Updated: 2022/07/10 15:48:37 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int	*add_to_existing(int *array, int *size, int insert)
{
	int	*new_array;
	int	i;

	new_array = ft_calloc(*size + 1, sizeof(int));
	i = -1;
	while (++i < *size)
		new_array[i] = array[i];
	new_array[i] = insert;
	(*size)++;
	free(array);
	return (new_array);
}

t_iarray	*ft_add_to_iarray(t_iarray *array, int insert)
{
	int	*new_array;

	if (insert > INT_MAX || insert < INT_MIN)
		ft_error("Not within INT values.", __FILE__, __func__, __LINE__);
	new_array = NULL;
	if (array)
		array->array = add_to_existing(array->array, &array->size, insert);
	else
	{
		array = ft_calloc(1, sizeof(t_iarray));
		new_array = ft_calloc(1, sizeof(int));
		new_array[0] = insert;
		array->array = new_array;
		array->size = 1;
	}
	return (array);
}
