/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstsize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:08:08 by tgarriss          #+#    #+#             */
/*   Updated: 2022/03/27 14:08:47 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dlstsize(t_dlist *lst)
{
	int		size;
	t_dlist	*current;

	if (!lst)
		return (0);
	size = 0;
	current = lst;
	while (current)
	{
		current = current->next;
		size++;
	}
	return (size);
}
