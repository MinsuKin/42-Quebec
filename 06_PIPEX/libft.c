/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:03:44 by minkim            #+#    #+#             */
/*   Updated: 2022/04/22 19:38:01 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

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

char	*ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (s2)
		ft_strcpy(s2, s1);
	return (s2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a1;
	unsigned char	*a2;

	i = 0;
	a1 = (unsigned char *)s1;
	a2 = (unsigned char *)s2;
	while (i < n && (a1[i] != '\0' || a2[i] != '\0'))
	{
		if (a1[i] != a2[i])
			return (a1[i] - a2[i]);
		i++;
	}
	return (0);
}

void	*ft_memset(void *b, int c, size_t len)
{
	char	*start;
	char	*end;

	start = (char *) b;
	end = start + len;
	while (start < end)
		*start++ = (unsigned char)c;
	return (b);
}
