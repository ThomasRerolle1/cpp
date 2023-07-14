/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:50:34 by trerolle          #+#    #+#             */
/*   Updated: 2023/07/14 15:07:30 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

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
//	char			*end;

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
		catch (std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	ifs.close();
}
/*
std::map<std::string, double>::const_iterator	closestDate(std::string date)
{
	int[3]	date, prev, next;
	std::map<std::string, double>::const_iterator	prev = _data.lower_bound(date);
	std::map<std::string, double>::const_iterator	next = _data.upper_bound(date);

	date = [ atoi(date.substr(0, 3)), atoi(date.substr(5, 6)), atoi(date.substr(8, 9))]
	prev = [ atoi(prev->first.substr(0, 3)), atoi(prev->first.substr(5, 6)), atoi(prev->first.substr(8, 9))]
	next = [ atoi(next->first.substr(0, 3)), atoi(next->first.substr(5, 6)), atoi(next->first.substr(8, 9))]
	while (prev != date || next != date)
	{
		prev = nextDay(prev);
		next = prevDay(next);
	}
	if (prev == date)
		return (prevIte);
	else
		return (nextIte);
}*/


void	BitcoinExchange::bitcoinConvertor(std::string date, double value) const
{
	std::map<std::string, double>::const_iterator	it;
	if (_data.empty())
		return ;	
	it = _data.find(date);
	if (it == _data.end())
	{
		it = _data.upper_bound(date);
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
