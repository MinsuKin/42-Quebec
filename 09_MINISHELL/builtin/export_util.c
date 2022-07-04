/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:58:58 by minkim            #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_strcmp(const char *s1, const char *s2)
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
	return (1);
}

void    ft_swap(char **env)
{
    char **envp;
    char **next;
    char *tmp;

    envp = env;
    next = env + 1;
    while (*next)
    {
        if (ft_strcmp(*env, *next) > 0)
        {
            tmp = *next;
            *next = *env;
            *env = tmp;
            env = envp;
            next = env + 1;
        }
        else
        {
            env++;
            next = env + 1;
        }
    }
}

void    ft_export_quotes(char *env)
{
	int i;
	int	flag;

	flag = 0;
	i = 0;
    write(1, "declare -x ", 11);
    while (env[i])
    {
        write(1, &env[i], 1);
        if (env[i] == '=')
		{
            write(1, "\"", 1);
			flag = 1;
		}
        i++;
    }
	if (flag == 1)
    	write(1, "\"", 1);
    write(1, "\n", 1);
}

void    print_export(char **env)
{
    ft_swap(env); // sort
    while (*env)
    {
        ft_export_quotes(*env);
        env++;
    }
}

char	**ft_export_add(char **s, char *add)
{
	size_t	i;
	size_t	ary;
	char	**split;

	ary = ft_cnt_ary(s);
	split = (char **)malloc(sizeof(char *) * (ary + 2));
	if (!split)
		return (0);
	i = -1;
	while (++i < ary)
		split[i] = ft_strdup(s[i]);
	split[i] = ft_strdup(add);
	split[i + 1] = NULL;
	return (split);
}
