/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:16:06 by trerolle          #+#    #+#             */
/*   Updated: 2023/07/20 19:23:22 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include <bits/stdc++.h>
#include "PmergeMe.hpp"

class	BadArgumentException: public std::exception
{
	public:
		virtual const char * what() const throw()
		{
			return ("Error: Bad Arguments, must be a positive integer");
		}
};

class	NotPositiveIntegerException: public std::exception
{
	public:
		virtual const char * what() const throw()
		{
			return ("Error: Not a positive integer");
		}
};

void	isNumber(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			throw BadArgumentException();
		str++;
	}
}

void	isInt(char *str)
{
	double	n;

	n = strtod(str, 0);
	if (n < 0 || n > INT_MAX)
		throw NotPositiveIntegerException();
}

void	checkArgs(char **argv)
{
	while (*argv)
	{
		isNumber(*argv);
		isInt(*argv);
		argv++;
	}
}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cout << "Too few arguments\n";
		return (0);
	}
	try 
	{
		time_t	start, end;
		time(&start);
		(void)argv;
		checkArgs(argv + 1);
		PmergeMe	p;
		p.fillVector(argv + 1);
		p.sort();
		time(&end);
		double time_taken = double(end - start);
		std::cout << "Time taken by program is : " << std::fixed << time_taken << std::setprecision(5) << " sec " << std::endl;
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
    return 0;
}
