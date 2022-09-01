/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_sarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 15:38:38 by tgarriss          #+#    #+#             */
/*   Updated: 2022/08/25 13:41:15 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	**add_to_front(char **array, char *insert)
{
	char	**new_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_array = ft_calloc(ft_get_array_length(array) + 2, sizeof(char *));
	new_array[j++] = ft_strdup(insert);
	if (array)
	{
		while (array[i])
		{
			new_array[j] = ft_strdup(array[i]);
			i++;
			j++;
		}
	}
	free(insert);
	return (new_array);
}

char	**add_to_back(char **array, char *insert)
{
	char	**new_array;
	int		i;

	i = 0;
	new_array = ft_calloc(ft_get_array_length(array) + 2, sizeof(char *));
	if (array)
	{
		while (array[i])
		{
			new_array[i] = ft_strdup(array[i]);
			i++;
		}
	}
	new_array[i] = ft_strdup(insert);
	free(insert);
	return (new_array);
}

// location: 0 (front), 1 (back)
char	**ft_add_to_sarray(char **array, char *insert, int location)
{
	char	**new_array;

	if (!insert)
		return (array);
	if (location == 0)
		new_array = add_to_front(array, insert);
	else if (location == 1)
		new_array = add_to_back(array, insert);
	else
		new_array = NULL;
	if (array)
		ft_free_carray(array);
	return (new_array);
}
