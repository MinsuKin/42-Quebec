/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:51:19 by minkim            #+#    #+#             */
/*   Updated: 2022/09/06 11:19:34 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_cd_strdup(const char *s1)
{
	char	*s2;
	char	*tmp;
	int		n;

	n = 0;
	while (s1[n] && s1[n] != ' ')
		n++;
	s2 = (char *)malloc(sizeof(char) * (n + 1));
	if (!s2)
		return (0);
	tmp = s2;
	while (n-- > 0)
		*tmp++ = *s1++;
	*tmp = '\0';
	return (s2);
}

int	print_and_return(char *str)
{
	printf("%s", str);
	return (1);
}

int	print_and_return2(void)
{
	perror("Error");
	*f_exit_code() = 1;
	return (1);
}

int	print_and_return3(char *str)
{
	printf("%s", str);
	*f_exit_code() = 1;
	return (1);
}
