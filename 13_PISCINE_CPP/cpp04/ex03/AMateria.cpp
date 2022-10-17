/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:02:42 by minkim            #+#    #+#             */
/*   Updated: 2022/10/17 16:15:41 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria()
{
    this->type = "default";
}

AMateria::AMateria(std::string const &type)
{
    this->type = type;
}

AMateria::AMateria(const AMateria& obj)
{
    this->type = obj.getType();
}

AMateria::~AMateria()
{
}

AMateria& AMateria::operator=(const AMateria& obj)
{
    this->type = obj.getType();
    return (*this);
}

std::string const &AMateria::getType() const
{
    return this->type;
}
    
void AMateria::use(ICharacter& target)
{
    (void)target;
}
