/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:50:39 by minkim            #+#    #+#             */
/*   Updated: 2021/02/22 16:37:35 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int i;
	unsigned int j;
	unsigned int y;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	if (i > size)
		y = size;
	else if (i < size)
		return (0);
	else
		y = i;
	while (src[j] && i < size - 1)
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	j = 0;
	while (src[j])
		j++;
	return (y + j);
}
