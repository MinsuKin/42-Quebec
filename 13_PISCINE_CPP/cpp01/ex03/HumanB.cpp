/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:28:02 by minkim            #+#    #+#             */
/*   Updated: 2022/10/08 15:09:55 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name)
{
    this->name = name;
}

HumanB::~HumanB(void)
{
}

void HumanB::attack(void) const
{
    std::cout << name << " attacks with his " << wp->getType() << std::endl;
}

void HumanB::setWeapon(Weapon &wp)
{
    this->wp = &wp;
}
