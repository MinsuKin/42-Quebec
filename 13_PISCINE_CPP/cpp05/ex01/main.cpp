/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 11:27:33 by minkim            #+#    #+#             */
/*   Updated: 2022/10/18 17:16:28 by minkim           ###   ########.fr       */
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
        Bureaucrat c("C", 1);
        c.incrementGrade();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        Bureaucrat d("D", 150);
        d.decrementGrade();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    Bureaucrat z("Z", 2);
    std::cout << z << std::endl;
    z.incrementGrade();
    std::cout << z << std::endl;
    z.decrementGrade();
    std::cout << z << std::endl;

    return 0;
}