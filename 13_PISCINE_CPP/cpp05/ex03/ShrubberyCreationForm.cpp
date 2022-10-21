/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 21:30:01 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 14:19:54 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : Form("ShrubberyCreationForm", 145, 137)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) : Form(target, 145, 137)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& obj) : Form(obj)
{
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& obj)
{
    setName(obj.getName());
    return *this;
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
{
    std::ofstream out;
    std::string filename;
    std::string shrubbery;

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
        out.open(this->getName() + "_shrubbery");
        if (!out.is_open()) 
        {
            std::cout << "Error - cannot open output file" << std::endl;
            return ;
        }
        shrubbery = "               ,@@@@@@@,\n"
                    "       ,,,.   ,@@@@@@/@@,  .oo8888o.\n"
                    "    ,&%%&%&&%,@@@@@/@@@@@@,8888\\88/8o\n"
                    "   ,%&\\%&&%&&%,@@@\\@@@/@@@88\\88888/88'\n"
                    "   %&&%&%&/%&&%@@\\@@/ /@@@88888\\88888'\n"
                    "   %&&%/ %&%%&&@@\\ V /@@' `88\\8 `/88'\n"
                    "   `&%\\ ` /%&'    |.|        \\ '|8'\n"
                    "       |o|        | |         | |\n"
                    "       |.|        | |         | |\n"
                    "    \\\\/ ._\\//_/__/  ,\\_//__\\\\/.  \\_//__/_\n";
        out << shrubbery;
    }
}
