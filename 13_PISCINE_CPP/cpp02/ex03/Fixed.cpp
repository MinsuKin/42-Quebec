/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:11 by minkim            #+#    #+#             */
/*   Updated: 2022/10/13 12:35:22 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void)
{
    this->value = 0;
}

Fixed::Fixed(const Fixed &fx)
{
    this->value = fx.getRawBits();
}

Fixed &Fixed::operator=(const Fixed &fx)
{
    this->value = fx.getRawBits();
    return (*this);
}

Fixed::~Fixed(void)
{
}

int Fixed::getRawBits(void) const
{
    return this->value;
}

void Fixed::setRawBits(int const raw)
{
    this->value = raw;
}

Fixed::Fixed(const int num)
{
    this->value = num << this->frac_bit;
}

Fixed::Fixed(const float fp_num)
{
    this->value = roundf(fp_num * (1 << this->frac_bit));
}

float Fixed::toFloat(void) const
{
    return ((float)this->value / (1 << this->frac_bit));
}

int Fixed::toInt(void) const
{
    return (this->value >> this->frac_bit);
}

std::ostream &operator<<(std::ostream &out, const Fixed &fx)
{
    out << fx.toFloat();
    return (out);
}

bool Fixed::operator>(Fixed const &fx) const
{
    return (this->getRawBits() > fx.getRawBits());
}

bool Fixed::operator<(Fixed const &fx) const
{
    return (this->getRawBits() < fx.getRawBits());
}

bool Fixed::operator>=(Fixed const &fx) const
{
    return (this->getRawBits() >= fx.getRawBits());
}

bool Fixed::operator<=(Fixed const &fx) const
{
    return (this->getRawBits() <= fx.getRawBits());
}

bool Fixed::operator==(Fixed const &fx) const
{
    return (this->getRawBits() == fx.getRawBits());
}

bool Fixed::operator!=(Fixed const &fx) const
{
    return (this->getRawBits() != fx.getRawBits());
}

Fixed Fixed::operator+(Fixed const &fx) const
{
    Fixed ret(this->toFloat() + fx.toFloat());
    
    return (ret);
}

Fixed Fixed::operator-(Fixed const &fx) const
{
    Fixed ret(this->toFloat() - fx.toFloat());
    
    return (ret);
}

Fixed Fixed::operator*(Fixed const &fx) const
{
    Fixed ret(this->toFloat() * fx.toFloat());
    
    return (ret);
}

Fixed Fixed::operator/(Fixed const &fx) const
{
    Fixed ret(this->toFloat() / fx.toFloat());
    
    return (ret);
}

Fixed &Fixed::operator++(void)
{
	++this->value;
	return (*this);
}

Fixed &Fixed::operator--(void)
{
	--this->value;
	return (*this);
}

const Fixed Fixed::operator++(int)
{
    const Fixed tmp(*this);
    
    this->value++;
    return tmp;
}

const Fixed Fixed::operator--(int)
{
    const Fixed tmp(*this);
    
    this->value--;
    return tmp;
}

Fixed &Fixed::max(Fixed &fx1, Fixed &fx2)
{
    if (fx1 >= fx2)
        return fx1;
    else
        return fx2;
}

Fixed &Fixed::min(Fixed &fx1, Fixed &fx2)
{
    if (fx1 <= fx2)
        return fx1;
    else
        return fx2;
}

const Fixed &Fixed::max(Fixed const &fx1, Fixed const &fx2)
{
    if (fx1 >= fx2)
        return fx1;
    else
        return fx2;
}

const Fixed &Fixed::min(Fixed const &fx1, Fixed const &fx2)
{
    if (fx1 <= fx2)
        return fx1;
    else
        return fx2;
}
