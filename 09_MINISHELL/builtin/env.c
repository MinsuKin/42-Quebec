/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:25:21 by minkim            #+#    #+#             */
/*   Updated: 2022/07/04 12:42:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_env_check(char *env)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (env[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

void    print_env(char **env)
{
    while (*env)
    {
        if (ft_env_check(*env))
            printf("%s\n", *env);
        env++;
    }
}

int env_exe(char *line)
{
    char **env;

    env = ft_copy_env(envp);
    line += 3;
    if (*line && !ft_isspace(*line))
		return print_and_return("Error: command not found\n");
    while (ft_isspace(*line))
        line++;
    if (*line && !ft_isspace(*line))
		printf("Error: builtin env does not take options or arguments\n");
    else
        print_env(env); // if there is VAR which does not have value, do not print
    ft_env_free(env);
    return (0);
}