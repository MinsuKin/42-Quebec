/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:12:49 by tgarriss          #+#    #+#             */
/*   Updated: 2022/09/11 19:51:31 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*f_exit_code(void)
{
	static int	exit_code;

	return (&exit_code);
}

void	wait_child(pid_t pid)
{
	int	status;
	int	signo;

	while (waitpid(pid, &status, WNOHANG) != -1)
	{
		if (WIFSIGNALED(status))
		{
			signo = WTERMSIG(status);
			*f_exit_code() = 128 + signo;
		}
		else
			*f_exit_code() = WEXITSTATUS(status);
	}
	while (wait(&status) != -1)
		;
}

char	*ft_shlvl_strjoin(char const *s1, char const *s2)
{
	char			*newstr;
	unsigned int	bytes;
	int				i;
	int				j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (0);
	bytes = (ft_strlen(s1) + ft_strlen(s2) + 1);
	newstr = malloc(sizeof(char) * bytes);
	if (!newstr)
		return (0);
	while (s1 != NULL && s1[j])
		newstr[i++] = s1[j++];
	j = 0;
	while (s2 != NULL && s2[j])
		newstr[i++] = s2[j++];
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_level(void)
{
	char	**env;
	int		level;
	char	*s;

	env = g_envp;
	while (*env)
	{
		if (ft_export_strcmp(*env, "SHLVL="))
			break ;
		env++;
	}
	s = *env;
	while (*s && *s != '=')
		s++;
	level = ft_atoi(++s);
	if (level < 0)
		level = -1;
	return (ft_itoa(level + 1));
}

void	*ft_shlvl(void)
{
	char	*level;
	char	*join;
	char	**env;

	if (ft_export_check("SHLVL="))
	{
		level = ft_level();
		join = ft_shlvl_strjoin("SHLVL=", level);
		ft_export_val_change(join);
		free(level);
		free(join);
	}
	else
	{
		env = ft_export_add(g_envp, "SHLVL=1");
		ft_env_free(g_envp);
		g_envp = ft_copy_env(env);
		ft_env_free(env);
	}
	return (0);
}
