/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:49:07 by minkim            #+#    #+#             */
/*   Updated: 2022/10/28 17:12:17 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main()
{
    // test from pdf
    Span sp = Span(5);

    sp.addNumber(6);
    sp.addNumber(3);
    sp.addNumber(17);
    sp.addNumber(9);
    sp.addNumber(11);

    std::cout << sp.shortestSpan() << std::endl;
    std::cout << sp.longestSpan() << std::endl;
    
    // // test for SpanCapacityFullException
    // try
    // {
    //     Span sp = Span(1);

    //     sp.addNumber(6);
    //     sp.addNumber(3); // Error
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }

    // // test for NoSpanFoundException
    // try
    // {
    //     Span sp = Span(5);

    //     sp.addNumber(6);

    //     std::cout << sp.shortestSpan() << std::endl; // Error
    //     std::cout << sp.longestSpan() << std::endl;
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }

    // // test for MAX and MIN values
    // try
    // {
    //     Span sp = Span(2);

    //     sp.addNumber(INT_MIN);
    //     sp.addNumber(INT_MAX);

    //     std::cout << sp.shortestSpan() << std::endl;
    //     std::cout << sp.longestSpan() << std::endl;
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }

    // // test for addRange()
    // try
    // {
    //     Span sp = Span(10000);

    //     sp.addRange(1, 10000);
    //     // sp.addRange(1, 10001); // Error

    //     std::cout << sp.shortestSpan() << std::endl;
    //     std::cout << sp.longestSpan() << std::endl;
    // }
    // catch(const std::exception& e)
    // {
    //     std::cerr << e.what() << '\n';
    // }

    return 0;
}
