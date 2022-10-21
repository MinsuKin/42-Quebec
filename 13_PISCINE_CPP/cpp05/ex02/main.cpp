/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:27:33 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 15:07:11 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main(void)
{
	try
	{
		Bureaucrat a("a", 150);
		Bureaucrat b("b", 1);
		ShrubberyCreationForm x("x");
		RobotomyRequestForm y("y");
		PresidentialPardonForm z("z");

		std::cout << x << std::endl;
		std::cout << y << std::endl;
		std::cout << z << std::endl;
		std::cout << std::endl;

		a.signForm(x);
		a.executeForm(x);
		a.signForm(y);
		a.executeForm(y);
		a.signForm(z);
		a.executeForm(z);

		b.signForm(x);
		b.executeForm(x);
		b.signForm(y);
		b.executeForm(y);
		b.signForm(z);
		b.executeForm(z);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

    // // copy operator test
    // ShrubberyCreationForm c("c");
    // std::cout << c << std::endl;
    // ShrubberyCreationForm d("d");
    // c = d;
    // std::cout << c << std::endl;
	
	return (0);
}