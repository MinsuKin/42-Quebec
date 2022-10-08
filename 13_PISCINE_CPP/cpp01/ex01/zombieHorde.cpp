/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 20:30:30 by minkim            #+#    #+#             */
/*   Updated: 2022/10/08 15:09:13 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name)
{
    Zombie *zbhd = new Zombie[N];
    
    for (int i = 0; i < N; i++)
    {
        std::stringstream ssInt;
        ssInt << i;
        zbhd[i].setName(name + ssInt.str());
    }
    return (zbhd);
}