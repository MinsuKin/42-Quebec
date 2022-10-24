/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 18:40:00 by minkim            #+#    #+#             */
/*   Updated: 2022/10/24 19:35:24 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base * generate()
{
    int num;

    srand((unsigned int)time(NULL));
    num = rand() % 3;
    switch (num)
    {
        case 0:
            return new A;
            break;
        case 1:
            return new B;
            break;
        case 2:
            return new C;
            break;

        default:
            break;
    }
    return NULL;
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p)) // return NULL if fails
    {
		std::cout << "p: \"A\"" << std::endl;
        return;
    }
	if (dynamic_cast<B*>(p))
    {
		std::cout << "p: \"B\"" << std::endl;
        return;
    }
	if (dynamic_cast<C*>(p))
    {
		std::cout << "p: \"C\"" << std::endl;
        return;
    }
}

void identify(Base& p)
{
    try
    {
        A &a = dynamic_cast<A&>(p);
        std::cout << "p: \"A\"" << std::endl;
        static_cast<void>(a);
    }
    catch(const std::exception& e) {}  // e = std::bad_cast
    try
    {
        B &b = dynamic_cast<B&>(p);
        std::cout << "p: \"B\"" << std::endl;
        static_cast<void>(b);
    }
    catch(const std::exception& e) {}
    try
    {
        C &c = dynamic_cast<C&>(p);
        std::cout << "p: \"C\"" << std::endl;
        static_cast<void>(c);
    }
    catch(const std::exception& e) {}
}
