/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:55:32 by minkim            #+#    #+#             */
/*   Updated: 2022/10/14 20:16:59 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

int main(void)
{
	FragTrap a("A");
	FragTrap b("B");
    
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
	a.highFivesGuys();

    return 0;
}
