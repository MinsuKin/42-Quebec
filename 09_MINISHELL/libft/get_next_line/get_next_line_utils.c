/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 09:19:21 by tgarriss          #+#    #+#             */
/*   Updated: 2021/10/23 10:29:44 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	gnl_strlen(char *string)
{
	size_t	len;

	len = 0;
	while (string[len])
		len++;
	return (len);
}

char	*gnl_strchr(char *src, int c)
{
	size_t	i;

	i = 0;
	if (!src)
		return (NULL);
	if (c == '\0')
		return ((char *) &src[gnl_strlen(src)]);
	while (src[i])
	{
		if (src[i] == (char) c)
			return ((char *) &src[i]);
		i++;
	}
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1)
	{
		s1 = (char *) malloc(sizeof(char) * 1);
		*s1 = '\0';
	}
	str = (char *) malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}

char	*gnl_cropline(char *src)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\n' && src[i])
		i++;
	line = (char *) malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (src[i] != '\n' && src[i])
	{
		line[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*gnl_cropsave(char *src)
{
	size_t	i;
	size_t	j;
	char	*save;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\n' && src[i])
		i++;
	if (src[i] == '\0')
	{
		free(src);
		return (NULL);
	}
	save = (char *) malloc(sizeof(char) * (gnl_strlen(src) - i + 1));
	if (!save)
		return (NULL);
	i++;
	j = 0;
	while (src[i])
		save[j++] = src[i++];
	save[j] = '\0';
	free(src);
	return (save);
}
