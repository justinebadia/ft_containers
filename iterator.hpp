#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include<cstddef>
#include<iterator>
#include "type_traits.hpp"

namespace ft {

template<class Iter>
struct iterator_traits {
	typedef typename Iter::value_type value_type;
	typedef typename Iter::difference_type difference_type;
	typedef typename Iter::iterator_category iterator_category;
	typedef typename Iter::pointer pointer;
	typedef typename Iter::reference reference;
};

template<class T>
struct iterator_traits<T*>{
	typedef std::ptrdiff_t difference_type;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef std::random_access_iterator_tag iterator_category;
};

template<class T>
struct iterator_traits<const T*>{
	typedef std::ptrdiff_t difference_type;
	typedef T value_type;
	typedef const T* pointer;
	typedef const T& reference;
	typedef std::random_access_iterator_tag iterator_category;
};

/*A reverse_iterator iterates from the end of the sequence
 defined by its underlying iterator to the beginning of that sequence. */

template<typename Iter>
class reverse_iterator : public std::iterator< 
	typename iterator_traits<Iter>::iterator_category,
	typename iterator_traits<Iter>::value_type,
	typename iterator_traits<Iter>::difference_type,
	typename iterator_traits<Iter>::pointer,
	typename iterator_traits<Iter>::reference> 
	{
	
	/*MEMBER TYPES*/
	public:
	typedef Iter 	iterator_type;
 	typedef typename iterator_traits<Iter>::value_type value_type;
	typedef typename iterator_traits<Iter>::difference_type difference_type;
	typedef typename iterator_traits<Iter>::iterator_category iterator_category;
	typedef typename iterator_traits<Iter>::pointer pointer;
	typedef typename iterator_traits<Iter>::reference reference;

	protected:
	Iter current;

	/*MEMBER FUNCTIONS*/
	public:
	reverse_iterator() : current(){}
	explicit reverse_iterator(iterator_type it): current(it){}
	reverse_iterator(const reverse_iterator& it) : current(it.current) {}
	
	template<class U>
	reverse_iterator(const reverse_iterator<U>& other): current(other.base()){}

	~reverse_iterator() {}
	
	reverse_iterator& operator=(const reverse_iterator& other)
	{
		current = other.current;
		return *this;
	}

	Iter base() const { return current; } //return iterator value


/*return a reference or pointer to the element previous to current*/ 
	reference operator*() const 
	{
		Iter tmp = current;
		return *--tmp;
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	reference operator[](difference_type n) const
	{
		return *(*this + n);
	}

	reverse_iterator& operator++() 
	{
		--current;
		return *this;
	}

	reverse_iterator operator++(int)
	{
		return reverse_iterator(current--);
	}

	reverse_iterator& operator--()
	{
		++current;
		return *this;
	}

	reverse_iterator operator--(int)
	{
		return reverse_iterator(current++);
	}

	reverse_iterator operator+(difference_type n) const
	{
		return reverse_iterator(base() - n);
	}

	reverse_iterator operator-(difference_type n) const
	{
		return reverse_iterator(base() + n);
	}

	reverse_iterator &operator-=(difference_type n)
	{
		current += n;
		return *this;
	}
	
	reverse_iterator &operator+=(difference_type n)
	{
		current -= n;
		return *this;
	}
};

/*NON-MEMBER FUNCTIONS*/
template<class It1, class It2>
bool operator==(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
	return lhs.base() == rhs.base();
}

template<class It1, class It2>
bool operator!=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
	return lhs.base() != rhs.base();
}

template<class It1, class It2>
bool operator<(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
	return lhs.base() > rhs.base();
}

template<class It1, class It2>
bool operator<=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
	return lhs.base() >= rhs.base();
}

template<class It1, class It2>
bool operator>(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
	return lhs.base() < rhs.base();
}

template<class It1, class It2>
bool operator>=(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
	return lhs.base() <= rhs.base();
}

/*returns the iterator incremented by n*/
template<class Iter>
reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it)
{
	return reverse_iterator<Iter>(it.base() - n);
}

/*returns the distance between 2 iterators adaptators*/
template <class It1, class It2>
typename reverse_iterator<It1>::difference_type operator-(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
{
return rhs.base() - lhs.base();
}

}

#endif