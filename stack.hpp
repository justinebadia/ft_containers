#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{
	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
	public:
		/*MEMBER TYPES*/
		typedef Container container_type;
		typedef typename container_type::value_type value_type;
		typedef typename container_type::size_type size_type;
		typedef typename container_type::reference reference;
		typedef typename container_type::const_reference const_reference;

		/*MEMBER FUNCTIONS*/
		explicit stack(const container_type &cont = container_type()) : c(cont) {}

		stack(const stack &other) : c(other.c) {}

		~stack() {}

		stack &operator=(const stack &other)
		{
			c = other.c;
			return *this;
		}

		/*Returns reference to the top element in the stack. This is the most recently pushed element.
		This element will be removed on a call to pop(). Effectively calls c.back().*/
		reference top() { return c.back(); }
		const_reference top() const { return c.back(); }

		/*Checks if the underlying container has no elements, i.e. whether c.empty().*/
		bool empty() const { return c.empty(); }

		/*Returns the number of elements in the underlying container*/
		size_type size() const { return c.size(); }

		void push(const value_type &value) { c.push_back(value); }

		void pop() { c.pop_back(); }

	protected:
		container_type c;

	public:
		template <typename U, typename C>
		friend bool operator==(const ft::stack<U, C> &lhs, const ft::stack<U, C> &rhs);

		template <typename U, typename C>
		friend bool operator<(const ft::stack<U, C> &lhs, const ft::stack<U, C> &rhs);
	};

	template <typename T, typename Container>
	inline bool operator==(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.c == rhs.c;
	}

	template <typename T, typename Container>
	inline bool operator!=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Container>
	inline bool operator<(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return lhs.c < rhs.c;
	}

	template <typename T, typename Container>
	inline bool operator<=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T, typename Container>
	inline bool operator>(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Container>
	inline bool operator>=(const ft::stack<T, Container> &lhs, const ft::stack<T, Container> &rhs)
	{
		return !(lhs < rhs);
	}
}

#endif