/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgarriss <tgarriss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:08:01 by tgarriss          #+#    #+#             */
/*   Updated: 2022/03/28 09:29:53 by tgarriss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error(char *msg, char *file, const char *function, int line)
{
	ft_printf(STDERR_FILENO, "ERROR: %s:%d:%s()\n", file, line, function);
	ft_printf(STDERR_FILENO, "%s\n", msg);
	exit(EXIT_FAILURE);
}
