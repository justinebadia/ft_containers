#include <utility>
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>

#include "../stack.hpp"

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

template <typename T>
void fill_stack(NAMESPACE::stack<T> &s)
{
	std::cout << "|| -------------------- FILL STACK ---------------------- ||" << std::endl;
	for (int i = 11; i != 0; i--)
	{
		s.push(i);
		std::cout << i << " ";
	}
	std::cout << std::endl
			  << std::endl;
}

template <typename T>
void get_size(NAMESPACE::stack<T> &s)
{
	std::cout << "STACK SIZE  =  " << s.size() << std::endl
			  << std::endl;
}

template <typename T>
void print_stack(NAMESPACE::stack<T> &s)
{

	get_size(s);
	std::cout << "|| ------------------- PRINT STACK ---------------------- ||" << std::endl
			  << std::endl;
	if (s.empty())
	{
		std::cout << "EMPTY STACK" << std::endl
				  << std::endl;
		return;
	}
	int i = 0;
	while (!s.empty())
	{
		std::cout << i++ << "   | " << s.top() << std::endl;
		s.pop();
	}
	std::cout << std::endl;
	std::cout << std::endl;
	return;
}

int main()
{
	{
		std::cout << "|| ------------------------------------------------------ ||" << std::endl;
		std::cout << "|| ------------------------ STACK ----------------------- ||" << std::endl;
		std::cout << "|| ------------------------------------------------------ ||" << std::endl
				  << std::endl
				  << std::endl;

		NAMESPACE::stack<int> _stack;
		NAMESPACE::stack<int> _stack2;

		print_stack(_stack);
		fill_stack(_stack);
		std::cout << "|| ------------------- stack2 = stack ------------------- ||" << std::endl;
		_stack2 = _stack;

		print_stack(_stack);
		print_stack(_stack2);
	}

	{
		NAMESPACE::stack<int> _s1;
		NAMESPACE::stack<int> _s2;

		fill_stack(_s1);
		std::cout << "_s1 = _s2;" << std::endl;
		_s2 = _s1;

		std::cout << "|| ------------------------------------------------------ ||" << std::endl;
		std::cout << "|| --------------------- COMPARISONS -------------------- ||" << std::endl;
		std::cout << "|| ------------------------------------------------------ ||" << std::endl;

		std::cout << "_s1 == _s2 ? : " << (_s1 == _s2) << " ;" << std::endl;
		std::cout << "_s1 != _s2 ? : " << (_s1 != _s2) << " ;" << std::endl;
		std::cout << "_s1 > _s2 ? : " << (_s1 > _s2) << " ;" << std::endl;
		std::cout << "_s1 <= _s2 ? : " << (_s1 <= _s2) << " ;" << std::endl;
		std::cout << "_s1 >= _s2 ? : " << (_s1 >= _s2) << " ;" << std::endl;
		std::cout << "_s1 < _s2 ? : " << (_s1 < _s2) << " ;" << std::endl << std::endl;

		_s1.push(12);
		std::cout << std::endl << "-- push 12 in _s1 -- " << std::endl << std::endl;
		std::cout << "_s1 == _s2 ? : " << (_s1 == _s2) << " ;" << std::endl;
		std::cout << "_s1 != _s2 ? : " << (_s1 != _s2) << " ;" << std::endl;
		std::cout << "_s1 > _s2 ? : " << (_s1 > _s2) << " ;" << std::endl;
		std::cout << "_s1 <= _s2 ? : " << (_s1 <= _s2) << " ;" << std::endl;
		std::cout << "_s1 >= _s2 ? : " << (_s1 >= _s2) << " ;" << std::endl;
		std::cout << "_s1 < _s2 ? : " << (_s1 < _s2) << " ;" << std::endl;
	}

		std::cout << "|| ------------------------------------------------------ ||" << std::endl;
		std::cout << "|| --------------------- CONST STACK --------------------- ||" << std::endl;
		std::cout << "|| ------------------------------------------------------ ||" << std::endl
				  << std::endl
				  << std::endl;
		{
			
			NAMESPACE::stack<std::string> _s2;
			_s2.push("salut");
			_s2.push("ca");
			_s2.push("va");
			const NAMESPACE::stack<std::string> _s1 = _s2;
			
			print_stack(_s2);
			
			std::cout << " _s1 = _s2 " << std::endl;
			std::cout << "const stack _s1 top() = " << _s1.top() << std::endl;
		}
}