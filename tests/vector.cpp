
#include "../vector.hpp"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
#include <vector>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

template<typename T>
void comparisons(NAMESPACE::vector<T>& lhs, NAMESPACE::vector<T>& rhs)
{
		std::cout << "lhs == rhs ? : " << (lhs == rhs) << " ;" << std::endl;
		std::cout << "lhs != rhs ? : " << (lhs != rhs) << " ;" << std::endl;
		std::cout << "lhs > rhs ? : " << (lhs > rhs) << " ;" << std::endl;
		std::cout << "lhs <= rhs ? : " << (lhs <= rhs) << " ;" << std::endl;
		std::cout << "lhs >= rhs ? : " << (lhs >= rhs) << " ;" << std::endl;
		std::cout << "lhs < rhs ? : " << (lhs < rhs) << " ;" << std::endl << std::endl;
}

void random_fill(NAMESPACE::vector<int>& v)
{
	std::srand(unsigned(std::time(nullptr)));
	std::generate(v.begin(), v.end(), std::rand);	
	std::cout << "FILL RANDOM VECTOR ...... " << std::endl;
}

template <typename T>
void get_size(NAMESPACE::vector<T> &v)
{
	std::cout << "Vector SIZE  =  " << v.size() << std::endl
			  << std::endl;
}

template<typename T>
void print_vector(NAMESPACE::vector<T>& v)
{
	std::cout << " --> PRINT VECTOR  :" << std::endl;

	if (v.empty())
	{
		std::cout << "  --> EMPTY VECTOR" << std::endl << std::endl;
		return;
	}
	for(int i = 0; i < v.size(); i++)
	{
		if (i % 10 == 0 && i != 0)
			std::cout << std::endl;
		std::cout << v[i] << "  ";
	}
	std::cout << std::endl << " --> VECTOR SIZE = " << v.size() << std::endl;
}

NAMESPACE::vector<int> fill_vector()
{
	NAMESPACE::vector<int> vec;
	for(int i = 0; i < 50; i++)
		vec.push_back(i);
	return vec;
}

void _print(std::string str)
{
	std::cout << str << std::endl;
}

int main()
{
	std::cout << "|| ------------------------------------------------------ ||" << std::endl;
	std::cout << "|| ------------------------ VECTOR ---------------------- ||" << std::endl;
	std::cout << "|| ------------------------------------------------------ ||" << std::endl
		<< std::endl
		<< std::endl;

	{
		std::cout << std::endl;
		_print("|| ------------------ DEFAULT CONSTRUCTOR ------------------ || ");
		NAMESPACE::vector<int> vec;
		print_vector(vec);
		std::cout << std::endl;

	}

	{
		std::cout << std::endl;
		_print("|| --------------------- FILL CONSTRUCTOR ------------------ ||");
		NAMESPACE::vector<int> vec(10, 5);
		print_vector(vec);
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		_print("|| --------------------- RANGE CONSTRUCTOR ----------------- ||");
		NAMESPACE::vector<int> vec(50);
		random_fill(vec);
		print_vector(vec);
		std::cout << std::endl;
		NAMESPACE::vector<int>::iterator it = vec.begin();
		NAMESPACE::vector<int>::iterator ite = vec.end();
		NAMESPACE::vector<int> range_vec(it, ite);
		print_vector(range_vec);
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		_print("|| --------------------- COPY CONSTRUCTOR ----------------- ||");
		NAMESPACE::vector<int> vec(10, 5);
		print_vector(vec);
		std::cout << std::endl;
		NAMESPACE::vector<int> copy(vec);
		print_vector(copy);
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		_print("|| ----------------------- COPY OPERATOR ------------------- ||");
		NAMESPACE::vector<int> vec(10, 5);
		print_vector(vec);
		std::cout << std::endl;
		NAMESPACE::vector<int> copy = vec;
		print_vector(copy);
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		_print("|| -------------------------- ASSIGN ----------------------- ||");
		NAMESPACE::vector<int> vec(10, 5);
		NAMESPACE::vector<int> copy(vec);
		print_vector(vec);
		std::cout << std::endl;
		vec.assign(20, 7);
		_print("... assign(20, 7)");
		print_vector(vec);
		std::cout << std::endl;

		_print("... assign(it, ite) - avec copy");
		NAMESPACE::vector<int>::iterator it = copy.begin();
		NAMESPACE::vector<int>::iterator ite = copy.end();
		vec.assign(it, ite);
		print_vector(vec);
		std::cout << std::endl;
		
	}

	std::cout << "|| ------------------------------------------------------ ||" << std::endl;
	std::cout << "|| -------------------- ELEMENT ACCESS ------------------ ||" << std::endl;
	std::cout << "|| ------------------------------------------------------ ||" << std::endl
		<< std::endl
		<< std::endl;

	{
		_print("|| ---------------------------- AT ------------------------- ||");
		NAMESPACE::vector<int> vec(50);
		random_fill(vec);
		print_vector(vec);
		_print("... at(9) ");
		std::cout << "value at position 9 =  " << vec.at(9) << std::endl;
		std::cout << std::endl;
		try
		{
			_print("--> EXCEPTION");
			_print("... at(vec.size()) ");
			std::cout << "CATCH --> " << vec.at(vec.size()) << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}	

	{
		std::cout << std::endl;
		_print("|| ------------------------ OPERATOR[] --------------------- ||");
		NAMESPACE::vector<int> vec(50);
		random_fill(vec);
		print_vector(vec);
		_print("... vec[9] ");
		std::cout << "value at position 9 =  " << vec[9] << std::endl;
		std::cout << std::endl;
		try
		{
			_print("--> EXCEPTION");
			_print("... at(vec.size()) ");
			std::cout << "CATCH --> " << vec.at(vec.size()) << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << " out of range" << '\n';
		}
	}	

	{
		std::cout << std::endl;
		_print("|| -------------------------- FRONT ------------------------ ||");
		NAMESPACE::vector<int> vec(10);
		random_fill(vec);
		print_vector(vec);
		std::cout << "--> FRONT : " << vec.front();
		std::cout << std::endl;

		std::cout << std::endl;
		_print("|| -------------------------- BACK ------------------------ ||");
		std::cout << "--> BACK : " << vec.back();
		std::cout << std::endl;

	}

	{
		std::cout << std::endl;
		_print("|| -------------------------- DATA ------------------------ ||");
		NAMESPACE::vector<int> vec(10);
		random_fill(vec);
		print_vector(vec);
		std::cout << "--> DATA : " << *vec.data();
		std::cout << std::endl;
		std::cout << std::endl;
	}

	std::cout << "|| ------------------------------------------------------ ||" << std::endl;
	std::cout << "|| ---------------------- ITERATORS --------------------- ||" << std::endl;
	std::cout << "|| ------------------------------------------------------ ||" << std::endl
		<< std::endl
		<< std::endl;
	{
		std::cout << std::endl;
		NAMESPACE::vector<int> vec(20);
		random_fill(vec);
		print_vector(vec);
		std::cout << std::endl;

		std::cout << " --> BEGIN : " << *vec.begin() << std::endl; 
		std::cout << " --> END : " << *(vec.end()- 1) << std::endl; 
		std::cout << " --> RBEGIN : " << *vec.rbegin() << std::endl; 
		std::cout << " --> REND : " << *(vec.rend() - 1) << std::endl; 
		std::cout << std::endl;
	}

	std::cout << "|| ------------------------------------------------------- ||" << std::endl;
	std::cout << "|| ----------------------- CAPACITY ---------------------- ||" << std::endl;
	std::cout << "|| ------------------------------------------------------- ||" << std::endl
		<< std::endl;
	{
		_print("|| ------------------------- EMPTY ------------------------- ||");
		NAMESPACE::vector<int> vec;
		print_vector(vec);
		
		_print("|| ------------------- SIZE / MAX_SIZE  -------------------- ||");
		std::cout << " --> SIZE : " << vec.size() << std::endl; 
		std::cout << " --> MAX_SIZE : " << vec.max_size() << std::endl; 
		std::cout << std::endl;

		_print("... filling vector");
		std::cout << std::endl;
		vec = fill_vector();
		print_vector(vec);
		std::cout << " --> MAX_SIZE : " << vec.max_size() << std::endl; 
		std::cout << std::endl;

		_print("|| ------------------- RESERVE / CAPACITY ------------------ ||");
		_print(" ... reserve(100)");
		vec.reserve(100);
		std::cout << " --> CAPACITY : " << vec.capacity() << std::endl; 
		std::cout << std::endl;


		_print(" ... reserve(200)");
		vec.reserve(200);
		std::cout << " --> CAPACITY : " << vec.capacity() << std::endl; 
		std::cout << std::endl;

		try
		{
			_print("--> EXCEPTION");
			_print("... reserve(max_size() + 1) ");
			vec.reserve(vec.max_size() + 1);
		}
		catch(const std::exception& e)
		{
			std::cout << e.what() << " reserve : length exception" << '\n';
		}
	}

	std::cout << "|| ------------------------------------------------------- ||" << std::endl;
	std::cout << "|| ----------------------- MODIFIERS --------------------- ||" << std::endl;
	std::cout << "|| ------------------------------------------------------- ||" << std::endl
		<< std::endl;
	{
		_print("|| ------------------------- EMPTY ------------------------- ||");
		NAMESPACE::vector<int> vec;
		vec = fill_vector();
		print_vector(vec);
		_print(" ... clear()");
		vec.clear();
		print_vector(vec);
		std::cout << std::endl;

		_print("|| ------------------------- INSERT ------------------------ ||");

		_print(" ... insert(vec.begin(), 2)");
		vec.insert(vec.begin(), 2);
		print_vector(vec);
		std::cout << std::endl;

		NAMESPACE::vector<int> vec_to_insert = fill_vector();
		_print(" ... insert(vec.begin() + 1, vec_to_insert.begin(), vec_to_insert.end())");
		vec.insert(vec.begin() + 1, vec_to_insert.begin(), vec_to_insert.end());
		print_vector(vec);
		std::cout << std::endl;

		_print(" ... insert(vec.begin() + 10, 10, 3)");
		vec.insert(vec.begin() + 10, 10, 3);
		print_vector(vec);
		std::cout << std::endl;

		_print("|| ------------------------- ERASE ------------------------- ||");
		_print(" ... erase(vec.begin())");
		vec.erase(vec.begin());
		print_vector(vec);
		std::cout << std::endl;

		_print(" ... erase(vec.begin() + 9, vec.begin() + 19)");
		vec.erase(vec.begin() + 9, vec.begin() + 19);
		print_vector(vec);
		std::cout << std::endl;
	}

	{
		_print("|| ----------------------- PUSH / POP ---------------------- ||");
		NAMESPACE::vector<int> vec;
		_print(" ... push_back()");
		for (int i = 0; i < 10; i++)
			vec.push_back(i);
		print_vector(vec);
		std::cout << std::endl;

		_print(" ... pop_back()");
		vec.pop_back();
		print_vector(vec);
		std::cout << std::endl;

		_print("|| ------------------------ RESIZE ------------------------- ||");
		_print(" ... resize() with new_size > size()");
		vec.resize(25, 5);
		print_vector(vec);
		std::cout << std::endl;

		_print(" ... resize() with new_size < size()");
		vec.resize(5, 5);
		print_vector(vec);
		std::cout << std::endl;
	}

	{
		_print("|| ------------------------- SWAP -------------------------- ||");
		NAMESPACE::vector<int> v1 = fill_vector();
		NAMESPACE::vector<int> v2(10);
		random_fill(v2);

		std::cout << std::endl;
		_print(" --> vector 1");
		print_vector(v1);

		std::cout << std::endl;
		_print(" --> vector 2");
		print_vector(v2);

		std::cout << std::endl;
		_print(" ... v1.swap(v2)");
		v1.swap(v2);

		std::cout << std::endl;
		_print(" --> vector 1");
		print_vector(v1);

		std::cout << std::endl;
		_print(" --> vector 2");
		print_vector(v2);
	}

	std::cout << "|| ------------------------------------------------------- ||" << std::endl;
	std::cout << "|| ----------------------- COMPARISONS ------------------- ||" << std::endl;
	std::cout << "|| ------------------------------------------------------- ||" << std::endl
		<< std::endl;

	{

		NAMESPACE::vector<int> lhs(3, 5);
		NAMESPACE::vector<int> rhs(3, 5);

		_print(" --> LHS");
		print_vector(lhs);
		std::cout << std::endl;

		_print(" --> RHS");
		print_vector(rhs);
		std::cout << std::endl;

		comparisons(lhs, rhs);
		std::cout << std::endl;

		_print(" ... lhs.push_back(2)");
		lhs.push_back(2);
		comparisons(lhs, rhs);
		std::cout << std::endl;

		_print(" ... swap(lhs, rhs)");
		swap(lhs, rhs);
		comparisons(lhs, rhs);
		std::cout << std::endl;
	}
}