/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:55:32 by minkim            #+#    #+#             */
/*   Updated: 2022/10/14 20:13:22 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main(void)
{
	ScavTrap a("A");
	ScavTrap b("B");
    
	a.attack("B");
	b.takeDamage(20);
	a.attack("B");
	b.takeDamage(20);
	a.attack("B");
	b.takeDamage(20);
	a.attack("B");
	b.takeDamage(20);
	a.attack("B");
	b.takeDamage(20);
	b.beRepaired(100);
	a.guardGate();

    return 0;
}
