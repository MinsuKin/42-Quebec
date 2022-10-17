/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:05:49 by minkim            #+#    #+#             */
/*   Updated: 2022/10/17 17:41:24 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "AMateria.hpp"

Character::Character()
{
    this->name = "default";
	for (size_t i = 0; i < 4; i++)
	{
		this->slot[i] = NULL;
	}
}

Character::Character(std::string name)
{
    this->name = name;
	for (size_t i = 0; i < 4; i++)
	{
		this->slot[i] = NULL;
	}
}

Character::Character(const Character& obj)
{
    this->name = obj.getName();
    for (size_t i = 0; i < 4; i++)
    {
        if (obj.slot[i] != NULL)
        {
            this->slot[i] = obj.slot[i]->clone();
        }
    }
}

Character::~Character()
{
	for (size_t i = 0; i < 4; i++)
	{
        if (this->slot[i] != NULL)
        {
            delete this->slot[i];
            this->slot[i] = NULL;
        }
	}
}

Character& Character::operator=(const Character& obj)
{
    this->name = obj.getName();
    for (size_t i = 0; i < 4; i++)
    {
        if (this->slot[i] != NULL)
        {
            delete this->slot[i];
            this->slot[i] = NULL;
        }
        if (obj.slot[i] != NULL)
        {
            this->slot[i] = obj.slot[i]->clone();
        }
    }
    return (*this);
}

std::string const &Character::getName() const
{
    return this->name;
}

void Character::equip(AMateria* m)
{
    for (size_t i = 0; i < 4; i++)
    {
        if (this->slot[i] == NULL && m != NULL)
        {
            this->slot[i] = m;
            break;
        }
    }
}

void Character::unequip(int idx)
{
    if (idx >= 0 && idx < 4 && slot[idx] != NULL)
        this->slot[idx] = NULL;
}

void Character::use(int idx, ICharacter& target)
{
    if (idx >= 0 && idx < 4 && slot[idx] != NULL)
        this->slot[idx]->use(target);
}
