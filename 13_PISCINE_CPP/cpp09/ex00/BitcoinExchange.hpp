/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 13:27:23 by minkim            #+#    #+#             */
/*   Updated: 2023/05/06 16:56:29 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <map>
# include <algorithm>
# include <ctime>

struct Date
{
    int year, month, day;
};

Date parseDate(const std::string &s);
void parseColumn(const std::string &s);

class BitcoinExchange
{
private:
    std::map<Date, float> exchange_rates;

public:
    BitcoinExchange(const std::string &filename);
    float getExchangeRate(const Date &date) const;
    void loadExchangeRates(const std::string &filename);
};

void processInput(const std::string &filename, const BitcoinExchange &bitcoin_exchange);

#endif
