/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:21:26 by minkim            #+#    #+#             */
/*   Updated: 2022/10/15 13:17:31 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
{
    std::cout << "DiamondTrap default constructor called" << std::endl;
    this->name = "default";
    ClapTrap::name = name + "_clap_name";
    this->energy_points = SCAVTRAP_ENERGY_POINTS;
}

DiamondTrap::DiamondTrap(std::string name)// : ClapTrap(), ScavTrap(), FragTrap()
{
	std::cout << "DiamondTrap constructor called" << std::endl;
	this->name = name;
	ClapTrap::name = name + "_clap_name";
    this->energy_points = SCAVTRAP_ENERGY_POINTS;
}

DiamondTrap::DiamondTrap(const DiamondTrap& dt)// : ClapTrap(dt), ScavTrap(dt), FragTrap(dt), name(dt.name)
{
    std::cout << "DiamondTrap copy constructor called" << std::endl;
    this->name = dt.name;
    this->hit_points = dt.hit_points;
    this->energy_points = dt.energy_points;
    this->attack_damage = dt.attack_damage;
}

DiamondTrap &DiamondTrap::operator=(const DiamondTrap &dt)
{
    std::cout << "DiamondTrap copy assignment operator called" << std::endl;
    this->name = dt.name;
    this->hit_points = dt.hit_points;
    this->energy_points = dt.energy_points;
    this->attack_damage = dt.attack_damage;
    return (*this);
}

DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap destructor called" << std::endl;
}

void DiamondTrap::whoAmI(void)
{
    std::cout << "DiamondTrap name : " << name << std::endl;
    std::cout << "ClapTrap name : " << ClapTrap::name << std::endl;
}

void DiamondTrap::printStatus(void)
{
	std::cout	<< "This DiamondTrap name is " << this->name << "\n"
				<< "HitPoint is " << hit_points << "\n"
				<< "EnergyPoint is " << energy_points << "\n"
				<< "AttackDamage is " << attack_damage << std::endl;
}