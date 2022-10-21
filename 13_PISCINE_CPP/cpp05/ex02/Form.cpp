/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:22:00 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 14:05:44 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

Form::Form() : name("default"), grade_sign(100), grade_excute(100)
{
    sign = false;
}

Form::Form(std::string name, int grade_sign, int grade_excute) : name(name), grade_sign(grade_sign), grade_excute(grade_excute)
{
    sign = false;
    if (grade_sign < 1 || grade_excute < 1)
    {
        throw GradeTooHighException();
    }
    else if (grade_sign > 150 || grade_excute > 150)
    {
        throw GradeTooLowException();
    }
}

Form::Form(const Form& obj) : name(obj.getName()), grade_sign(obj.getGradeSign()), grade_excute(obj.getGradeExcute())
{
    this->sign = obj.getSign();
}

Form::~Form()
{
}

Form& Form::operator=(const Form& obj)
{
    const_cast<std::string&>(name) = obj.getName();
    this->sign = obj.getSign();
    const_cast<int&>(grade_sign) = obj.getGradeSign();
    const_cast<int&>(grade_excute) = obj.getGradeExcute();
    return *this;
}

const char *Form::GradeTooHighException::what() const throw()
{
    return "GradeTooHighException";
}

const char *Form::GradeTooLowException::what() const throw()
{
    return "GradeTooLowException";
}

const char *Form::NotSignedException::what() const throw()
{
    return "NotSignedException";
}

const std::string& Form::getName() const
{
    return this->name;
}

const bool& Form::getSign() const
{
    return this->sign;
}

const int& Form::getGradeSign() const
{
    return this->grade_sign;
}

const int& Form::getGradeExcute() const
{
    return this->grade_excute;
}

void Form::beSigned(const Bureaucrat &bc)
{
    if (grade_sign < bc.getGrade())
    {
        throw GradeTooLowException();
    }
    else
    {
        sign = true;
    }
}

void Form::setName(const std::string& name)
{
    const_cast<std::string&>(this->name) = name;
}

std::ostream &operator<<(std::ostream &out, const Form &f)
{
    out << f.getName() 
        << ", signed : " << std::boolalpha << f.getSign()
        << ", grade required to sign : " << f.getGradeSign()
        << ", grade required to execute : " << f.getGradeExcute();
    return (out);
}
