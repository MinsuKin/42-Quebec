/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 13:48:30 by minkim            #+#    #+#             */
/*   Updated: 2022/10/25 16:48:55 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

void ftExit(void)
{
    std::cout << "Error" << std::endl;
    exit(EXIT_FAILURE);
}

bool ftPrintable(char c)
{
    if (c >= 32 && c <= 126)
        return true;
    return false;
}

Convert::Convert(const char *str)
{
    char *endptr;

    if (!str[0])
        ftExit();
    num = std::strtod(str, &endptr);
    check_num = toCheckNum(num);
    if (*endptr != '\0' && *endptr != 'f')
        ftExit();
    if (*endptr == 'f')
    {
        if (str == endptr)
            ftExit();
        if (*(endptr + 1))
            ftExit();
        if (!(*(endptr - 1) >= 48 && *(endptr - 1) <= 57) && !std::isnan(num) && !std::isinf(num))
            ftExit();
    }
    if (*(endptr - 1) == '.')
        ftExit();
}

Convert::Convert(const Convert& obj)
{
    this->num = obj.getNum();
    this->check_num = obj.getCheckNum();
}

Convert::~Convert()
{
}

Convert& Convert::operator=(const Convert& obj)
{
    this->num = obj.getNum();
    this->check_num = obj.getCheckNum();
    return (*this);
}

double Convert::getNum() const
{
    return this->num;
}

long Convert::getCheckNum() const
{
    return this->check_num;
}

int Convert::toCheckNum(const double& num) const
{
    return static_cast<int>(num);
}

char Convert::toChar() const
{
    if (ftPrintable(num))
        return static_cast<char>(num);
    return '\0';
}

int Convert::toInt() const
{
    return static_cast<int>(num);
}

float Convert::toFloat() const
{
    return static_cast<float>(num);
}

double Convert::toDouble() const
{
    return static_cast<double>(num);
}

void Convert::printChar() const
{
    if (check_num <= INT_MIN)
    {
        std::cout << "char: impossible" << std::endl;
        return;
    }
    if (toChar() == '\0')
    {
        std::cout << "char: Non displayable" << std::endl;
        return;
    }
    std::cout << "char: '" << toChar()  << '\'' << std::endl;
}

void Convert::printInt() const
{
    if (check_num <= INT_MIN)
    {
        std::cout << "int: impossible" << std::endl;
        return;
    }
    std::cout << "int: " << toInt() << std::endl;
}

bool ftFindDot(double nb)
{
    std::string s;
    std::stringstream ss;
    size_t pos = 0;
    
    ss << nb;
    s = ss.str();
    pos = s.find('.', pos);
    if (pos == std::string::npos)
        return true;
    else
        return false;
}

void Convert::printFloat() const
{
    if (check_num <= INT_MIN)
    {
        std::cout << "float: " << std::showpos << toFloat() << 'f' << std::endl;
        return;
    }
    if (ftFindDot(toFloat()))
        std::cout << "float: " << toFloat() << ".0f" << std::endl;
    else
        std::cout << "float: " << toFloat() << 'f' << std::endl;
}

void Convert::printDouble() const
{
    if (check_num <= INT_MIN)
    {
        std::cout << "double: "<< std::showpos << toDouble() << std::endl;
        return;
    }
    if (ftFindDot(toDouble()))
        std::cout << "double: " << toDouble() << ".0" << std::endl;
    else
        std::cout << "double: " << toDouble() << std::endl;
}
