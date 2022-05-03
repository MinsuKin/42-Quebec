/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msauvage <msauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 08:17:58 by msauvage          #+#    #+#             */
/*   Updated: 2021/03/01 10:23:00 by msauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../bsq.h"

int	main(int argc, char **argv)
{
	char buf[BUF_SIZE + 1];
	int	fd;
	int ret;

	if (argc == 1)
		return (0);
	fd = open(argv[1], O_RDONLY);
	ret = read(fd, buf, BUF_SIZE);
	buf[ret] = '\0';
	printf("%s\n", buf);
	if (close(fd) == -1)
	{
		ft_putstr("close error\n");
		return (1);
	}
	return (0);
}
