
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <map>

#include "../map.hpp"

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

template <typename Key, typename T>
NAMESPACE::map<Key, T> build_map() {

    NAMESPACE::map<Key, T> m;
    for (size_t i = 0; i < static_cast<size_t>(rand() % 100) + 10; ++i)
        m.insert(NAMESPACE::make_pair(i, rand() % 25000));

    return m;
}

template<typename Key, typename T>
void comparisons(NAMESPACE::map<Key, T>& lhs, NAMESPACE::map<Key, T>& rhs)
{
		std::cout << "lhs == rhs ? : " << (lhs == rhs) << " ;" << std::endl;
		std::cout << "lhs != rhs ? : " << (lhs != rhs) << " ;" << std::endl;
		std::cout << "lhs > rhs ? : " << (lhs > rhs) << " ;" << std::endl;
		std::cout << "lhs <= rhs ? : " << (lhs <= rhs) << " ;" << std::endl;
		std::cout << "lhs >= rhs ? : " << (lhs >= rhs) << " ;" << std::endl;
		std::cout << "lhs < rhs ? : " << (lhs < rhs) << " ;" << std::endl << std::endl;
}


template<typename Key, typename T>
void print_map(NAMESPACE::map<Key, T>& map)
{
	std::cout << " --> PRINT MAP  :" << std::endl;
	if (map.empty())
	{
		std::cout << "  --> EMPTY MAP" << std::endl << std::endl;
		return;
	}

	typename NAMESPACE::map<Key, T>::iterator it = map.begin();
	typename NAMESPACE::map<Key, T>::iterator ite = map.end();

	for(; it!= ite; it++)
		std::cout << "KEY = " << it->first << "  |  VALUE = " << it->second << " " << std::endl;

	std::cout << std::endl << " --> MAP SIZE = " << map.size() << std::endl;
}


void _print(std::string str)
{
	std::cout << str << std::endl;
}

int main()
{
	std::cout << "|| ------------------------------------------------------ ||" << std::endl;
	std::cout << "|| ------------------------- MAP ------------------------ ||" << std::endl;
	std::cout << "|| ------------------------------------------------------ ||" << std::endl
		<< std::endl
		<< std::endl;
	
	{
		std::cout << std::endl;
		_print("|| ------------------ DEFAULT CONSTRUCTOR ------------------ || ");

		NAMESPACE::map<int, int> m;
		print_map(m);
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		_print("|| --------------------- COPY CONSTRUCTOR ------------------ ||");
		NAMESPACE::map<int, int> m = build_map<int, int>();
		NAMESPACE::map<int, int> m1(m);
		print_map(m1);
		std::cout << std::endl;
		
	}

		{
		std::cout << std::endl;
		_print("|| --------------------- RANGE CONSTRUCTOR ----------------- ||");
		
		NAMESPACE::map<int, int> map = build_map<int, int>();
		NAMESPACE::map<int, int>::iterator it = map.begin();
		NAMESPACE::map<int, int>::iterator ite = map.end();
		std::cout << std::endl;
	
		NAMESPACE::map<int, int> map_range(it, ite);
		print_map(map_range);
		
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		_print("|| ----------------------- COPY OPERATOR ------------------- ||");
		NAMESPACE::map<int, int> map = build_map<int, int>();
		print_map(map);
		std::cout << std::endl;
		NAMESPACE::map<int, int> map_copy = map;
		print_map(map_copy);
		std::cout << std::endl;
	}

	{
		std::cout << std::endl;
		_print("|| ----------------------- GET ALLOCATOR ------------------- ||");
		 int psize;

        NAMESPACE::map<char, int> map;
        NAMESPACE::pair<const char, int>* p;

        p = map.get_allocator().allocate(5);

        psize = sizeof(std::map<char, int>::value_type) * 5;

        std::cout << "ALLOC " << psize << " bytes." << std::endl;

        map.get_allocator().deallocate(p, 5);
		std::cout << std::endl;
	}

	std::cout << "|| ------------------------------------------------------ ||" << std::endl;
	std::cout << "|| ---------------------- ITERATORS --------------------- ||" << std::endl;
	std::cout << "|| ------------------------------------------------------ ||" << std::endl
		<< std::endl
		<< std::endl;
	{
		NAMESPACE::map<int, int> map = build_map<int, int>();
		print_map(map);
		NAMESPACE::map<int, int>::iterator it = map.begin();
		NAMESPACE::map<int, int>::iterator ite = map.end();
		ite--;
		NAMESPACE::map<int, int>::reverse_iterator rit = map.rbegin();
		NAMESPACE::map<int, int>::reverse_iterator rite = map.rend();
		rite--;
		std::cout << std::endl;

		std::cout << " --> BEGIN : " << it->second << std::endl; 
		std::cout << " --> END : " << ite->second << std::endl; 
		std::cout << " --> RBEGIN : " << rit->second << std::endl; 
		std::cout << " --> REND : " << rite->second << std::endl; 
		std::cout << std::endl;
	}
	std::cout << "|| ------------------------------------------------------- ||" << std::endl;
	std::cout << "|| --------------------- ELEMENT ACCESS ------------------ ||" << std::endl;
	std::cout << "|| ------------------------------------------------------- ||" << std::endl
		<< std::endl;
	{
		NAMESPACE::map<int, int> map = build_map<int, int>();
		print_map(map);
		_print("|| ---------------------------- AT ------------------------- ||");
		try {
			std::cout << "value at position 2 =  " << map.at(2) << std::endl;
			std::cout << "value at position 5 =  " << map.at(5) << std::endl;
			std::cout << "value at position 15 =  " << map.at(15) << std::endl;
			std::cout << "value at position 100 =  " << map.at(100) << std::endl;
		}
		catch(std::exception& e){
			std::cout << e.what() << '\n';
		}
		_print("|| ------------------------ OPERATOR[] --------------------- ||");
		print_map(map);
		try {
			std::cout << "value at position [2] =  " << map[2] << std::endl;
			std::cout << "value at position [5] =  " << map[5] << std::endl;
			std::cout << "value at position [15] =  " << map[15] << std::endl;
			std::cout << "value at position [100]=  " << map[100] << std::endl;
		}
		catch(std::exception& e){
			std::cout << e.what() << '\n';
		}
		print_map(map);

	}

	std::cout << "|| ------------------------------------------------------- ||" << std::endl;
	std::cout << "|| ----------------------- MODIFIERS --------------------- ||" << std::endl;
	std::cout << "|| ------------------------------------------------------- ||" << std::endl
		<< std::endl;
	{
			NAMESPACE::map<int, int> map = build_map<int, int>();
			print_map(map);
		_print("|| ------------------------- CLEAR ------------------------- ||");
			map.clear();
			print_map(map);
			std::cout << std::endl;
		_print("|| ------------------------- ERASE ------------------------- ||");

			map = build_map<int, int>();
			NAMESPACE::map<int, int>::iterator it = map.begin();
			print_map(map);
			std::cout << std::endl;
			
			_print("--> erase begin()");
			map.erase(it);
			print_map(map);
			std::cout << std::endl;
			
			_print("--> erase key 12");
			map.erase(12);
			print_map(map);
			std::cout << std::endl;

			it = map.begin();
			NAMESPACE::map<int, int>::iterator ite = map.end();
			map.erase(it, ite);
			_print("--> erase(begin(),end())");
			print_map(map);
			std::cout << std::endl;
	}
		_print("|| ------------------------- INSERT ------------------------ ||");
		{
			_print("--> insert(value_type)");
			NAMESPACE::map<int, std::string> map;
			map.insert(NAMESPACE::pair<int, std::string>(22, "ca"));
			map.insert(NAMESPACE::pair<int, std::string>(26, "va"));
			map.insert(NAMESPACE::pair<int, std::string>(12, "salut"));
			map.insert(NAMESPACE::pair<int, std::string>(1, "Tchuss"));
			map.insert(NAMESPACE::pair<int, std::string>(1, "Test"));
			print_map(map);
			std::cout << std::endl;

			_print("--> insert(iterator, value_type)");
			NAMESPACE::map<int, std::string>::iterator it = map.begin();
			map.insert(it, NAMESPACE::pair<int, std::string>(5, "Oh"));
			print_map(map);
			std::cout << std::endl;

			_print("--> insert(iterator, iterator)");
			NAMESPACE::map<int, std::string> map2;
			map2.insert(map.begin(), map.end());
			print_map(map);
			std::cout << std::endl;
		
		_print("|| ------------------------- SWAP -------------------------- ||");
			NAMESPACE::map<int, std::string> map3;
			
			map3.insert(NAMESPACE::pair<int, std::string>(22, "come"));
			map3.insert(NAMESPACE::pair<int, std::string>(26, "va"));
			map3.insert(NAMESPACE::pair<int, std::string>(12, "Ciao"));
			map3.insert(NAMESPACE::pair<int, std::string>(1, "Buongiorno"));
			map3.insert(NAMESPACE::pair<int, std::string>(1, "Hop"));
			
		_print("-->italien");
			print_map(map3);
		_print("-->swap");
			map3.swap(map2);
		_print("-->francais");
			print_map(map3);
			std::cout << std::endl;
		}


	std::cout << "|| ------------------------------------------------------- ||" << std::endl;
	std::cout << "|| ----------------------- LOOK UP ----------------------- ||" << std::endl;
	std::cout << "|| ------------------------------------------------------- ||" << std::endl
		<< std::endl;
	{
		NAMESPACE::map<int, std::string> map;
			map.insert(NAMESPACE::pair<int, std::string>(22, "ca"));
			map.insert(NAMESPACE::pair<int, std::string>(26, "va"));
			map.insert(NAMESPACE::pair<int, std::string>(12, "salut"));
			map.insert(NAMESPACE::pair<int, std::string>(1, "Tchuss"));
			map.insert(NAMESPACE::pair<int, std::string>(1, "Test"));
			print_map(map);
		_print("|| ------------------------- COUNT ------------------------- ||");
			std::cout << "--> count 3 ? : " << map.count(3) << std::endl;
			std::cout << "--> count 1 ? : " << map.count(1) << std::endl;
			std::cout << "--> count 22 ? : " << map.count(22) << std::endl;

		_print("|| ------------------------- FIND ------------------------- ||");
			bool find = false;
			NAMESPACE::map<int, std::string>::iterator it;
			it = map.find(3);
			if (it != map.end())
				find = true;
			std::cout << "--> find 3 ? : " << find << std::endl;

			it = map.find(1);
			if (it != map.end())
				find = true;
			std::cout << "--> find 1 ? : " << find << std::endl;

			it = map.find(22);
			if (it != map.end())
				find = true;
			std::cout << "--> find 22 ? : " << find << std::endl;


		
	}
		_print("|| ------------------------- LOWER_BOUND ------------------------ ||");
		{
			 _print("Returns an iterator pointing to the first element that is not less than\n (i.e. greater or equal to) key");
			NAMESPACE::map<int, std::string> map;
			map.insert(NAMESPACE::pair<int, std::string>(22, "ca"));
			map.insert(NAMESPACE::pair<int, std::string>(24, "test"));
			map.insert(NAMESPACE::pair<int, std::string>(26, "va"));
			map.insert(NAMESPACE::pair<int, std::string>(12, "salut"));
			map.insert(NAMESPACE::pair<int, std::string>(1, "Tchuss"));
			map.insert(NAMESPACE::pair<int, std::string>(1, "Test"));
			map.insert(NAMESPACE::pair<int, std::string>(19, "je"));
			map.insert(NAMESPACE::pair<int, std::string>(100, "suis"));
			map.insert(NAMESPACE::pair<int, std::string>(31, "bleue"));
			print_map(map);

			std::cout << "LOWER BOUND DE 22 est -->  " << map.lower_bound(22)->first << " ! \n";
			std::cout << "LOWER BOUND DE 42 est -->  " << map.lower_bound(42)->first << " ! \n";
			std::cout << "LOWER BOUND DE 1 est -->  " << map.lower_bound(1)->first << " ! \n";
			std::cout << "LOWER BOUND DE 9 est -->  " << map.lower_bound(9)->first << " ! \n";
			std::cout << std::endl;

		_print("|| ------------------------- UPPER_BOUND -------------------------- ||");
		_print("Returns an iterator pointing to the first elementthat is greater than key.");
			std::cout << "UPPER BOUND DE 22 est -->  " << map.upper_bound(22)->first << " ! \n";
			std::cout << "UPPER BOUND DE 42 est -->  " << map.upper_bound(42)->first << " ! \n";
			std::cout << "UPPER BOUND DE 1 est -->  " << map.upper_bound(1)->first << " ! \n";
			std::cout << "UPPER BOUND DE 9 est -->  " << map.upper_bound(9)->first << " ! \n";
			std::cout << std::endl;


		_print("|| ------------------------- EQUAL_RANGE ------------------------ ||");
            NAMESPACE::pair<NAMESPACE::map<int, std::string>::iterator, NAMESPACE::map<int, std::string>::iterator> pair;
			std::cout << "--> equal_range -1 = ";
			pair = map.equal_range(-1);
			if (pair.first == map.begin())
				std::cout << "No elements less than the key\n";
			if (pair.second == map.end())
				std::cout << "No elements greater than the key\n";
			if (pair.first != map.begin() && pair.second != map.end())
			{
				for (; pair.first != pair.second; pair.first++)
				{
					std::cout << pair.first->first;
				}
			}
			std::cout << std::endl;

			std::cout << "--> equal_range 22 = ";
			pair = map.equal_range(22);
			if (pair.first == map.begin())
				std::cout << "No elements less than the key\n";
			if (pair.second == map.end())
				std::cout << "No elements greater than the key\n";
			if (pair.first != map.begin() && pair.second != map.end())
			{
				for (; pair.first != pair.second; pair.first++)
				{
					std::cout << pair.first->first;
				}
			}
			std::cout << std::endl;
		}

	std::cout << "|| ------------------------------------------------------- ||" << std::endl;
	std::cout << "|| ----------------------- OBSERVERS ----------------------- ||" << std::endl;
	std::cout << "|| ------------------------------------------------------- ||" << std::endl
		<< std::endl;
	{
		_print("|| ------------------------- KEY_COMP ------------------------- ||");
		 NAMESPACE::map<int, int> m(build_map<int, int>());
		print_map(m);

        for (NAMESPACE::map<int, int>::iterator first = m.begin(); first != m.end(); ++first) {
            NAMESPACE::map<int, int>::iterator it = m.find(rand() % m.size() - 1);
            NAMESPACE::map<int, int>::key_compare comp;

            std::cout << std::boolalpha;
            std::cout << "KEY " << it->first << " is less than: " << first->first << " --> "
                      << comp(it->first, first->first) << std::endl;
        }
	}

	std::cout << "|| ------------------------------------------------------- ||" << std::endl;
	std::cout << "|| ----------------------- COMPARISONS ------------------- ||" << std::endl;
	std::cout << "|| ------------------------------------------------------- ||" << std::endl
		<< std::endl;
	{
		NAMESPACE::map<int, int> lhs(build_map<int, int>());
		_print("--> LHS");
		print_map(lhs);
		NAMESPACE::map<int, int> rhs(build_map<int, int>());
		_print("--> RHS");
		print_map(rhs);

		std::cout << std::endl;
		comparisons(lhs, rhs);
	}	
}
