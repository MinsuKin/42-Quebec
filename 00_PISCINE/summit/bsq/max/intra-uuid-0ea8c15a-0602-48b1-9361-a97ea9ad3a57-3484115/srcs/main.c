/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msauvage <msauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 10:14:09 by msauvage          #+#    #+#             */
/*   Updated: 2021/03/04 08:46:35 by msauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_header.h>
#include <stdio.h>

void	ft_process_file(t_map mymap, char *filename)
{
	char	*str;

	if (!(mymap.map =
	ft_check_map(ft_get_lines_from_grid(filename), mymap.row)))
	{
		ft_error("map error\n");
		return ;
	}
	str = mymap.map[0];
	while (*str)
		str++;
	mymap.fill = *(str - 1);
	mymap.obs = *(str - 2);
	mymap.empty = *(str - 3);
	ft_do_square(mymap);
}

void	ft_calcs(int file, char *filename)
{
	t_map		mymap;
	char		c;
	char		temp;
	char		prev_c;

	c = 0;
	prev_c = 0;
	while (c != '\n' && read(file, &c, 1))
		;
	mymap.col = 0;
	mymap.row = 1;
	while (read(file, &c, 1))
	{
		if (mymap.row == 1 && c != '\n')
			mymap.col++;
		if (c == '\n')
			mymap.row++;
		prev_c = temp;
		temp = c;
	}
	close(file);
	(c == '\n' && prev_c != '\n' && prev_c != '\0') ?
	ft_process_file(mymap, filename)
	: ft_error("map error\n");
}

void	ft_parse_file(char *filename)
{
	int			file;

	if ((file = open(filename, O_RDONLY)) < 0)
		ft_error("map error\n");
	else
		ft_calcs(file, filename);
}

int		main(int ac, char **av)
{
	int i;

	i = 1;
	if (ac == 1)
		ft_parse_file(ft_file_missing());
	while (i < ac)
	{
		ft_parse_file(av[i]);
		if (i < ac - 1)
			ft_putchar('\n');
		i++;
	}
	return (0);
}
