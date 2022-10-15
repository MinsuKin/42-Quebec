/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 18:29:31 by minkim            #+#    #+#             */
/*   Updated: 2022/10/14 20:33:42 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
{
    std::cout << "ScavTrap default constructor called" << std::endl;
    name = "default";
    hit_points = 100;
    energy_points = 50;
    attack_damage = 20;
}

ScavTrap::ScavTrap(std::string name)
{
    std::cout << "ScavTrap constructor called" << std::endl;
    this->name = name;
    hit_points = 100;
    energy_points = 50;
    attack_damage = 20;
}

ScavTrap::ScavTrap(const ScavTrap& st)
{
    std::cout << "ScavTrap copy constructor called" << std::endl;
    this->name = st.name;
    this->hit_points = st.hit_points;
    this->energy_points = st.energy_points;
    this->attack_damage = st.attack_damage;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &st)
{
    std::cout << "ScavTrap copy assignment operator called" << std::endl;
    this->name = st.name;
    this->hit_points = st.hit_points;
    this->energy_points = st.energy_points;
    this->attack_damage = st.attack_damage;
    return (*this);
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap destructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
    if (hit_points == 0)
    {
        std::cout << "ScavTrap " << name << " is already dead, cannot attack!" << std::endl;
    }
    else if (energy_points == 0)
    {
        std::cout << "ScavTrap " << name << " has no energy points!" << std::endl;
    }
    else
        std::cout << "ScavTrap " << name << " attacks " << target << " causing " << attack_damage << " points of damage!" << std::endl;
}

void ScavTrap::guardGate()
{
    if (hit_points == 0)
    {
        std::cout << "ScavTrap " << name << " is already dead!" << std::endl;
    }
    else if (energy_points == 0)
    {
        std::cout << "ScavTrap " << name << " has no energy points!" << std::endl;
    }
    else
    {
        std::cout << "ScavTrap " << name << " is now in Gate keeper mode." << std::endl;
        energy_points--;
    }
}
