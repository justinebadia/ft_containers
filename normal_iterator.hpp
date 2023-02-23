#ifndef NORMAL_ITERATOR_HPP
#define NORMAL_ITERATOR_HPP

#include"iterator.hpp"

namespace ft {


// This iterator adapter is @a normal in the sense that it does not
// change the semantics of any of the operators of its iterator
// parameter.  Its primary purpose is to convert an iterator that is
// not a class, e.g. a pointer, into an iterator that is a class.
template <typename Iterator, typename Container>
	class normal_iterator
	{
		protected:
			Iterator 										current;
			typedef iterator_traits<Iterator>				traits_type;
		
		public:
			typedef Iterator								iterator_type;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::reference			reference;
			typedef typename traits_type::pointer			pointer;


			normal_iterator() : current(Iterator()){}
			explicit normal_iterator(const iterator_type& it) : current(it){}

		/* Allow iterator to const_iterator conversion*/
       template<typename Iter>
	   normal_iterator(const normal_iterator<Iter, 
	   	typename enable_if<is_same<Iter, typename Container::pointer>::value, Container>::type>& it) :
			current(it.base()) {}

      
		/*
		*	Random access iterators are bidirectional iterators 
		* 	that can perform random acces; and bidirectional 
		*	iterators are forward iterators that provides
		*	the ability to iterate bacward
		*/

		/* 
		* Forward iterartor requirements 
		*/
		reference operator*() const
		{
			return *current;
		}

		pointer operator->() const
		{
			return current;
		}

		normal_iterator& operator++()
		{
			++current;
			return *this;
		}

		normal_iterator operator++(int)
		{
			return normal_iterator(current++);
		}

		/* 
		* Bidirectional iterator requirements 
		*/
		normal_iterator& operator--()
		{
			--current;
			return *this;
		}

		normal_iterator operator--(int)
		{
			return normal_iterator(current--);
		}

		/*	
		* Random access iterator requirements 
		*/
		reference operator[](const difference_type& n) const
		{
			return current[n];
		}

		normal_iterator& operator+=(const difference_type& n)
		{
			current += n;
			return *this;
		}

		normal_iterator operator+(const difference_type& n) const 
		{
			return normal_iterator(current + n);
		}

		normal_iterator& operator-=(const difference_type& n)
		{
			current -= n;
			return *this;
		}

		normal_iterator operator-(const difference_type& n) const
		{
			return normal_iterator(current - n);
		}		

		const Iterator& base() const
		{
			return current;
		}
	};

	/*
	*	NON MEMBER FUNCTIONS 
	*/

	template <typename It1, typename It2, typename C>
	inline bool operator==(const normal_iterator<It1, C>& lhs, const normal_iterator<It2, C> &rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <typename It, typename C>
	inline bool operator==(const normal_iterator<It, C>& lhs, const normal_iterator<It, C> &rhs)
	{
		return lhs.base() == rhs.base();
	}

		template <typename It1, typename It2, typename C>
	inline bool operator!=(const normal_iterator<It1, C>& lhs, const normal_iterator<It2, C> &rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <typename It, typename C>
	inline bool operator!=(const normal_iterator<It, C>& lhs, const normal_iterator<It, C> &rhs)
	{
		return lhs.base() != rhs.base();
	}

		template <typename It1, typename It2, typename C>
	inline bool operator<(const normal_iterator<It1, C>& lhs, const normal_iterator<It2, C> &rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <typename It, typename C>
	inline bool operator<(const normal_iterator<It, C>& lhs, const normal_iterator<It, C> &rhs)
	{
		return lhs.base() < rhs.base();
	}

		template <typename It1, typename It2, typename C>
	inline bool operator>(const normal_iterator<It1, C>& lhs, const normal_iterator<It2, C> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename It, typename C>
	inline bool operator>(const normal_iterator<It, C>& lhs, const normal_iterator<It, C> &rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <typename It1, typename It2, typename C>
	inline bool operator<=(const normal_iterator<It1, C>& lhs, const normal_iterator<It2, C> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename It, typename C>
	inline bool operator<=(const normal_iterator<It, C>& lhs, const normal_iterator<It, C> &rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <typename It1, typename It2, typename C>
	inline bool operator>=(const normal_iterator<It1, C>& lhs, const normal_iterator<It2, C> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename It, typename C>
	inline bool operator>=(const normal_iterator<It, C>& lhs, const normal_iterator<It, C> &rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <typename It1, typename It2, typename C>
	inline typename normal_iterator<It1, C>::difference_type 
	operator-(const normal_iterator<It1, C>& lhs, const normal_iterator<It2, C> &rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <typename It, typename C>
	inline typename normal_iterator<It, C>::difference_type 
	operator-(const normal_iterator<It, C>& lhs, const normal_iterator<It, C> &rhs)
	{
		return lhs.base() - rhs.base();
	}

	template <typename It, typename C>
	inline normal_iterator<It, C>operator+(typename normal_iterator<It, C>:: difference_type n, const normal_iterator<It, C> &i)
	{
		return normal_iterator<It, C>(i.base() + n);
	}


} // namespace

#endif