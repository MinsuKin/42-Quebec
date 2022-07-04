/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:08:23 by tgarriss          #+#    #+#             */
/*   Updated: 2022/04/13 11:09:04 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// This could be modified to have an index of -1, which would make more sense.
t_dlist	*ft_dlstnew(int content)
{
	t_dlist	*list;

	list = malloc(sizeof(t_dlist));
	if (!list)
		return (NULL);
	list->prev = NULL;
	list->content = content;
	list->next = NULL;
	list->index = 0;
	return (list);
}
