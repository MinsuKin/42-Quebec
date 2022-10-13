/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:34:24 by minkim            #+#    #+#             */
/*   Updated: 2022/10/11 17:18:28 by minkim           ###   ########.fr       */
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
    // 멤버 함수이기 때문에 동일한 클래스를 사용하는 객체의 private 멤버는 추가적인 멤버 함수를 사용하지 않고 직접 사용이 가능하다.
    // Possible to use private member variable when it is from the same class.
    // this->value = fx.value;
}

Fixed &Fixed::operator=(const Fixed &fx)
{
    std::cout << "Copy assignment operator called" << std::endl;
    this->value = fx.getRawBits();
    // this->value = fx.value;
    return (*this);
}

Fixed::~Fixed(void)
{
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
    // std::cout << "getRawBits member function called" << std::endl;
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

// https://modoocode.com/203
// std::cout << a 
// ==
// std::cout.operator<<(a)
// so overloading can be done and << can deal with additional objects.
std::ostream &operator<<(std::ostream &out, const Fixed &fx)
{
    out << fx.toFloat();
    return (out);
}
