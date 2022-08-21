/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:09:04 by tgarriss          #+#    #+#             */
/*   Updated: 2022/03/27 14:09:07 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **list, t_dlist *new)
{
	t_dlist	*last;

	if (*list == NULL)
	{
		*list = new;
		return ;
	}
	last = ft_dlstlast(*list);
	last->next = new;
	new->prev = last;
}
