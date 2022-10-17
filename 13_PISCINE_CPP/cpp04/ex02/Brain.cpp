/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:25:32 by minkim            #+#    #+#             */
/*   Updated: 2022/10/16 17:21:54 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
    std::cout << "Brain default constructor called" << std::endl;
    for (int i = 0; i < 100; i++)
    {
        std::stringstream ss;
        ss << i;
        this->ideas[i] = ss.str();
    }
}

Brain::Brain(const Brain& obj)
{
    std::cout << "Brain copy constructor called" << std::endl;
    for (size_t i = 0; i < 100; i++)
    {
        this->ideas[i] = obj.getIdea(i);
    }
}

Brain::~Brain()
{
    std::cout << "Brain destructor called" << std::endl;
}

Brain& Brain::operator=(const Brain& obj)
{
    std::cout << "Brain copy assignment operator called" << std::endl;
    for (size_t i = 0; i < 100; i++)
    {
        this->ideas[i] = obj.getIdea(i);
    }
    return (*this);
}

std::string Brain::getIdea(const int& i) const
{
    return ideas[i];
}

void Brain::setIdea(const int& i, std::string idea)
{
    ideas[i] = idea;
}
