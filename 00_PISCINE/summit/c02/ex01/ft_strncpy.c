/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:14:42 by minkim            #+#    #+#             */
/*   Updated: 2021/02/17 18:43:02 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned long i;
	unsigned long j;

	i = 0;
	j = 0;
	while (src[j])
		j++;
	while (i < n)
	{
		if (i >= j)
			dest[i] = '\0';
		else
			dest[i] = src[i];
		i++;
	}
	return (dest);
}
