/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:21 by minkim            #+#    #+#             */
/*   Updated: 2022/10/12 15:57:25 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_HPP
# define POINT_HPP

# include <iostream>
# include "Fixed.hpp"

class Point {
 private:
    Fixed const x;
    Fixed const y;

 public:
    Point(void);
    Point(const float x, const float y);
    Point(const Point& pt);
    Point& operator=(const Point& pt);
    ~Point(void);

    Fixed getX(void) const;
    Fixed getY(void) const;
};

bool bsp( Point const a, Point const b, Point const c, Point const point);

#endif
