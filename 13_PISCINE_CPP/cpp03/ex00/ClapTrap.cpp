/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:55:27 by minkim            #+#    #+#             */
/*   Updated: 2022/10/13 17:39:34 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void)
{
    std::cout << "Default constructor called" << std::endl;
    name = "default";
    hit_points = 10;
    energy_points = 10;
    attack_damage = 0;
}

ClapTrap::ClapTrap(std::string name)
{
    std::cout << "Constructor called" << std::endl;
    this->name = name;
    hit_points = 10;
    energy_points = 10;
    attack_damage = 0;
}

ClapTrap::ClapTrap(const ClapTrap& ct)
{
    std::cout << "Copy constructor called" << std::endl;
    this->name = ct.name;
    this->hit_points = ct.hit_points;
    this->energy_points = ct.energy_points;
    this->attack_damage = ct.attack_damage;
}

ClapTrap::~ClapTrap()
{
    std::cout << "Destructor called" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &ct)
{
    std::cout << "Copy assignment operator called" << std::endl;
    this->name = ct.name;
    this->hit_points = ct.hit_points;
    this->energy_points = ct.energy_points;
    this->attack_damage = ct.attack_damage;
    return (*this);
}

void ClapTrap::attack(const std::string& target)
{
    if (hit_points == 0)
    {
        std::cout << "ClapTrap " << name << " is already dead, cannot attack!" << std::endl;
    }
    else if (energy_points == 0)
    {
        std::cout << "ClapTrap " << name << " has no energy points!" << std::endl;
    }
    else
        std::cout << "ClapTrap " << name << " attacks " << target << " causing " << attack_damage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (hit_points == 0)
    {
        std::cout << "ClapTrap " << name << " is already dead!" << std::endl;
    }
    else
    {
        if (hit_points <= amount)
        {
            hit_points = 0;
            std::cout << "ClapTrap " << name << " lost all hit points!" << std::endl;
            std::cout << "ClapTrap " << name << " died!" << std::endl;
        }
        else
        {
            std::cout << "ClapTrap " << name << " lost " << amount << " hit points!" << std::endl;
            hit_points -= amount;
        }
    }
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (hit_points == 0)
    {
        std::cout << "ClapTrap " << name << " is already dead, cannot repair!" << std::endl;
    }
    else if (energy_points == 0)
    {
        std::cout << "ClapTrap " << name << " has no energy points!" << std::endl;
    }
    else
    {
        std::cout << "ClapTrap " << name << " repaired " << amount << " hit points!" << std::endl;
        energy_points--;
        hit_points += amount;
    }
}
