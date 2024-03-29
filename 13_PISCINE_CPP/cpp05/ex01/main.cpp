/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:27:33 by minkim            #+#    #+#             */
/*   Updated: 2022/10/20 14:06:34 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void)
{
	try
	{
		Bureaucrat a("a", 150);
		Bureaucrat b("b", 1);
		Form c("c", 100, 100);

		a.signForm(c);
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
		std::cout << std::endl;

		b.signForm(c);
		std::cout << a << std::endl;
		std::cout << b << std::endl;
		std::cout << c << std::endl;
		std::cout << std::endl;	

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

    // // copy operator test
    // Form c("c", 100, 100);
    // std::cout << c << std::endl;
    // Form d("d", 10, 10);
    // c = d;
    // std::cout << c << std::endl;

	return (0);
}