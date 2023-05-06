/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 11:40:19 by minkim            #+#    #+#             */
/*   Updated: 2022/10/24 12:37:58 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Convert.hpp"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        std::cout << "Error" << std::endl;
        return 0;
    }

    Convert cvt(argv[1]);

    cvt.printChar();
    cvt.printInt();
    cvt.printFloat();
    cvt.printDouble();
    
    return 0;
}
