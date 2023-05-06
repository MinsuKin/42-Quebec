/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:48:28 by minkim            #+#    #+#             */
/*   Updated: 2022/10/25 16:48:45 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP
# define CONVERT_HPP

# include <iostream>
# include <sstream>
# include <cmath>

class Convert {
 private:
   double num;
   long check_num;

 public:
    Convert(const char *str);
    Convert(const Convert& obj);
    ~Convert();
    Convert& operator=(const Convert& obj);

    double getNum(void) const;
    long getCheckNum(void) const;

    int toCheckNum(const double& num) const;

    char toChar(void) const;
    int toInt(void) const;
    float toFloat(void) const;
    double toDouble(void) const;

    void printChar(void) const;
    void printInt(void) const;
    void printFloat(void) const;
    void printDouble(void) const;
};

#endif
