/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trerolle <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:15:31 by trerolle          #+#    #+#             */
/*   Updated: 2023/07/20 19:36:57 by trerolle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(){}

PmergeMe::~PmergeMe(){}

PmergeMe::PmergeMe(const PmergeMe &cpy)
{
	*this = cpy;
}

void	PmergeMe::fillVector(char **argv)
{
	for (; *argv; argv++)
		v.push_back(atoi(*argv));
}

void	PmergeMe::swapVector(std::vector<int> &v1, std::vector<int> &v2)
{
	int	tmp;
	size_t	i = 0;

	while (i < v2.size() || i < v2.size())
	{
		if (v2[i] > v2[i + v2.size() / 2])
		{
			tmp = v2[i];
			v2[i] = v2[i + v2.size() / 2];
			v2[i] = tmp;
			tmp = v1[i];
			v1[i] = v1[i + v1.size() / 2];
			v1[i] = tmp;

		}
		i++;
	}
}

void	PmergeMe::splitVector(std::vector<int> &v1, std::vector<int> &v2)
{
	std::vector<int>	leftA;
	std::vector<int>	rightA;
	if (v2.size() < 3)
		swapVector(v1, v2);
	else
	{
		for (size_t i = 0; i < v.size() / 2 + 1; i++)
		{
			leftA[i] = v[i];
			rightA[i] = v[i + v.size() / 2];
		}
		splitVector(leftA, rightA);
		//merge(v, leftA, rightA);
	}
}

void	PmergeMe::fordJohnsonVector(std::vector<int> v)
{
	std::vector<int>	leftSubarray(v.size() / 2 + 1);
	std::vector<int>	rightSubarray(v.size() / 2 + 1);

	std::cout << "coucou1\n";
	std::cout << v[0] << std::endl;
	for (size_t i = 0; i < v.size() / 2; i++)
	{
		if (v[i] < v[i + (v.size() / 2)])
		{
			std::cout << "coucou3\n";
			std::cout << i + (v.size()/2) << std::endl;
			leftSubarray[i] = v[i];
			std::cout << "coucou3\n";
			rightSubarray[i] = v[i + (v.size() / 2 + 1)];
		}
		else
		{
			leftSubarray[i] = v[i + (v.size() / 2 + 1)];
			rightSubarray[i] = v[i];
		}
	}

	swapVector(leftSubarray, rightSubarray);
	std::vector<int>	leftRsub;
	std::vector<int>	rightRsub;
	for (size_t i = 0; i < v.size() / 2; i++)
	{
		leftRsub[i] = rightSubarray[i];
		rightRsub[i] = rightSubarray[i + rightSubarray.size()];
	}

	splitVector(leftRsub, rightRsub);
}


void	PmergeMe::sort()
{
	fordJohnsonVector(v);
}

















































































/*
void PMergeMe::mergeVector(std::vector<int>& arr, int left, int middle, int right)
{
	int n1 = middle - left + 1;
	int n2 = right - middle;

	std::vector<int> leftSubarray(n1);
	std::vector<int> rightSubarray(n2);

	for (int i = 0; i < n1; ++i)
		leftSubarray[i] = arr[left + i];
	for (int j = 0; j < n2; ++j)
		rightSubarray[j] = arr[middle + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2) 
	{
		if (leftSubarray[i] <= rightSubarray[j]) 
		{
			arr[k] = leftSubarray[i];
			++i;
		} 
		else 
		{
			arr[k] = rightSubarray[j];
			++j;
		}
		++k;
	}

	while (i < n1) 
	{
		 arr[k] = leftSubarray[i];
		++i;
		++k;
	}

	while (j < n2) 
	{
		arr[k] = rightSubarray[j];
		++j;
		++k;
	}
	for (int i  = 0; i < right; i++)
		std::cout << arr[i] << std::endl;
	std::cout << "\n=====\n";
}

void PMergeMe::insertionSortVector(std::vector<int>& arr, int left, int right) {
	for (int i = left + 1; i <= right; ++i) {
		int key = arr[i];
		int j = i - 1;

		while (j >= left && arr[j] > key) {
			arr[j + 1] = arr[j];
			--j;
		}

		arr[j + 1] = key;
	}
}

void PMergeMe::mergeInsertionSortVector(std::vector<int>& arr, int left, int right) {
	if (left >= right)
		return;

	int middle = left + (right - left) / 2;

	if (right - left + 1 <= INSERTION_THRESHOLD) {

		insertionSort(arr, left, right);
	} else {
		mergeInsertionSort(arr, left, middle);
		mergeInsertionSort(arr, middle + 1, right);
		merge(arr, left, middle, right);
	}
}








void PMergeMe::mergeList(std::list<int>& arr, int left, int middle, int right)
{
	int n1 = middle - left + 1;
	int n2 = right - middle;

	std::list<int> leftSubarray(n1);
	std::list<int> rightSubarray(n2);

	for (int i = 0; i < n1; ++i)
		leftSubarray[i] = arr[left + i];
	for (int j = 0; j < n2; ++j)
		rightSubarray[j] = arr[middle + 1 + j];

	int i = 0, j = 0, k = left;

	while (i < n1 && j < n2) 
	{
		if (leftSubarray[i] <= rightSubarray[j]) 
		{
			arr[k] = leftSubarray[i];
			++i;
		} 
		else 
		{
			arr[k] = rightSubarray[j];
			++j;
		}
		++k;
	}

	while (i < n1) 
	{
		 arr[k] = leftSubarray[i];
		++i;
		++k;
	}

	while (j < n2) 
	{
		arr[k] = rightSubarray[j];
		++j;
		++k;
	}
	for (int i  = 0; i < right; i++)
		std::cout << arr[i] << std::endl;
	std::cout << "\n=====\n";
}

void PMergeMe::insertionSortList(std::list<int>& arr, int left, int right) 
{
	for (int i = left + 1; i <= right; ++i) {
		int key = arr[i];
		int j = i - 1;

		while (j >= left && arr[j] > key) {
			arr[j + 1] = arr[j];
			--j;
		}

		arr[j + 1] = key;
	}
}

void PMergeMe::mergeInsertionSortList(std::list<int>& arr, int left, int right) {
	if (left >= right)
		return;

	int middle = left + (right - left) / 2;

	if (right - left + 1 <= INSERTION_THRESHOLD) {
		insertionSort(arr, left, right);
	} else {
		mergeInsertionSort(arr, left, middle);
		mergeInsertionSort(arr, middle + 1, right);
		merge(arr, left, middle, right);
	}
}





void	sortArr(cahr **argv)
{
	fillList(argv);
	fillVector(argv);
	std::cout << "Before: ";
	for (; *argv; argv++)
		std::cout << *argv << " ";
	std::cout << std::endl;

*/











/*


//void	fillVector(char **argv);
	
void	PmergeMe::insertionSortList()
{
	for (std::list<int>::iterator itS = smallInts.begin(); itS != smallInts.end(); ++itS)
	{
		for (std::list<int>::iterator itB = bigInts.begin(); itB != bigInts.end(); ++itB)
		{
			if (*itS <= *itB)
			{
				bigInts.insert(itB, *itS);
				break ;
			}
		}
	}
}
void	PmergeMe::fillList(char **argv)
{
	std::clock_t	start, end;

	start = clock();
	for (; *argv; argv++)
	{
		l.push_back(atoi(*argv));
	}
	splitList(l);
	bigInts.sort();
	insertionSortList();
	for (std::list<int>::iterator it = bigInts.begin(); it != bigInts.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n";
	end = clock();
	double time = static_cast<double>(end - start) / CLOCKS_PER_SEC* 1000;
	std::cout << "Time taken by program list : " << std::fixed << time << std::setprecision(5) << " sec " << std::endl;

}


void	PmergeMe::splitList(std::list<int> l)
{
	if (l.size() <= 2)
	{
		l.sort();
		if (l.size() == 2)
		{
			smallInts.push_back(*(l.begin()));
			bigInts.push_back(*(++l.begin()));
		}
		else
			bigInts.push_back(*(l.begin()));
		return ;
	}
		
	std::list<int>				splitList1;
	std::list<int>				splitList2;
	std::list<int>::iterator	itSeparator = l.begin();
	std::advance(itSeparator, l.size() / 2);
	splitList1.splice(splitList1.begin(), l, l.begin(), itSeparator);
	splitList(splitList1);
	splitList2.splice(splitList2.begin(), l, itSeparator, l.end());
	splitList(splitList2);
}

void	PmergeMe::splitVector(std::vector<int> v)
{
	if (v.size() <= 2)
	{
		if (v.size() == 2)
		{
			if (*v.begin() > *(++v.begin()))
			{
				int	tmp = *(v.begin());
				*(v.begin()) = *(++v.begin());
				*(++v.begin()) = tmp;
			}
			smallV.push_back(*(v.begin()));
			bigV.push_back(*(++v.begin()));
		}
		else
			bigV.push_back(*v.begin());
		return ;
	}
	std::vector<int>			splitVect1;
	std::vector<int>			splitVect2;
	std::vector<int>::iterator	itSeparator = v.begin();
	


}

void	PmergeMe::fillVector(char **argv)
{
	std::clock_t	start, end;
	double			time;

	start = clock();
	for (; *argv; argv++)
	{
		v.push_back(atoi(*argv));
	}
	splitVector(l);
	for (std::list<int>::iterator it = bigInts.begin(); it != bigInts.end(); ++it)
		std::cout << *it << " ";
	std::cout << "\n";
	
	end = clock();
	time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000;

	std::cout << "Time taken by program vector : " << std::fixed << time << std::setprecision(5) << " sec " << std::endl;
		void	sortVector();
		void	sortList();
	
		void	processVector();
		void	processList();*/
