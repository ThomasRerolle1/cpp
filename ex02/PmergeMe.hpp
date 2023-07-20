/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:15:36 by trerolle          #+#    #+#             */
/*   Updated: 2023/07/20 19:23:11 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <time.h>
#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <exception>

const int INSERTION_THRESHOLD = 2; // Threshold for switching to insertion sort

class	PmergeMe
{
	public:
		//constructors
		
		PmergeMe();
		PmergeMe(PmergeMe const &cpy);

		//destructor

		~PmergeMe();

		//functions
		

		void	fillVector(char **argv);
		void	swapVector(std::vector<int> &v1, std::vector<int> &v2);
		void	splitVector(std::vector<int> &v1, std::vector<int> &v2);
		void	fordJohnsonVector(std::vector<int> v);
		void	sort();


	private:
		std::vector<int>	v;
		std::list<int>		l;
		std::list<int>		smallInts;
		std::list<int>		bigInts;
};
#endif
