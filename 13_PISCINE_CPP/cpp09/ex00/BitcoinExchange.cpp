/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:27:27 by minkim            #+#    #+#             */
/*   Updated: 2023/05/27 13:51:12 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool isValidDate(const Date &date)
{
    return date.year >= 2009 && date.year <= 2024 && date.month >= 1 && date.month <= 12 && date.day >= 1 && date.day <= 31;
}

bool operator<(const Date &a, const Date &b)
{
    return a.year < b.year || (a.year == b.year && (a.month < b.month || (a.month == b.month && a.day < b.day)));
}

Date parseDate(const std::string &s)
{
    Date date;
    std::stringstream ss(s);
    ss >> date.year;
    ss.ignore(1);
    ss >> date.month;
    ss.ignore(1);
    ss >> date.day;
    if (!isValidDate(date))
    {
        throw std::runtime_error("Invalid date format");
    }
    return date;
}

void isValidValue(const std::string &value)
{
    for (size_t i = 0; i < value.length(); i++)
    {
        if (value[i] == '.' || value[i] == '-')
            continue;
        if (value[i] < '0' || value[i] > '9')
            throw std::runtime_error("Invalid value format");
    }
}

void parseColumn(const std::string &s)
{
    std::string date;
    std::string pipe;
    std::string value;

    std::stringstream ss(s);
    ss >> date;
    ss.ignore(1);
    ss >> pipe;
    ss.ignore(1);
    ss >> value;
    if (date != "date" || pipe != "|" || value != "value")
    {
        throw std::runtime_error("Invalid column format");
    }
}

BitcoinExchange::BitcoinExchange(const std::string &filename)
{
    loadExchangeRates(filename);
}

float BitcoinExchange::getExchangeRate(const Date &date) const
{
    std::map<Date, float>::const_iterator it = exchange_rates.upper_bound(date);
    if (it != exchange_rates.begin())
    {
        --it;
    }
    return it->second;
}

void BitcoinExchange::loadExchangeRates(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string date_str, rate_str;
        std::getline(ss, date_str, ',');
        std::getline(ss, rate_str);
        Date date = parseDate(date_str);
        float rate = static_cast<float>(std::atof(rate_str.c_str()));
        exchange_rates[date] = rate;
    }
}

void processInput(const std::string &filename, const BitcoinExchange &bitcoin_exchange)
{
    std::ifstream file(filename.c_str());
    std::string line;

    std::getline(file, line);
    parseColumn(line);
    
    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string date_str, value_str;
        std::getline(ss, date_str, '|');
        std::getline(ss, value_str);
        date_str.erase(std::remove(date_str.begin(), date_str.end(), ' '), date_str.end());
        value_str.erase(std::remove(value_str.begin(), value_str.end(), ' '), value_str.end());

        try
        {
            Date date = parseDate(date_str);
            isValidValue(value_str);
            float value = static_cast<float>(std::atof(value_str.c_str()));

            if (value < 0 || value > 1000)
            {
                std::cout << "Error: ";
                if (value < 0)
                {
                    std::cout << "not a positive number.\n";
                }
                else
                {
                    std::cout << "too large a number.\n";
                }
                continue;
            }

            float exchange_rate = bitcoin_exchange.getExchangeRate(date);
            float result = value * exchange_rate;
            std::cout << date_str << " => " << value << " = " << result << std::endl;
        }
        catch (const std::runtime_error &e)
        {
            std::cout << "Error: bad input => " << date_str << std::endl;
        }
    }
}
