/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:38:12 by minkim            #+#    #+#             */
/*   Updated: 2021/02/17 14:12:28 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

char	*ft_strlowcase(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + 32;
		i++;
	}
	return (str);
}

int		main(void)
{
	// char  i[] = "minsu";
	// char *u = ft_strupcase("minsu");
	// printf("%s\n", ft_strupcase(u));
	char text1[] = "asdfasdf"; //소문자만
	printf("%s\n", ft_strlowcase(text1));
	char text2[] = "ASDFasdf"; // 대 소문자
	printf("%s\n", ft_strlowcase(text2));
	char text3[] = "ASSDDGBZAQ";//대문자만
	printf("%s\n", ft_strlowcase(text3));
	char text4[] = "a.b.C.d";//다른문자 섞임
	printf("%s\n", ft_strlowcase(text4));
	char text5[] = "";//비어있는 문자열
	printf("%s\n", ft_strlowcase(text5));
	char text6[] = "ac bbBa";//공백 섞임
	printf("%s\n", ft_strlowcase(text6));
	return (0);
}
