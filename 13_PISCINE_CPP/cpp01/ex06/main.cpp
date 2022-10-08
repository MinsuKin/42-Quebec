/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 13:51:11 by minkim            #+#    #+#             */
/*   Updated: 2022/10/08 17:22:32 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main(int ac, char const *av[])
{
	if (ac != 2)
	{
		std::cout << "Error" << std::endl;
		return 0;
	}

	Harl h;

	h.complain(av[1]);
	return 0;
}

