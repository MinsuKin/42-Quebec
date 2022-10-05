/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:47:37 by minkim            #+#    #+#             */
/*   Updated: 2022/10/05 16:29:45 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "contact.hpp"

Contact::Contact()
{

}

Contact::~Contact()
{

}

void    Contact::AddContent()
{
    std::cout << "FIRST NAME : ";
    std::getline(std::cin, info[0]);
    std::cout << "LAST NAME : ";
    std::getline(std::cin, info[1]);
    std::cout << "NICKNAME : ";
    std::getline(std::cin, info[2]);
    std::cout << "PHONE NUMBER : ";
    std::getline(std::cin, info[3]);
    std::cout << "DARKEST SECRET : ";
    std::getline(std::cin, info[4]);

    for (int i = 0; i < 5; i++)
    {
        content[i] = info[i];
        if (content[i].length() >= 10)
        {
            content[i].replace(9, (content[i].length() - 9), ".");
        }
        else
        {
            while (content[i].length() != 10)
            {
                content[i].insert(0, " ");
            }
        }
    }
}

void    Contact::PrintContent()
{
    for (int i = 0; i < 3; i++)
    {
        std::cout << "|";
        std::cout << content[i];
    }
    std::cout << "|";
}

void    Contact::PrintSearch()
{
    std::cout << "FIRST NAME : " << info[0] << std::endl;
    std::cout << "LAST NAME : " << info[1] << std::endl;
    std::cout << "NICKNAME : " << info[2] << std::endl;
    std::cout << "PHONE NUMBER : " << info[3] << std::endl;
    std::cout << "DARKEST SECRET : " << info[4] << std::endl;
}
