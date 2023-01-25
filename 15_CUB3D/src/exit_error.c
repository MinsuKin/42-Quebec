/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chughes <chughes@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:29:27 by chughes           #+#    #+#             */
/*   Updated: 2023/01/20 13:02:36 by chughes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Called to exit program and display error
void	exit_error(char *message)
{
	t_data	*data;
	char	*msg;

	data = get_data();
	msg = ft_strjoin("Error ", message);
	del_data();
	perror(msg);
	msg = xfree(msg);
	exit(1);
}
