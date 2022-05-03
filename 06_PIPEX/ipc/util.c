/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:03:44 by minkim            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/05/02 20:40:47 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>
# include <fcntl.h>
=======
/*   Updated: 2022/04/30 18:58:05 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
>>>>>>> 4395dbbc1e84b21a88b2f4d0784c16546c42389a

static size_t	ft_cnt_ary(const char *s, char c)
{
	size_t	cnt;
	size_t	flag;

	cnt = 0;
	flag = 0;
	while (*s != '\0')
	{
		if (*s != c && flag == 0)
		{
			flag = 1;
			cnt++;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (cnt);
}

static size_t	ft_cnt_wrd(char const *s, char c)
{
	size_t	cnt;

	cnt = 0;
	while (*s != '\0' && *s != c)
	{
		cnt++;
		s++;
	}
	return (cnt);
}

static char	*ft_strndup(const char *s1, size_t n)
{
	char	*s2;
	char	*tmp;

	s2 = (char *)malloc(sizeof(char) * (n + 1));
	if (!s2)
		return (0);
	tmp = s2;
	while (n-- > 0)
		*tmp++ = *s1++;
	*tmp = '\0';
	return (s2);
}

static void	ft_free(char **s, int i)
{
	while (i--)
	{
		free(s[i]);
		s[i] = NULL;
	}
	free(s);
	s = NULL;
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	wrd;
	size_t	ary;
	char	**split;

	ary = ft_cnt_ary(s, c);
	split = (char **)malloc(sizeof(char *) * (ary + 1));
	if (!split)
		return (0);
	i = -1;
	while (++i < ary)
	{
		while (*s != '\0' && *s == c)
			s++;
		wrd = ft_cnt_wrd(s, c);
		split[i] = ft_strndup(s, wrd);
		if (!split[i])
		{
			ft_free(split, i - 1);
			return (0);
		}
		s += wrd;
	}
	split[i] = NULL;
	return (split);
}
<<<<<<< HEAD

int main()
{
	char **ch;

	ch = ft_split("ls -a -l", ' ');
	int i = 0;
	while (ch[i])
	{
		printf("%s\n", ch[i]);
		i++;
	}
	printf("%s\n", ch[i]);
	printf("%s\n", ch[i+10]);
}
=======
>>>>>>> 4395dbbc1e84b21a88b2f4d0784c16546c42389a
