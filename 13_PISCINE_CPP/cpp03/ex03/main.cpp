/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:55:32 by minkim            #+#    #+#             */
/*   Updated: 2022/10/15 13:21:12 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main(void)
{
	DiamondTrap a("A");
	DiamondTrap b("B");

	// DiamondTrap b(a);
	// DiamondTrap c;

	// c = a;
	// a.printStatus();
	// b.printStatus();
	// c.printStatus();
    
	a.attack("B");
	b.takeDamage(30);
	a.attack("B");
	b.takeDamage(30);
	a.attack("B");
	b.takeDamage(30);
	b.beRepaired(20);
	a.attack("B");
	b.takeDamage(30);
	b.beRepaired(10);
	a.whoAmI();
	a.printStatus();

    return 0;
}
