/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:14:42 by minkim            #+#    #+#             */
/*   Updated: 2021/02/19 12:16:30 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int i;
	unsigned int j;

	i = 0;
	while (i < size && dest[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[size - 1] = '\0';
	j = 0;
	while (src[j])
		j++;
	return (j);
}
