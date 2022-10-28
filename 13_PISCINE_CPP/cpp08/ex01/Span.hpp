/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:49:00 by minkim            #+#    #+#             */
/*   Updated: 2022/10/28 14:20:32 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <iostream>
# include <vector>
# include <numeric>

class Span {
 private:
    std::vector<int> vec;
    unsigned int N;
    
 public:
    Span(unsigned int N);
    Span(const Span& obj);
    ~Span();
    Span& operator=(const Span& obj);

    unsigned int getN();
    std::vector<int> getVec();

    void addNumber(const int& num);
    void addRange(const int& start, const int& finish);
    long shortestSpan();
    long longestSpan();
};

#endif
