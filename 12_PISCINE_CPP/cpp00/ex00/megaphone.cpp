/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 17:40:34 by minkim            #+#    #+#             */
/*   Updated: 2022/10/05 16:08:25 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int	main(int ac, char **av)
{
	if (ac == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	}
	else
	{
		for (int i = 1; i < ac; i++)
		{
			for (int j = 0; av[i][j] != 0; j++)
			{
				std::cout << static_cast<char>(std::toupper(av[i][j]));
			}
		}
		std::cout << std::endl;
	}
}