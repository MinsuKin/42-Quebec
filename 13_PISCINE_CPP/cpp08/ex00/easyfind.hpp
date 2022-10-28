/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 18:42:23 by minkim            #+#    #+#             */
/*   Updated: 2022/10/27 21:20:47 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include <iostream>
# include <algorithm>

template <typename T>
typename T::iterator easyfind(T& container, int num)
{
    typename T::iterator itr;

    itr = std::find(container.begin(), container.end(), num);
    if (itr == container.end())
        throw std::runtime_error("ValueNotFoundException");
    return itr;
}

#endif
