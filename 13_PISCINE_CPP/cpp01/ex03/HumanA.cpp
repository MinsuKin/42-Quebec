/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:27:27 by minkim            #+#    #+#             */
/*   Updated: 2022/10/08 15:09:41 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

// Use initializer list to use REF in the class
HumanA::HumanA(std::string name, Weapon &wp) : name(name), wp(wp)
{
}

HumanA::~HumanA(void)
{
}

void HumanA::attack(void) const
{
    std::cout << name << " attacks with his " << wp.getType() << std::endl;
}