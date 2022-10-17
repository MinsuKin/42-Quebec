/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:51:42 by minkim            #+#    #+#             */
/*   Updated: 2022/10/17 17:23:48 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"
#include "ICharacter.hpp"

Cure::Cure()
{
    this->type = "cure";
}

Cure::Cure(const Cure& obj)
{
    this->type = obj.getType();
}

Cure::~Cure()
{
}

Cure& Cure::operator=(const Cure& obj)
{
    this->type = obj.getType();
    return (*this);
}

AMateria* Cure::clone() const
{
    return new Cure();
}

void Cure::use(ICharacter& target)
{
    std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}
