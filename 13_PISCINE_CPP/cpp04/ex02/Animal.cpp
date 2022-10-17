/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:01:16 by minkim            #+#    #+#             */
/*   Updated: 2022/10/16 18:50:32 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal()
{
    std::cout << "Animal default constructor called" << std::endl;
    type = "Animal";
}

Animal::Animal(const Animal& obj)
{
    std::cout << "Animal copy constructor called" << std::endl;
    this->type = obj.getType();
}

Animal::~Animal()
{
    std::cout << "Animal destructor called" << std::endl;
}

Animal& Animal::operator=(const Animal& obj)
{
    std::cout << "Animal copy assignment operator called" << std::endl;
    this->type = obj.getType();
    return (*this);
}

std::string Animal::getType(void) const
{
    return this->type;
}
// Pure virtual function - it can never be used whether it's defined or not
// void Animal::makeSound(void) const 
// {
//     std::cout << "Animal : ..." << std::endl;
// }
