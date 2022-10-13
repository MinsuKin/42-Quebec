/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minkim <minkim@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:51:30 by minkim            #+#    #+#             */
/*   Updated: 2022/10/13 14:05:37 by minkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>
#include <iostream>
#include "Account.hpp"

int	Account::_nbAccounts;
int	Account::_totalAmount;
int	Account::_totalNbDeposits;
int	Account::_totalNbWithdrawals;

void	Account::_displayTimestamp( void )
{
	time_t	ts;
	char	buf[16];

	time(&ts);
	strftime(buf, sizeof(buf), "%Y%m%d_%H%M%S", localtime(&ts));
	std::cout << "[" << buf << "]";
}

Account::Account( int initial_deposit )
{
	_accountIndex = _nbAccounts;
	_amount = initial_deposit;
	_nbDeposits = 0;
	_nbWithdrawals = 0;
	_nbAccounts++;
	_totalAmount = _totalAmount + initial_deposit;
	_displayTimestamp();
	std::cout	<< " index:" << _accountIndex \
				<< ";amount:" << _amount \
				<< ";created" << std::endl;
}

int	Account::getNbAccounts( void )
{
	return (_nbAccounts);
}

int	Account::getTotalAmount( void )
{
	return (_totalAmount);
}

int	Account::getNbDeposits( void )
{
	return (_totalNbDeposits);
}

int	Account::getNbWithdrawals( void )
{
	return (_totalNbWithdrawals);
}

void	Account::displayAccountsInfos(void)
{
	_displayTimestamp();
	std::cout	<< " accounts:" << getNbAccounts()\
				<< ";total:" << getTotalAmount()\
				<< ";deposits:" << getNbDeposits()\
				<< ";withdrawals:" << getNbWithdrawals() << std::endl;
}

void	Account::displayStatus(void) const
{
	_displayTimestamp();
	std::cout	<< " index:" << _accountIndex \
				<< ";amount:" << _amount \
				<< ";deposits:" << _nbDeposits \
				<< ";withdrawals:" << _nbWithdrawals << std::endl;
}

void	Account::makeDeposit(int deposit)
{
	_amount = _amount + deposit;
	_totalAmount = _totalAmount + deposit;
	_nbDeposits++;
	_totalNbDeposits++;
	_displayTimestamp();
	std::cout	<< " index:" << _accountIndex \
				<< ";p_amount:" << _amount - deposit \
				<< ";deposit:" << deposit \
				<< ";amount:" << _amount \
				<< ";nb_deposits:" << _nbDeposits << std::endl;
}

int	Account::checkAmount( void ) const
{
	if (_amount < 0)
		return (0);
	return (1);
}

bool	Account::makeWithdrawal(int withdrawal)
{
	bool	result;

	_amount = _amount - withdrawal;
	_displayTimestamp();
	std::cout	<< " index:" << _accountIndex \
				<< ";p_amount:" << _amount + withdrawal;
	if (checkAmount())
	{
		result = true;
		_totalAmount = _totalAmount - withdrawal;
		_nbWithdrawals++;
		_totalNbWithdrawals++;
		std::cout	<< ";withdrawal:" << withdrawal \
					<< ";amount:" << _amount \
					<< ";nb_withdrawals:" << _nbWithdrawals;
	}
	else
	{
		result = false;
		_amount = _amount + withdrawal;
		std::cout << ";withdrawal:refused";
	}
	std::cout << std::endl;
	return (result);
}

Account::~Account( void )
{
	_nbAccounts--;
	_totalAmount = _totalAmount - _amount;
	_totalNbDeposits = _totalNbDeposits - _nbDeposits;
	_totalNbWithdrawals = _totalNbWithdrawals - _nbWithdrawals;
	_displayTimestamp();
	std::cout	<< " index:" << _accountIndex \
				<< ";amount:" << _amount \
				<< ";closed" << std::endl;
}
