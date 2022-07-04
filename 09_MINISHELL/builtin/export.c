/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:19:54 by minkim            #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_export_check(char *line)
{
	char	**env;

	env = envp;
	while (*env)
	{
		if (ft_export_strcmp(*env, line))
			return (*env);
		env++;
	}
	return (NULL);
}

int	ft_export_val_exist(char *line)
{
	while (*line)
	{
		if (*line == '=') // value exists
			return (1);
		line++;
	}
	return (0); // value not exists
}

void    ft_export_val_change(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		if (ft_export_strcmp(envp[i], line))
			break ;
		i++;
	}
	tmp = envp[i];
	envp[i] = ft_strdup(line);
	free(tmp);
	tmp = NULL;
}

void    ft_export_args(char *line)
{
    char	**env;

    if (ft_isalpha(*line) || *line == '_')
    {
		if (ft_export_check(line) && ft_export_val_exist(line)) // key exists in env && it has value too ('=')
			ft_export_val_change(line); // change (key=value)
		else // add new key and value
		{
			env = ft_export_add(envp, line);
			ft_env_free(envp);
			envp = ft_copy_env(env);
			ft_env_free(env);
		}
    }
    else
        printf("Error: not a valid identifier\n");
}

int export_exe(char *line)
{
    char **env;

    line += 6;
    if (*line && !ft_isspace(*line))
		return print_and_return("Error: command not found\n");
    while (ft_isspace(*line))
        line++;
    if (*line) // if there is argument
        ft_export_args(line); //add or change
    else // no args
    {
        env = ft_copy_env(envp);
        print_export(env); // still prints even if there is VAR which does not have value
        ft_env_free(env);
    }
    return (0);
}
