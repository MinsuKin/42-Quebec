/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 11:55:58 by minkim            #+#    #+#             */
/*   Updated: 2022/10/16 16:36:45 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat()
{
    std::cout << "WrongCat default constructor called" << std::endl;
    type = "WrongCat";
}

WrongCat::WrongCat(const WrongCat& obj)
{
    std::cout << "WrongCat copy constructor called" << std::endl;
    this->type = obj.getType();
}

WrongCat::~WrongCat()
{
    std::cout << "WrongCat destructor called" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& obj)
{
    std::cout << "WrongCat copy assignment operator called" << std::endl;
    this->type = obj.getType();
    return (*this);
}

std::string WrongCat::getType(void) const
{
    return this->type;
}

void WrongCat::makeSound(void) const
{
    std::cout << "WrongCat : Meow Meow" << std::endl;
}