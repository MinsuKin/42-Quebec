/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:49:02 by minkim            #+#    #+#             */
/*   Updated: 2022/10/05 17:08:33 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
    index = 0;
}

PhoneBook::~PhoneBook()
{

}

void    PhoneBook::AddContact()
{
    contacts[index % 8].AddContent();
    index++;
}

void    PrintLine(int cnt)
{
    for (int i = 0; i < cnt; i++)
        std::cout << "=";
    std::cout << std::endl;
}

int    PhoneBook::PrintAll()
{
    int count = 8;

    if (index == 0)
    {
        std::cout << "The Phonebook is empty." << std::endl;
        return (1);
    }
    else
    {
        if (index < 8)
            count = index;
        std::cout << std::endl;
        PrintLine(40);
        std::cout << "|Index|First Name|Last  Name|Nick  Name|" << std::endl;
        for (int i = 0; i < count; i++)
        {
            PrintLine(40);
            std::cout << "|    " << i + 1;
            contacts[i].PrintContent();
            std::cout << std::endl;
        }
        PrintLine(40);
        std::cout << std::endl;
    }
    return (0);
}

int    PhoneBook::Search()
{
    std::string id;
    int idx;

    while (true)
    {
        std::cout << "Enter the index('0' -> main menu) : ";
        std::getline(std::cin, id);
        for (size_t i = 0; i < id.length(); i++)
        {
            if (isdigit(id[i]) == 0)
            {
                if (i == 0 && id[i] == '+')
                    continue;    
                std::cout << "Index can only be an unsigned integer." << std::endl;
                return (0);
            }
        }
        idx = atoi(id.c_str());
        if (idx == 0)
            return (0);
        else if (idx < 1 || idx > 8)
            std::cout << "Index cannot be lower than 1 or higher than 8." << std::endl;
        else if(idx > index)
            std::cout << "No information for Index " << idx << std::endl;
        else
        {
            std::cout << std::endl;
            PrintLine(40);
            contacts[idx - 1].PrintSearch();
            PrintLine(40);
            std::cout << std::endl;
        }
    }
    return (0);
}
