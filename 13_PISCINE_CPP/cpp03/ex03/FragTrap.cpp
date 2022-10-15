/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 19:56:59 by minkim            #+#    #+#             */
/*   Updated: 2022/10/14 20:45:30 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap()
{
    std::cout << "FragTrap default constructor called" << std::endl;
    name = "default";
    hit_points = 100;
    energy_points = 100;
    attack_damage = 30;
}

FragTrap::FragTrap(std::string name)
{
    std::cout << "FragTrap constructor called" << std::endl;
    this->name = name;
    hit_points = 100;
    energy_points = 100;
    attack_damage = 30;
}

FragTrap::FragTrap(const FragTrap& ft)
{
    std::cout << "FragTrap copy constructor called" << std::endl;
    this->name = ft.name;
    this->hit_points = ft.hit_points;
    this->energy_points = ft.energy_points;
    this->attack_damage = ft.attack_damage;
}

FragTrap &FragTrap::operator=(const FragTrap &ft)
{
    std::cout << "FragTrap copy assignment operator called" << std::endl;
    this->name = ft.name;
    this->hit_points = ft.hit_points;
    this->energy_points = ft.energy_points;
    this->attack_damage = ft.attack_damage;
    return (*this);
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap destructor called" << std::endl;
}

void FragTrap::highFivesGuys(void)
{
    if (hit_points == 0)
    {
        std::cout << "FragTrap " << name << " is already dead!" << std::endl;
    }
    else
    {
        std::cout << "FragTrap " << name << " : " << "Give me a high five!" << std::endl;
    }
}
