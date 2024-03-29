/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:27:33 by minkim            #+#    #+#             */
/*   Updated: 2022/10/19 20:49:54 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main(void)
{
    try
    {
        Bureaucrat("A", 0);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        Bureaucrat("B", 151);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        Bureaucrat c("C", 2);
        std::cout << c << std::endl;
        c.incrementGrade();
        std::cout << c << std::endl;
        c.incrementGrade();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        Bureaucrat d("D", 149);
        std::cout << d << std::endl;
        d.decrementGrade();
        std::cout << d << std::endl;
        d.decrementGrade();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    // // copy operator test
    // Bureaucrat a("A", 1);
    // std::cout << a << std::endl;
    // Bureaucrat z("Z", 150);
    // a = z;
    // std::cout << a << std::endl;

    return 0;
}