/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:30:13 by minkim            #+#    #+#             */
/*   Updated: 2022/07/18 14:07:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_cnt_ary(char **s)
{
	size_t	cnt;

	cnt = 0;
	while (*s != 0)
	{
		cnt++;
		s++;
	}
	return (cnt);
}

void	ft_env_free(char **s)
{
	int	i;
	int	len;

	i = 0;
	len = ft_cnt_ary(s);
	while (i < len)
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
	s = NULL;
}

char	**ft_copy_env(char **s)
{
	size_t	i;
	size_t	ary;
	char	**split;

	ary = ft_cnt_ary(s);
	split = (char **)malloc(sizeof(char *) * (ary + 1));
	if (!split)
		return (0);
	i = -1;
	while (++i < ary)
		split[i] = ft_strdup(s[i]);
	split[i] = NULL;
	return (split);
}
