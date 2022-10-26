/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 14:14:25 by minkim            #+#    #+#             */
/*   Updated: 2022/10/25 15:44:20 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

# include <iostream>

template <typename T>
void iter(T *array, size_t len, void (*f)(T&))
{
    for (size_t i = 0; i < len; i++)
    {
        (*f)(array[i]);
    }
}

template <typename T>
void ftPrint(T& element)
{
    std::cout << element << " ";
}

#endif
