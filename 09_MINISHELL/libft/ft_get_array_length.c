/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_array_length.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 13:56:01 by tgarriss          #+#    #+#             */
/*   Updated: 2022/05/09 14:08:27 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_get_array_length(char **array)
{
    int length;

    length = 0;
    if (!array)
        return (length);
    while (array[length])
        length++;
    return (length);
}