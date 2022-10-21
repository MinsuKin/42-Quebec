/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:30:34 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 14:46:26 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : Form("RobotomyRequestForm", 72, 45)
{
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target) : Form(target, 72, 45)
{
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& obj) : Form(obj)
{
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& obj)
{
    setName(obj.getName());
    return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
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
        std::cout << "Drilling noises : drrrrrrrr...!" << std::endl;
        std::cout << "* Robotization success rate: 50% *" << std::endl;
        srand((unsigned int)time(NULL));
        if (rand() % 2)
        {
            std::cout << this->getName() << " is successfully robotomized!" << std::endl;
        }
        else
        {
            std::cout << this->getName() << "'s robotization failed." << std::endl;
        }
    }
}
