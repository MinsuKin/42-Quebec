/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:16 by minkim            #+#    #+#             */
/*   Updated: 2022/10/13 16:08:39 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Fixed.hpp"
#include "Point.hpp"

int main(void)
{
    Point a(5, 0);
    Point b(0, 5);
    Point c(0, 0);

    Point point(1, 1);

    if (bsp(a, b, c, point))
        std::cout << "The point is in the triangle" << std::endl;
    else
        std::cout << "The point is out of the triangle" << std::endl;

    Point point2(-1, -1);

    if (bsp(a, b, c, point2))
        std::cout << "The point2 is in the triangle" << std::endl;
    else
        std::cout << "The point2 is out of the triangle" << std::endl;

    return 0;
}
