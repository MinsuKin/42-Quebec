/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:07:50 by minkim            #+#    #+#             */
/*   Updated: 2022/10/05 17:08:51 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "PhoneBook.hpp"

int	main(void)
{
    PhoneBook pb;
    std::string cmd;
    
    while (true)
    {
        std::cout << "Enter command(ADD, SEARCH, EXIT)";
        std::cout << " : ";
        std::getline(std::cin, cmd);
    	if (std::cin.eof())
		    return (0);
        else if (cmd == "ADD" || cmd == "add")
        {
            pb.AddContact();
        }
        else if (cmd == "SEARCH" || cmd == "search")
        {
            if (pb.PrintAll() == 0)
                pb.Search();
        }
        else if (cmd == "EXIT" || cmd == "exit")
        {
            break;
        }
        else
        {
            std::cout << "Command not found" << std::endl;
        }
    }
    return (0);
}
