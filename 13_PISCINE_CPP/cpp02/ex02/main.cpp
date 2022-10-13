/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:34:26 by minkim            #+#    #+#             */
/*   Updated: 2022/10/13 14:14:36 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"

int main(void)
{
    Fixed a;
    Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

    std::cout << a << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;

    std::cout << b << std::endl;
    
    std::cout << Fixed::max( a, b ) << std::endl;
    
	// std::cout << "a = " << a << std::endl;
	// std::cout << "++a = " << ++a << std::endl;
	// std::cout << "a = " << a << std::endl;
	// std::cout << "a++ = " << a++ << std::endl;
	// std::cout << "a = " << a << std::endl;
	// std::cout << "--a = " << --a << std::endl;
	// std::cout << "a = " << a << std::endl;
	// std::cout << "a-- = " << a-- << std::endl;
	// std::cout << "a = " << a << std::endl;

	// std::cout << "b = " << b << std::endl;
	// std::cout << std::endl;
	
	// std::cout << "max = " << Fixed::max( a, b ) << std::endl;
	// std::cout << "min = " << Fixed::min( a, b ) << std::endl;

	// std::cout << std::endl;

	// std::cout << "5.0 < 4.0 = " << (Fixed(5.0f) < Fixed(4.0f)) << std::endl;
	// std::cout << "5.0 > 4.0 = " << (Fixed(5.0f) > Fixed(4.0f)) << std::endl;
	// std::cout << "5.0 <= 4.0 = " << (Fixed(5.0f) <= Fixed(4.0f)) << std::endl;
	// std::cout << "5.0 >= 4.0 = " << (Fixed(5.0f) >= Fixed(4.0f)) << std::endl;
	// std::cout << "4.0 == 4.0 = " << (Fixed(4.0f) == Fixed(4.0f)) << std::endl;
	// std::cout << "4.0 != 4.0 = " << (Fixed(4.0f) != Fixed(4.0f)) << std::endl;
	// std::cout << "4.2 + 2.0 = " << (Fixed(4.2f) + Fixed(2.0f)) << std::endl;
	// std::cout << "4.2 - 2.0 = " << (Fixed(4.2f) - Fixed(2.0f)) << std::endl;
	// std::cout << "4.2 * 2.0 = " << (Fixed(4.2f) * Fixed(2.0f)) << std::endl;
	// std::cout << "4.2 / 2.0 = " << (Fixed(4.2f) / Fixed(2.0f)) << std::endl;

    return 0;
}
