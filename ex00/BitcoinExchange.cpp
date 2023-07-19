/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:50:34 by trerolle          #+#    #+#             */
/*   Updated: 2023/07/19 18:55:55 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <unistd.h>
	//constructors
BitcoinExchange::BitcoinExchange()
{
	try
	{
		_data = fromTextToMap("Data.csv");
	}
	catch (BitcoinExchange::FileNotFoundException &e)
	{
		std::cerr << e.what() << std::endl;
	}
}


		
BitcoinExchange::BitcoinExchange(BitcoinExchange const &rhs)
{
	*this = rhs;
}
		

		//Destructor
		
BitcoinExchange::~BitcoinExchange()
{
}

		//overload operators
		
BitcoinExchange const &	BitcoinExchange::operator=(BitcoinExchange const &rhs)
{
	if (this == &rhs)
		return (*this);
	_data = rhs.getData();
	return (*this);
}


		//functions

void	BitcoinExchange::displayBTC(std::string file) const
{
	std::ifstream	ifs;
	std::string		line;

	if (_data.empty())
		return ;
	ifs.open(file, std::ifstream::in);
	if (!ifs.is_open())
		throw BitcoinExchange::FileNotFoundException();
	std::getline(ifs, line);
	while (std::getline(ifs, line))
	{
		try
		{
			if (line.length() < 11)
				throw BitcoinExchange::BadDateException();
			bitcoinConvertor(line.substr(0, 10), strtod(line.substr(12, line.length()).c_str(), 0));
		}
		catch (BitcoinExchange::BadDateException &e)
		{
			std::cerr << e.what() << " => " << line.substr(0, 10) << std::endl;
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	ifs.close();
}

std::map<std::string, double>::const_iterator	BitcoinExchange::closestDate(std::string date) const
{
	BitcoinExchange::t_date	date1, prev, next;
	std::map<std::string, double>::const_iterator	nextIt = _data.upper_bound(date);
	std::map<std::string, double>::const_iterator	prevIt = _data.upper_bound(date);

	if (prevIt == _data.begin() || prevIt == _data.end())
		return (_data.end());
	--prevIt;
	prev = prevIt->first;
	next = nextIt->first;
	date1 = date;
	date1++;
	date1--;

	while (!(prev == date1) && !(next == date1))
	{
		prev++;
		next--;
	}
	if (next == date1)
		return (nextIt);
	else
		return (prevIt);
}

void	BitcoinExchange::bitcoinConvertor(std::string date, double value) const
{
	std::map<std::string, double>::const_iterator	it;
	if (_data.empty())
		return ;	
	it = _data.find(date);
	if (it == _data.end())
	{
		it = closestDate(date);
	}
	if (it == _data.end())
		throw BitcoinExchange::BadDateException();
	if (value < 0)
		throw BitcoinExchange::NegativevalueException();
	if (value > static_cast<double>(INT_MAX))
		throw BitcoinExchange::TooLargeNumberException();
	std::cout << date << " => " << value << " = " << value * it->second << std::endl;
}

		
std::map<std::string, double>	BitcoinExchange::fromTextToMap(std::string fileName)
{
	std::ifstream					ifs;
	std::map<std::string, double>	dataMap;
	std::string						line;
	char							*end;

	ifs.open(fileName, std::ifstream::in);	
	if (!ifs.is_open())
		throw (BitcoinExchange::FileNotFoundException());
	std::getline(ifs, line);
	while (std::getline(ifs, line))
	{
		try
		{
			dataMap[line.substr(0, 10)] = strtod(line.substr(11, line.length()).c_str(), &end);
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	ifs.close();
	return (dataMap);
}

//getters


std::map<std::string, double> const &	BitcoinExchange::getData() const
{
	return (_data);
}



//Date overloads



bool	BitcoinExchange::s_date::operator==(BitcoinExchange::s_date &rhs)
{
	if (year == rhs.year && month == rhs.month && day == rhs.day)
		return (true);
	return (false);
}
		
bool	BitcoinExchange::s_date::operator<(BitcoinExchange::t_date const &rhs)
{
	if (year < rhs.year || (year == rhs.year && month < rhs.month) || (year == rhs.year && month == rhs.month && day < rhs.day))
		return (true);
	return (false);
}

bool	BitcoinExchange::s_date::operator>(BitcoinExchange::t_date const &rhs)
{
	if (year > rhs.year || (year == rhs.year && month > rhs.month) || (year == rhs.year && month == rhs.month && day > rhs.day))
		return (true);
	return (false);
}

bool	BitcoinExchange::s_date::operator<=(BitcoinExchange::t_date const &rhs)
{
	if (year <= rhs.year || (year == rhs.year && month <= rhs.month) || (year == rhs.year && month == rhs.month && day <= rhs.day))
		return (true);
	return (false);
}

bool	BitcoinExchange::s_date::operator>=(BitcoinExchange::t_date const &rhs)
{
	if (year >= rhs.year || (year == rhs.year && month >= rhs.month) || (year == rhs.year && month == rhs.month && day >= rhs.day))
		return (true);
	return (false);
}

void	BitcoinExchange::s_date::operator=(std::string str)
{

	if (str.length() < 10)
		throw BitcoinExchange::BadDateException();
 	year = atoi(str.substr(0, 4).c_str());
	month = atoi(str.substr(5, 6).c_str());
	day = atoi(str.substr(8, 9).c_str());
}



BitcoinExchange::s_date	BitcoinExchange::t_date::operator++(int)
{
	switch (month)
	{
		case 1: case 3: case 5: case 7: case 8: case 10:
			if (day > 31)
				throw BitcoinExchange::BadDateException();
			if (day == 31)
			{
				month++;
				day = 1;
			}
			else
				day++;
			break;
		case 4: case 6: case 9: case 11:
			if (day > 30)
				throw BitcoinExchange::BadDateException();
			if (day == 30)
			{
				month++;
				day = 1;
			}
			else
				day++;
			break;
		case 12:
			if (day == 31)
			{
				day = 1;
				month = 1;
				year++;
			}
			else
				day++;
			break;
		case 2:
			if (year % 4 && day > 28)
				throw BitcoinExchange::BadDateException();
			if (year % 4 && day == 28)
			{
				month++;
				day = 1;
			}
			else if (day == 29)
			{
				month++;
				day = 1;
			}
			else
				day++;
			break;
		default:
			throw BitcoinExchange::BadDateException();
	}
	return (*this);
}

BitcoinExchange::s_date	BitcoinExchange::t_date::operator--(int)
{
	switch (month)
	{
		case 5: case  7: case 10: case 12:
			if (day == 1)
			{
				month--;
				day = 30;
			}
			else
				day--;
			break;
		case 2: case 4: case 6: case 8: case 9: case 11:
			if (day == 1)
			{
				month--;
				day = 31;
			}
			else
				day--;
			break;
		case 1:
			if (day == 1)
			{
				day = 31;
				month = 12;
				year--;
			}
			else
				day--;
			break;
		case 3:
			if (!year % 4 && day == 1)
			{
				month--;
				day = 29;
			}
			else if (day == 1)
			{
				month--;
				day = 28;
			}
			else
				day--;
			break;
		default:
			throw BitcoinExchange::BadDateException();
	}
	return (*this);
}



