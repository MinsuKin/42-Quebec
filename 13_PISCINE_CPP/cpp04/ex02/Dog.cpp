/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:00:49 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 11:21:04 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog()
{
    std::cout << "Dog default constructor called" << std::endl;
    type = "Dog";
    brain = new Brain();
}

Dog::Dog(const Dog& obj)
{
    std::cout << "Dog copy constructor called" << std::endl;
    this->type = obj.getType();
    brain = new Brain(*obj.getBrain());
}

Dog::~Dog()
{
    delete brain;
    std::cout << "Dog destructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& obj)
{
    std::cout << "Dog copy assignment operator called" << std::endl;
    this->type = obj.getType();
    delete brain;
    brain = new Brain(*obj.getBrain());
    return (*this);
}

void Dog::makeSound(void) const
{
    std::cout << "Dog : Woof woof" << std::endl;
}

Brain *Dog::getBrain(void) const
{
    return this->brain;
}
