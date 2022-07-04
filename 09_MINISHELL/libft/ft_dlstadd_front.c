/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:08:41 by tgarriss          #+#    #+#             */
/*   Updated: 2022/03/27 14:08:43 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Do a NULL-check
// Set the new node's next value to the pointer pointing at the beginning
// of the list. Set the pointer pointing at the beginning of the list to
// the new node.
void	ft_dlstadd_front(t_dlist **list, t_dlist *new)
{
	if (!list || !new)
		return ;
	new->next = *list;
	*list = new;
}
