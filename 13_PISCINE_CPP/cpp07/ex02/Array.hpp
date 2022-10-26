/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 15:51:32 by minkim            #+#    #+#             */
/*   Updated: 2022/10/25 20:28:58 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>

template <typename T>
class Array {
 private:
    T *array;
    std::size_t len;

 public:
    Array();
    Array(unsigned int n);
    Array(const Array& obj);
    ~Array();
    Array& operator=(const Array& obj);
    
    T& operator[] (std::size_t i);
    const T& operator[] (std::size_t i) const;

    std::size_t size() const;
};

# include "Array.tpp"

#endif
