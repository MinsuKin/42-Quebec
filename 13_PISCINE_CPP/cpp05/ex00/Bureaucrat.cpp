/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:27:28 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 11:55:55 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("default")
{
    this->grade = 100;
}

Bureaucrat::Bureaucrat(std::string name, int grade) : name(name)
{
    this->grade = grade;
    if (grade < 1)
    {
        throw Bureaucrat::GradeTooHighException();
    }
    else if (grade > 150)
    {
        throw Bureaucrat::GradeTooLowException();
    }
}

Bureaucrat::Bureaucrat(const Bureaucrat& obj) : name(obj.getName())
{
    this->grade = obj.getGrade();
}

Bureaucrat::~Bureaucrat()
{
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& obj)
{
    // use 'const_cast' to change const value
    // (*(const_cast<std::string *>(&name))) = obj.getName(); // pointer const
    const_cast<std::string&>(name) = obj.getName(); // ref const
    this->grade = obj.getGrade();
    return *this;
}

std::string Bureaucrat::getName() const
{
    return this->name;
}

int Bureaucrat::getGrade() const
{
    return this->grade;
}

void Bureaucrat::incrementGrade()
{
    grade--;
    if (grade < 1)
    {
        throw Bureaucrat::GradeTooHighException();
    }
    else if (grade > 150)
    {
        throw Bureaucrat::GradeTooLowException();
    }
}

void Bureaucrat::decrementGrade()
{
    grade++;
    if (grade < 1)
    {
        throw Bureaucrat::GradeTooHighException();
    }
    else if (grade > 150)
    {
        throw Bureaucrat::GradeTooLowException();
    }
}
// 'throw' above is a keyword for run time
// 'const throw()' below is a keyword for compile time
// 'throw()' below is different from 'throw(void)'
const char *Bureaucrat::GradeTooHighException::what() const throw()
{
    return "GradeTooHighException";
}

const char *Bureaucrat::GradeTooLowException::what() const throw()
{
    return "GradeTooLowException";
}

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bc)
{
    out << bc.getName() << ", bureaucrat grade " << bc.getGrade();
    return (out);
}