/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:55:32 by minkim            #+#    #+#             */
/*   Updated: 2022/10/14 20:11:58 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main(void)
{
	ClapTrap a("A");
	ClapTrap b("B");
    
	a.attack("B");
	b.takeDamage(0);
	b.beRepaired(1);
	b.attack("A");
	a.takeDamage(0);
	a.beRepaired(1);

    return 0;
}
