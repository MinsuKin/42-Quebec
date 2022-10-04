/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_util2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:19:54 by minkim            #+#    #+#             */
/*   Updated: 2022/09/16 20:38:23 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_export_check(char *line)
{
	char	**env;

	env = g_envp;
	while (*env)
	{
		if (ft_export_strcmp(*env, line))
			return (*env);
		env++;
	}
	return (NULL);
}

int	ft_export_valid(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '=')
			return (1);
		if (ft_isalnum(line[i]) == 0)
		{
			if (line[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);
}

int	ft_export_strcmp2(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s2 || !s1)
		ft_error("invalid string pointers", __FILE__, __func__, __LINE__);
	while (s1[i] && s1[i] != '=')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_export_check2(char *line)
{
	char	**env;

	env = g_envp;
	while (*env)
	{
		if (ft_export_strcmp2(*env, line))
			return (*env);
		env++;
	}
	return (NULL);
}

void	ft_export_args(char *line)
{
	char	**env;

	if (ft_export_valid(line) == 0)
	{
		*f_exit_code() = 1;
		printf("Error: not a valid identifier\n");
	}
	else if (ft_isalpha(*line) || *line == '_')
	{
		if (ft_export_check(line) && ft_export_val_exist(line))
			ft_export_val_change(line);
		else if (!ft_export_check2(line))
		{
			env = ft_export_add(g_envp, line);
			ft_env_free(g_envp);
			g_envp = ft_copy_env(env);
			ft_env_free(env);
		}
	}
	else
	{
		*f_exit_code() = 1;
		printf("Error: not a valid identifier\n");
	}
}
