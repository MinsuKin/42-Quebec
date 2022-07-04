/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 13:34:37 by tgarriss          #+#    #+#             */
/*   Updated: 2021/09/21 14:26:28 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Initialize a counter. As long as the node has a non-NULL next value, 
// increment the pointer. The first loop will stop without counting the last
// node. Add an if statement at the end to account for that.
int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*temp_list;

	if (!lst)
		return (0);
	size = 0;
	temp_list = lst;
	while (temp_list->next)
	{
		temp_list = temp_list->next;
		size++;
	}
	if (!(temp_list->next))
		size++;
	return (size);
}
