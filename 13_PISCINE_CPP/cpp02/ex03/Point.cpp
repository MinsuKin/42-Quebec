/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:19 by minkim            #+#    #+#             */
/*   Updated: 2022/10/12 16:01:10 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

Point::Point(void) : x(0), y(0)
{
}

Point::Point(const float x, const float y) : x(x), y(y)
{
}

Point::Point(const Point& pt) : x(pt.getX()), y(pt.getY())
{
}

Point& Point::operator=(const Point& pt)
{
    const_cast<Fixed&>(x) = pt.getX();
    const_cast<Fixed&>(y) = pt.getY();
    return (*this);
}

Point::~Point()
{
}

Fixed Point::getX(void) const
{
    return this->x;
}

Fixed Point::getY(void) const
{
    return this->y;
}
