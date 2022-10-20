/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:01:03 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 11:21:00 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat()
{
    std::cout << "Cat default constructor called" << std::endl;
    type = "Cat";
    brain = new Brain();
}

Cat::Cat(const Cat& obj)
{
    std::cout << "Cat copy constructor called" << std::endl;
    this->type = obj.getType();
    brain = new Brain(*obj.getBrain());
}

Cat::~Cat()
{
    delete brain;
    std::cout << "Cat destructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& obj)
{
    std::cout << "Cat copy assignment operator called" << std::endl;
    this->type = obj.getType();
    delete brain;
    brain = new Brain(*obj.getBrain());
    return (*this);
}

void Cat::makeSound(void) const
{
    std::cout << "Cat : Meow meow" << std::endl;
}

Brain *Cat::getBrain(void) const
{
    return this->brain;
}
