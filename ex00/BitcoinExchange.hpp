/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:21:40 by trerolle          #+#    #+#             */
/*   Updated: 2023/07/18 21:07:08 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	BITCOINEXCHANGE_HPP
#define	BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>


//operator overloads
//


class	BitcoinExchange
{
	public:
		//Constructors
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &rhs);

		//Destructor
		~BitcoinExchange();

		//overload operators
		BitcoinExchange const &	operator=(BitcoinExchange const &rhs);	

			//functions
		void											displayBTC(std::string file) const;
		void											bitcoinConvertor(std::string date, double value) const;
		std::map<std::string, double> 					fromTextToMap(std::string fileName);
		std::map<std::string, double>::const_iterator	closestDate(std::string date) const;


		//getters
		std::map<std::string, double> const &	getData() const;
		
		//struct date
		//
		typedef	struct s_date
		{
			int	year;
			int	month;
			int	day;
	
			//operator overloads
			bool	operator==(s_date &date);
			bool	operator<(s_date const &rhs);
			bool	operator<=(s_date const &rhs);
			bool	operator>(s_date const &rhs);
			bool	operator>=(s_date const &rhs);
			void	operator=(std::string str);
			s_date	operator++(int);
			s_date	operator--(int);
		} t_date;

		//exceptions
		
		class	NegativevalueException: public std::exception
		{
			public:
				virtual const char * what() const throw()
				{
					return ("Error: Value is negative");
				}
		};
		
		
		class	FileNotFoundException: public std::exception
		{
			public:
				virtual const char * what() const throw()
				{
					return ("Error: Cannot open the file");
				}
		};
		
		class	BadDateException: public std::exception
		{
			public:
				virtual const char * what() const throw()
				{
					return ("Error: Bad input");
				}
		};
		
		
		class	TooLargeNumberException: public std::exception
		{
			public:
				virtual const char * what() const throw()
				{
					return ("Error: Too large number");
				}
		};

	private:
		std::map<std::string, double>	_data;
		static t_date					_date;



};

#endif
