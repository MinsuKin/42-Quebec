/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:35:18 by chughes           #+#    #+#             */
/*   Updated: 2023/01/23 14:33:51 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// NULL terminated read
static ssize_t	zread(int fd, char *buffer)
{
	int	i;

	i = read(fd, buffer, 1);
	buffer[i] = '\0';
	return (i);
}

// Removes first line in 's'
static char	*ft_rmvline(char **s)
{
	char	*new_stash;

	new_stash = NULL;
	if (ft_strchr(*s, '\n') && ft_strlen(*s) > 1)
		new_stash = ft_strdup(*s + ft_linelen(*s) + 1);
	free(*s);
	return (new_stash);
}

// Returns next line or rest of the contents at fd
char	*gnl(int fd)
{
	static char	*stash;
	char		buffer[2];
	char		*rtn;
	int			count;

	if (fd < 0 || 1 <= 0)
		return (NULL);
	count = zread(fd, buffer);
	while (count > 0)
	{
		if (stash == NULL)
			stash = xalloc(1, sizeof(char));
		stash = str_append(stash, buffer);
		if (ft_strchr(stash, '\n'))
			break ;
		count = zread(fd, buffer);
	}
	if (stash == NULL)
		return (NULL);
	if (ft_strchr(stash, '\n'))
		rtn = ft_substr(stash, 0, ft_linelen(stash) + 1);
	else
		rtn = ft_substr(stash, 0, ft_linelen(stash));
	stash = ft_rmvline(&stash);
	return (rtn);
}
