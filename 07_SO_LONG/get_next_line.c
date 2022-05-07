/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 13:35:48 by minkim            #+#    #+#             */
/*   Updated: 2022/05/06 17:12:40 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_free(char *str)
{
	free(str);
	return (NULL);
}

static char	*ft_return_line(char **buf)
{
	char	*address_n;
	char	*temp;
	char	*line;

	if (!buf || !*buf)
		return (NULL);
	if (ft_strlen(*buf) == 0)
		return (ft_free(*buf));
	address_n = ft_strchr(*buf, '\n');
	if (!address_n)
	{
		line = *buf;
		*buf = 0;
		return (line);
	}
	line = ft_strndup(*buf, address_n - *buf + 1);
	if (!line)
		return (NULL);
	temp = ft_strndup(address_n + 1, ft_strlen(address_n + 1));
	if (!temp)
		return (NULL);
	free(*buf);
	*buf = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	char		buffer[BUFFER_SIZE + 1];
	size_t		size;

	if (read(fd, buffer, 0) == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strchr(save[fd], '\n'))
		return (ft_return_line(&save[fd]));
	size = read(fd, buffer, BUFFER_SIZE);
	while (size > 0)
	{
		buffer[size] = 0;
		save[fd] = ft_strjoin(save[fd], buffer);
		if (ft_strchr(save[fd], '\n'))
			return (ft_return_line(&save[fd]));
		size = read(fd, buffer, BUFFER_SIZE);
	}
	return (ft_return_line(&save[fd]));
}
