/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:48:54 by minkim            #+#    #+#             */
/*   Updated: 2022/10/28 17:11:22 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(unsigned int N)
{
    this->N = N;
}

Span::Span(const Span& obj)
{
    N = obj.N;
    vec = obj.vec;
}

Span::~Span()
{
}

Span& Span::operator=(const Span& obj)
{
    N = obj.N;
    vec = obj.vec;
    return (*this);
}

unsigned int Span::getN()
{
    return this->N;
}

std::vector<int> Span::getVec()
{
    return this->vec;
}

void Span::addNumber(const int& num)
{
    if (vec.size() >= N)
        throw std::runtime_error("SpanCapacityFullException");
    
    vec.push_back(num);
}

void Span::addRange(const int& start, const int& finish)
{
    unsigned int space = N - vec.size();
    unsigned int range = finish - start + 1;
    
    if (range > space)
        throw std::runtime_error("SpanCapacityNotEnoughException");

    for (int i = start; i <= finish; i++)
        vec.push_back(i);
}

long Span::shortestSpan()
{
    if (vec.size() < 2)
        throw std::logic_error("NoSpanFoundException");

    std::vector<int> gap(vec);
    std::sort(gap.begin(), gap.end());

    long span = static_cast<long>(gap[1]) - static_cast<long>(gap[0]);
    for (size_t i = 2; i < gap.size(); i++)
    {
        long tmp = static_cast<long>(gap[i]) - static_cast<long>(gap[i - 1]);
        if (tmp < span)
            span = tmp;
        if (span == 0)
            return 0;
    }
    return span;
}

long  Span::longestSpan()
{
    if (vec.size() < 2)
        throw std::logic_error("NoSpanFoundException");

    long max = *std::max_element(vec.begin(), vec.end());
    long min = *std::min_element(vec.begin(), vec.end());
    return max - min;
}
