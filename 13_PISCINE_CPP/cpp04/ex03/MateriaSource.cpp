/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:41:34 by minkim            #+#    #+#             */
/*   Updated: 2022/10/17 17:41:05 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"
#include "AMateria.hpp"

MateriaSource::MateriaSource()
{
	for (size_t i = 0; i < 4; i++)
	{
		this->slot[i] = NULL;
	}
}

MateriaSource::MateriaSource(const MateriaSource& obj)
{
    for (size_t i = 0; i < 4; i++)
    {
        if (obj.slot[i] != NULL)
        {
            this->slot[i] = obj.slot[i]->clone();
        }
    }
}

MateriaSource::~MateriaSource()
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

MateriaSource& MateriaSource::operator=(const MateriaSource& obj)
{
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

void MateriaSource::learnMateria(AMateria* m)
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

AMateria *MateriaSource::createMateria(std::string const &type)
{
	for (size_t i = 0; i < 4; i++)
	{
		if (slot[i] != NULL && slot[i]->getType() == type)
		{
			return (slot[i]->clone());
		}
	}
    return 0;
}
