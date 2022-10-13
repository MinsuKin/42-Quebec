/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:44:08 by minkim            #+#    #+#             */
/*   Updated: 2022/10/13 12:34:21 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
	bool ret = false;

	if ((a.getY() > point.getY()) != (b.getY() > point.getY()))
	{
		if (((b.getX() - a.getX()) * ((point.getY() - a.getY()) / (b.getY() - a.getY())) + a.getX()) >= point.getX())
		{
			if (ret)
				ret = false;
			else
				ret = true;
		}
	}
	if ((a.getY() > point.getY()) != (c.getY() > point.getY()))
	{
		if (((c.getX() - a.getX()) * ((point.getY() - a.getY()) / (c.getY() - a.getY())) + a.getX()) >= point.getX())
		{
			if (ret)
				ret = false;
			else
				ret = true;
		}
	}
	if ((b.getY() > point.getY()) != (c.getY() > point.getY()))
	{
		if (((c.getX() - b.getX()) * ((point.getY() - b.getY()) / (c.getY() - b.getY())) + b.getX()) >= point.getX())
		{
			if (ret)
				ret = false;
			else
				ret = true;
		}
	}
	return (ret);
}