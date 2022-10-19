/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:27:28 by minkim            #+#    #+#             */
/*   Updated: 2022/10/18 17:21:27 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

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