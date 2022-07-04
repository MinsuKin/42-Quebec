/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:13:31 by minkim            #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s2 || !s1)
		ft_error("invalid string pointers", __FILE__, __func__, __LINE__);
	while (s1[i] && s2[i])
	{
		if (s1[i] == '=' && s2[i] == '=')
			return (1);
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
    if (s1[i])
    {
        if (s1[i] == '=')
            return (1);
        return (0);
    }
    if (s2[i])
        return (0);
	return (1);
}

int	ft_unset_check(char *line)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_unset_strcmp(envp[i], line))
			return (i);
		i++;
	}
    return (0);
}

void    ft_unset(char *line)
{
	int		i;
	char	*tmp;

	i = ft_unset_check(line);
    if (i != 0)
    {
		while (envp[i + 1])
        {
            tmp = envp[i];
            envp[i] = envp[i + 1];
            envp[i + 1] = tmp;
            i++;
        }
		free(envp[i]);
		envp[i] = NULL;
    }
}

int unset_exe(char *line)
{
    line += 5;
    if (*line && !ft_isspace(*line))
		return print_and_return("Error: command not found\n");
    while (ft_isspace(*line))
        line++;
    if (*line)// && (ft_isalpha(*line) || *line == '_')) // 유효하지 않으면 에러 리턴
    {
        if (ft_isalpha(*line) || *line == '_') // valid
            ft_unset(line);
        else
            printf("Error: not a valid identifier\n");
    }
    return (0);
}
