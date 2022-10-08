/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:30:38 by minkim            #+#    #+#             */
/*   Updated: 2022/10/06 11:47:45 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Zombie.hpp"

int	main(void)
{
    Zombie *horde;

    horde = zombieHorde(10, "Zombie");
	for (int i = 0; i < 10; i++)
	{
		horde[i].announce();
	}
	delete[] horde;
    return (0);
}