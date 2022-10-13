/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:34:21 by minkim            #+#    #+#             */
/*   Updated: 2022/10/12 14:54:31 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed
{
private:
    int value;
    static const int frac_bit = 8;

public:
    Fixed(void);
    Fixed(const int num);
    Fixed(const float fp_num);
    Fixed(const Fixed &fx);
    Fixed &operator=(const Fixed &fx);
    ~Fixed(void);

    int getRawBits(void) const;
    void setRawBits(int const raw);
    
    float toFloat(void) const;
    int toInt(void) const;

    bool operator>(Fixed const &fx) const;
    bool operator<(Fixed const &fx) const;
    bool operator>=(Fixed const &fx) const;
    bool operator<=(Fixed const &fx) const;
    bool operator==(Fixed const &fx) const;
    bool operator!=(Fixed const &fx) const;
    Fixed operator+(Fixed const &fx) const;
    Fixed operator-(Fixed const &fx) const;
    Fixed operator*(Fixed const &fx) const;
    Fixed operator/(Fixed const &fx) const;
    Fixed &operator++(void); // ++f
    Fixed &operator--(void); // --f
    const Fixed operator++(int); // f++
    const Fixed operator--(int); // f--

    static Fixed &max(Fixed &fx1, Fixed &fx2);
    static Fixed &min(Fixed &fx1, Fixed &fx2);
    static const Fixed &max(Fixed const &fx1, Fixed const &fx2);
    static const Fixed &min(Fixed const &fx1, Fixed const &fx2);
};

std::ostream &operator<<(std::ostream &out, const Fixed &fx);

#endif
