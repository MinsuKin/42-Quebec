/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_to_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msauvage <msauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 11:01:40 by msauvage          #+#    #+#             */
/*   Updated: 2021/03/04 07:28:38 by msauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_header.h>

char			*ft_file_missing(void)
{
	char	buf;
	int		file;

	if ((file = open("tempmap", O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
		return (NULL);
	while (read(STDIN_FILENO, &buf, 1))
	{
		write(file, &buf, 1);
	}
	close(file);
	return ("tempmap");
}

char			*ft_file_to_str(char *path)
{
	char			currchar;
	char			*strs;
	unsigned int	nbchars;
	int				grid;
	int				i;

	if ((grid = open(path, O_RDONLY)) < 0)
		return (NULL);
	nbchars = 0;
	while (read(grid, &currchar, 1))
		nbchars++;
	if (!(strs = malloc(sizeof(char) * (nbchars + 1))))
		return (NULL);
	close(grid);
	grid = open(path, O_RDONLY);
	i = 0;
	while (read(grid, strs + i, 1))
		i++;
	close(grid);
	strs[nbchars] = '\0';
	return (strs);
}

char			**ft_get_lines_from_grid(char *path)
{
	char **lines;
	char *strs;

	if (!(strs = ft_file_to_str(path)))
		return (NULL);
	lines = ft_split(strs, "\n");
	free(strs);
	return (lines);
}

int				ft_row_len(char **lines)
{
	int i;

	i = 0;
	while (lines[i])
		i++;
	return (i);
}
