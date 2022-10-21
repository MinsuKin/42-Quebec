/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 15:08:55 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 22:25:32 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern& obj)
{
    static_cast<void>(obj);
}

Intern::~Intern()
{
}

Intern& Intern::operator=(const Intern& obj)
{
    static_cast<void>(obj);
    return *this;
}

const char *Intern::NameNotFoundException::what() const throw()
{
    return "NameNotFoundException";
}

Form* createShrubberyCreationForm(const std::string& target)
{
    return new ShrubberyCreationForm(target);
}

Form* createRobotomyRequestForm(const std::string& target)
{
    return new RobotomyRequestForm(target);
}

Form* createPresidentialPardonForm(const std::string& target)
{
    return new PresidentialPardonForm(target);
}

Form* Intern::makeForm(const std::string& name, const std::string& target)
{
    std::string form_type[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
    Form* (*f[3])(const std::string&) = {createShrubberyCreationForm, createRobotomyRequestForm, createPresidentialPardonForm};
    Form* tmp;

    for (size_t i = 0; i < 3; i++)
    {
        if (name == form_type[i])
        {
            tmp = (*f[i])(target);
            std::cout << "Intern creates " << tmp->getName() << std::endl;
            return tmp;
        }
    }
    throw NameNotFoundException();
    
    return NULL;
}
