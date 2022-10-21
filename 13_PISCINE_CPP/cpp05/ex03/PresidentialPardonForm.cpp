/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:31:14 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 14:49:07 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : Form("PresidentialPardonForm", 25, 5)
{
}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target) : Form(target, 25, 5)
{
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& obj) : Form(obj)
{
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& obj)
{
    setName(obj.getName());
    return *this;
}

void PresidentialPardonForm::execute(Bureaucrat const & executor) const
{   
    if (getSign() == false)
    {
        throw NotSignedException();
    }
    else if (this->getGradeExcute() < executor.getGrade())
    {
        throw GradeTooLowException();
    }
    else
    {
        std::cout << this->getName() << " has been pardoned by Zaphod Beeblebrox." << std::endl;
    }
}
