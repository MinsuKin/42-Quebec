/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:34:21 by minkim            #+#    #+#             */
/*   Updated: 2022/10/10 19:44:06 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed
{
private:
    int value;
    static const int frac_bit = 8;

public:
    Fixed(void);
    Fixed(const Fixed &fx);
    Fixed &operator=(const Fixed &fx);
    ~Fixed(void);

    int getRawBits(void) const;
    void setRawBits(int const raw);
};

#endif
