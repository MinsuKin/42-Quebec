/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:34:24 by minkim            #+#    #+#             */
/*   Updated: 2022/10/13 14:14:45 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed(void)
{
    std::cout << "Default constructor called" << std::endl;
    this->value = 0;
}

Fixed::Fixed(const Fixed &fx)
{
    std::cout << "Copy constructor called" << std::endl;
    this->value = fx.getRawBits();
}

Fixed &Fixed::operator=(const Fixed &fx)
{
    std::cout << "Copy assignment operator called" << std::endl;
    this->value = fx.getRawBits();
    return (*this);
}

Fixed::~Fixed(void)
{
    std::cout << "Destructor called" << std::endl;
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
    std::cout << "Int constructor called" << std::endl;
    this->value = num << this->frac_bit;
}

Fixed::Fixed(const float fp_num)
{
    std::cout << "Float constructor called" << std::endl;
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

Fixed &Fixed::operator++(void) // ++f
{
	++this->value;
	return (*this);
}

Fixed &Fixed::operator--(void) // --f
{
	--this->value;
	return (*this);
}
// 후위 연산자의 반환 값은 임시로 만들어진 객체이므로
// 해당 값에 다시 증감 연산을 했을 때 임시 객체의 값이 증감하게 되는 문제가 있다.
// 그걸 막기 위해 const를 붙여준다.
// Used const to prevent bad usage like (a++)++; -> make (a++) Rvalue
const Fixed Fixed::operator++(int) // f++
{
    const Fixed tmp(*this);
    
    this->value++;
    return tmp;
}

const Fixed Fixed::operator--(int) // f--
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
