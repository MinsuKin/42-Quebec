/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:27:33 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 22:33:14 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main(void)
{
	Intern someRandomIntern;
	Form* rrf;
	Form* rr;
	Form* r;
	Form* wrong;

	try
	{
		rrf = someRandomIntern.makeForm("robotomy request", "Bender");
		rr = someRandomIntern.makeForm("shrubbery creation", "Bende");
		r = someRandomIntern.makeForm("presidential pardon", "Bend");

		std::cout << *rrf << std::endl;
		std::cout << *rr << std::endl;
		std::cout << *r << std::endl;
		
		delete rrf;
		delete rr;
		delete r;
		
		wrong = someRandomIntern.makeForm("wrong request", "Ben");
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	return (0);
}