/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:51:58 by minkim            #+#    #+#             */
/*   Updated: 2022/10/17 17:24:09 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Ice.hpp"
#include "ICharacter.hpp"

Ice::Ice()
{
    this->type = "ice";
}

Ice::Ice(const Ice& obj)
{
    this->type = obj.getType();
}

Ice::~Ice()
{
}

Ice& Ice::operator=(const Ice& obj)
{
    this->type = obj.getType();
    return (*this);
}

AMateria* Ice::clone() const
{
    return new Ice();
}

void Ice::use(ICharacter& target)
{
    std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
