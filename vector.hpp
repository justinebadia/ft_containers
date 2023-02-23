#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <iostream>

#include "iterator.hpp"
#include "normal_iterator.hpp"
#include "type_traits.hpp"
#include "utility.hpp"

namespace ft {

	/*
	* Typename T -> type de donnés des éléments à stocker dans le vecteur
	* Allocator -> type qui représente l'objet allocateur stocké qui
	* contient des informations sur l'allocation et désallocation de
	* mémoire du vecteur.
	*/
    template <typename T, typename Allocator = std::allocator<T> >
    class vector 
    {
        /* ---------- MEMBER TYPE ---------- */
        public:
            typedef T                                                   value_type; /* Type représentant le type de données stockées dans un vecteur.*/
            typedef Allocator		                                  	allocator_type; /* Type qui représente la classe allocator pour l'objet vector.*/
            typedef std::size_t                                         size_type; /* Type qui compte le nombre d'éléments dans un vecteur. */
            typedef std::ptrdiff_t                                      difference_type; /* Type qui fournit la différence entre les adresses de deux éléments dans un vecteur.*/
            typedef value_type&                                         reference; /* Type qui fournit une référence à un élément stocké dans un vecteur.*/
            typedef const value_type&                                   const_reference; /* Type qui fournit une référence à un const élément stocké dans un vecteur.*/
            typedef typename allocator_type::pointer                    pointer; /* Type qui fournit un pointeur vers un élément d'un vecteur.*/
            typedef typename allocator_type::const_pointer              const_pointer; /* Type qui fournit un pointeur vers un élément const d'un vecteur.*/
			typedef normal_iterator<pointer, vector>					iterator; /* Type qui fournit un itérateur à accès aléatoire pour lire ou modifier un élément dans un vecteur.*/
            typedef normal_iterator<const_pointer, vector>				const_iterator; /* Type qui fournit un pointeur vers un élément const d'un vecteur.*/
            typedef ft::reverse_iterator<iterator>             			reverse_iterator; /* Type qui fournit un itérateur à accès aléatoire pouvant lire ou modifier un élément d'un vecteur inversé.*/
            typedef ft::reverse_iterator<const_iterator>       			const_reverse_iterator; /* Type qui fournit un itérateur à accès aléatoire qui peut lire un élément const dans un vecteur.*/

        /* ---------- MEMBER FUNCTIONS ---------- */

        /* ----------- CONSTRUCTORS -----------*/

		/*
		*	Default constructor creates no elements.
		*/
        vector() : 
			_alloc(allocator_type()), 
			_start(NULL), 
			_finish(NULL), 
			_end_storage(NULL)
			{}

		/*
		* @brief -> Creates a vector with no elements.
		* @param alloc -> an allocator object
		*/
        explicit vector( const allocator_type& alloc) : 
			_alloc(alloc), 
			_start(NULL), 
			_finish(NULL), 
			_end_storage(NULL)
		{}

		/*
		 * @brief  Creates a %vector with copies of an exemplar element.
        *  @param  n  The number of elements to initially create.
        *  @param  value  An element to copy.
        *  @param  alloc  An allocator.
        *
        *  This constructor fills the %vector with n copies of value.
		*/
        explicit vector( size_type n, const T& value = value_type(), const allocator_type& alloc = allocator_type()) : 
			_alloc(alloc),
			_start(NULL), 
			_finish(NULL), 
			_end_storage(NULL)
		{
			if (n == 0)
				return;
			if( n > max_size())
				throw std::length_error("len error");
			_start = _alloc.allocate(n);
			_finish = _start;
			_end_storage = _start + n;
			while(n--)
			{
				_alloc.construct(_finish, value);
				_finish++;
			}
		}

		/**
        *  @brief  Builds a %vector from a range.
        *  @param  first  An input iterator.
        *  @param  last  An input iterator.
        *  @param  a  An allocator.
        *
        *  Create a %vector consisting of copies of the elements from
        *  [first,last).
        *
        *  If the iterators are forward, bidirectional, or
        *  random-access, then this will call the elements' copy
        *  constructor N times (where N is distance(first,last)) and do
        *  no memory reallocation.  But if only input iterators are
        *  used, then this will do at most 2N calls to the copy
        *  constructor, and logN memory reallocations.
        */
	   // Check whether it's an integral type.  If so, it's not an iterator.
		template<typename InputIt>
		vector(InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last, const allocator_type& alloc = allocator_type()): 
			_alloc(alloc),
			_start(NULL), 
			_finish(NULL), 
			_end_storage(NULL)
		{
			typedef typename iterator_traits<InputIt>::iterator_category category;	
			range_initialize(first, last, category());
		} 

		/*
		*  @brief  %Vector copy constructor.
        *  @param  other  A %vector of identical element and allocator types.
        *
        *  The newly-created %vector uses a copy of the allocation
        *  object used by other.  All the elements of other are copied,
        *  but any extra memory in other (for fast expansion) will not be copied.
		*/
      	vector( const vector& other ) :
			_alloc(other._alloc),
			_start(NULL), 
			_finish(NULL), 
			_end_storage(NULL)
		{
			typedef typename iterator_traits<vector::iterator>::iterator_category category;	
			range_initialize(other._start, other._finish, category());
		}

	/* ---------- DESTRUCTEUR ----------
	* The destructors of the elements are called 
	* and the used storage is deallocated. 
	* Note, that if the elements are pointers, 
	* the pointed-to objects are not destroyed.*/
	~vector()
	{
		my_deallocate();
	} 

	/* ---------- COPY OPERATOR ----------- 
	* Remplace les éléments du vecteur par une copie d'un autre vecteur.*/
	vector& operator=( const vector& other ) 
	{
		if(this == &other)
			return *this;
		assign(other.begin(), other.end());
		return *this;
	} 

 	/**
	*  @brief  Assigns a range to a %vector.
    *  @param  n  Number of elements to be assigned.
    *  @param  value  Value to be assigned.
    *
    *  This function fills a %vector with @a n copies of the given
    *  value.  Note that the assignment completely changes the
    *  %vector and that the resulting %vector's size is the same as
    *  the number of elements assigned.  Old data may be lost.
    */
	void assign( size_type n, const value_type& value )
	{
		if ( n > capacity())
		{
			vector tmp(n, value);
			tmp.swap(*this);
		}
		else if (n  > size())
		{
			std::fill(begin(), end(), value);
			size_type more = n - size();
			_finish = construct_range(_finish, _finish + more, value);
		}
		else
		{
			my_erase_at_end(std::fill_n(_start, n, value)); 
		}
	}
	

 	/**
    *  @brief  Assigns a range to a %vector.
    *  @param  first  An input iterator.
	*  @param  last   An input iterator.
    *
    *  This function fills a %vector with copies of the elements in the
    *  range [first,last).
    *
    *  Note that the assignment completely changes the %vector and
    *  that the resulting %vector's size is the same as the number
    *  of elements assigned.  Old data may be lost.
    */
   // Check whether it's an integral type.  If so, it's not an iterator. 
	template <class InputIt>
	void assign( InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last )
	{
		typedef typename iterator_traits<InputIt>::iterator_category category;	
		range_assign(first, last, category());
	}

	/* Retourne une copie de l’objet allocateur utilisé pour construire le vecteur. */
	allocator_type get_allocator() const 
	{
		return (allocator_type());
	}

	/*
	* ---------- ELEMENT ACCESS ---------- *
	*/
   /* Returns a reference to the element at specified 
   * location pos, with bounds checking.
   */
	reference at( size_type pos )
	{
		range_check(pos);
		return (*this)[pos];
	}

	const_reference at( size_type pos ) const
	{
		range_check(pos);
		return (*this)[pos];
	}

	/*
	* Returns a reference to the element at specified location pos. 
	* No bounds checking is performed.
	*/
	reference operator[]( size_type pos )
	{
		return *(_start + pos);
	}

	const_reference operator[]( size_type pos ) const 
	{
		return *(_start + pos);
	}
	
	/*
	* Returns a reference to the data at the first element of the vector.
	*/
	reference front()
	{
		return *begin();
	}

	const_reference front() const 
	{
		return *begin();
	}

	/*
	* Returns a reference to the last element in the container.
	*/
	reference back()
	{
		return *(end() - 1);
	}

	const_reference back() const
	{
		return *(end() - 1);
	}

	/*
	* Returns pointer to the underlying element storage. 
	* For non-empty containers, the returned pointer 
	* compares equal to the address of the first element.
	*/
	T* data()
	{
		return _start;
	}

	const T* data() const
	{
		return _start;
	}

	/* ---------- ITERATORS ----------- */
	/*
	* ---------- BEGIN ---------- * 
	* Returns an iterator to the first element of the vector.
	* If the vector is empty, the returned iterator will be equal to end().
	*/
	iterator begin()
	{
		return iterator(_start);
	}

	const_iterator begin() const
	{
		return const_iterator(_start);
	}

	/*
	* ---------- END ---------- * 
	* Returns an iterator to the element following 
	* the last element of the vector.
	*/
	iterator end()
	{
		return iterator(_finish);
	}

	const_iterator end() const
	{
		return const_iterator(_finish);
	}

	/*
	* ---------- RBEGIN ---------- * 
	* Returns a reverse iterator to the first element 
	* of the reversed vector. It corresponds to the 
	* last element of the non-reversed vector. 
	* If the vector is empty, the returned iterator is equal to rend()
	*/
	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	/*
	* --------- REND ---------- *
	* Returns a reverse iterator to the element 
	* following the last element of the reversed vector. 
	* It corresponds to the element preceding the first element 
	* of the non-reversed vector 
	*/
	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	/*
	* ---------- CAPACITY ---------- *
	*/

 /* Returns true if the %vector is empty. (Thus begin() would equal end().)*/
	bool empty() const
	{
		return (begin() == end());
	}

	/* Returns the number of elements in the vector*/
	size_type size() const
	{
		return (_finish - _start);
	}

	/*  Returns the size() of the largest possible vector. */
	size_type max_size() const
	{
		const size_t diff_max = std::numeric_limits<difference_type>::max();
		const size_t alloc_max = allocator_type().max_size();

		return std::min(diff_max, alloc_max);
	}

	/**
    *  @brief  Attempt to preallocate enough memory for specified number of
    *          elements.
    *  @param  n  Number of elements required.
    *  @throw  std::length_error  If @a n exceeds @c max_size().
    *
	*/
	void reserve( size_type new_cap )
	{
		if (new_cap > max_size())
			throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
		if (capacity() < new_cap)
		{
			pointer new_start = _alloc.allocate(new_cap);
			pointer new_finish = construct_range(new_start, _start, _finish);
			my_deallocate();

			_start = new_start;
			_finish = new_finish;
			_end_storage = _start + new_cap;
		}
	}

	/* Returns the total number of elements that the vector
	* can hold before needing to allocate more memory.*/
	size_type capacity() const
	{
		return (_end_storage - _start);
	}

	/*
	* ---------- MODIFIERS --------- *
	*/
	/* Erases all elements from the container.*/
	void clear()
	{
		my_erase_at_end(_start);
	}

	/**
    *  @brief  Inserts a number of copies of given data into the %vector.
    *  @param  position  An iterator into the %vector.
    *  @param  n  Number of elements to be inserted.
    *  @param  value  Data to be inserted.
    *  This function will insert a specified number of copies of
    *  the given data before the location specified by @a position.
	*/
	void insert( iterator position, size_type n, const value_type& value )
	{
		if (n != 0)
		{
            if (capacity() - size() >= n) // s'il reste de la place
            {
                const size_type elems_after = end() - position;
                pointer old_finish = _finish;
                if (elems_after > n)
                {
                    _finish = construct_range(_finish, _finish - n, _finish);
                    std::copy_backward(position.base(), old_finish - n, old_finish);
                    std::fill(position.base(), position.base() + n, value);
                }
                else
                {
                    _finish = construct_range(_finish, _finish + (n - elems_after), value);
                    _finish = construct_range(_finish, position.base(), old_finish);
                    std::fill(position.base(), old_finish, value);
                }
            }
            else // plsude place
            {
                const size_type len = check_len(n);
                pointer new_start = _alloc.allocate(len);
                pointer new_end = construct_range(new_start, _start, position.base());
                new_end = construct_range(new_end, new_end + n, value);
                new_end = construct_range(new_end, position.base(), _finish);

                my_deallocate();
                _start = new_start;
                _finish = new_end;
                _end_storage = _start + len;
            }

        }
	}

	/**
    *  @brief  Inserts given value into %vector before specified iterator.
    *  @param  position  An iterator into the %vector.
    *  @param  value  Data to be inserted.
    *  @return  An iterator that points to the inserted data.
    *  This function will insert a copy of the given value before
    *  the specified location.
	*/
	iterator insert( iterator position, const value_type& value )
	{
		const size_type n = position - begin();
		
		insert(position, 1, value);
		
		return iterator(_start + n);
	}
	
    /**
    *  @brief  Inserts a range into the %vector.
    *  @param  position  An iterator into the %vector.
    *  @param  first  An input iterator.
    *  @param  last   An input iterator.
    *  This function will insert copies of the data in the range
    *  [first,last) into the %vector before the location specified
    *  by @a pos.
    * Check whether it's an integral type.  If so, it's not an iterator.
    */
	template <class InputIt> 
    void insert( iterator position, InputIt first, typename enable_if<!is_integral<InputIt>::value, InputIt>::type last )
    {
        typedef typename iterator_traits<InputIt>::iterator_category category;
    
        range_insert(position, first, last, category());
    }

	/**
    *  @brief  Remove element at given position.
    *  @param  position  Iterator pointing to element to be erased.
    *  @return  An iterator pointing to the next element (or end()).
    *
    *  This function will erase the element at the given position and thus
    *  shorten the %vector by one. 
	* Returns iterator following the last removed element.
	*/
	iterator erase( iterator position )
	{
		iterator first = position + 1;
		if (first != end())
		{
			std::copy(first, end(), position);
		}
		--_finish;
		_alloc.destroy(_finish);

		return position;
	}

	/**
    *  @brief  Remove a range of elements.
    *  @param  first  Iterator pointing to the first element to be erased.
    *  @param  last  Iterator pointing to one past the last element to be
    *                erased.
    *  @return  An iterator pointing to the element pointed to by @a last
    *           prior to erasing (or end()).
	*/
iterator erase( iterator first, iterator last )
{
	if (first != last)
	{
		if(last != end())
		{
			std::copy(last, end(), first);
		}
		my_erase_at_end(first.base() + (end() - last));
	}
	return first;
}

	/*
	*  @brief  Add data to the end of the %vector.
    *  @param  value  Data to be added.
    * The function creates an element at the end 
	* of the vector and assigns the given data to it.
	*/
	void push_back( const value_type& value )
	{
		if ( _finish != _end_storage)
		{
			_alloc.construct(_finish, value);
			++_finish;
		}
		else
			insert(end(), value);
	}

	/*
	*   @brief  Removes last element.
    *  It shrinks the vector by one.
	*/
	void pop_back()
	{
		--_finish;
		_alloc.destroy(_finish);
	}

	/**
    *  @brief  Resizes the %vector to the specified number of elements.
    *  @param  new_size  Number of elements the %vector should contain.
    *  @param  x  Data with which new elements should be populated.
    *
    *  This function will %resize the %vector to the specified
    *  number of elements.  If the number is smaller than the
    *  %vector's current size the %vector is truncated, otherwise
    *  the %vector is extended and new elements are populated with
    *  given data.
    */
	void resize(size_type new_size, value_type value = value_type())
	{
		if (new_size > size())
			insert(end(), new_size - size(), value);
		else if (new_size < size())
			my_erase_at_end(_start + new_size);
	}

	/**
    *  @brief  Swaps data with another %vector.
    *  @param  other  A %vector of the same element and allocator types.
    *
    *  This exchanges the elements between two vectors in constant time.
    *  (Three pointers, so it should be quite fast.)
    *  Note that the global std::swap() function is specialized such that
    *  std::swap(v1,v2) will feed to this function.
    */
	void swap(vector& other)
	{
		std::swap(_start, other._start);
		std::swap(_finish, other._finish);
		std::swap(_end_storage, other._end_storage);
	}

	private:
		allocator_type 	_alloc;
		pointer			_start;
		pointer			_finish;
		pointer			_end_storage;

		/* Safety check used only from at() */
		inline void range_check(size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("vector");
		}

		void my_destroy( pointer first, pointer last)
		{
			for(; first != last; ++first)
				_alloc.destroy(first);
		}

		void my_deallocate()
		{
			if (_start)
			{
				clear();	
				_alloc.deallocate(_start, capacity());
			}
		}

		void my_erase_at_end(pointer pos)
		{
			my_destroy(pos, _finish);
			_finish = pos;
		}

		template<typename InputIt>
		void range_initialize(InputIt first, InputIt last, std::input_iterator_tag)
		{
			for (; first != last; ++first)
				push_back(*first);
		}

		template<typename ForwardIt>
		void range_initialize(ForwardIt first, ForwardIt last, std::forward_iterator_tag)
		{
			size_type n = std::distance(first, last);
			_start = _alloc.allocate(n);
			_end_storage = _start + n;
			_finish = _start;
			while(n)
			{
				_alloc.construct(_finish, *first++);
				_finish++;
				n--;
			}
		}

		template<typename InputIt>
		void range_assign(InputIt first, InputIt last, std::input_iterator_tag)
		{
			clear();
			for (; first != last; ++first)
				push_back(*first);
		}

		template <typename Iter>
		pointer construct_range(pointer dest, Iter start, Iter finish)
		{
			for (; start != finish; ++dest, (void)++start) {
				_alloc.construct(dest, *start);
			}
			return dest;
		}

		pointer construct_range(pointer dest, const_pointer finish, const_reference value)
		{
			for (; dest != finish; ++dest) {
				_alloc.construct(dest, value);
			}
			return dest;
		}

		size_type check_len(size_type n)
		{
			if (max_size() - capacity() < n)
				throw std::length_error("insert error");
			if (capacity() >= max_size() / 2)
				return max_size();
			return std::max(size() + n, capacity() * 2);
		}

        template<typename InputIt>
		void range_insert(iterator position, InputIt first, InputIt last, std::input_iterator_tag)
        {
            for (; first != last; first++)
            {
                position = insert(position, *first);
                position++;
            }
        }

        template<typename ForwardIt>
        void range_insert(iterator position, ForwardIt first, ForwardIt last, std::forward_iterator_tag)
        {
            if (first != last)
            {
                const size_type n = std::distance(first, last);
				check_len(n);
                if (size_type(_end_storage - _finish) >= n)
                {
                    const size_type elems_after = end() - position;
                   	pointer old_finish = _finish;
                    if (elems_after > n)
                    {
                        _finish = construct_range(_finish, _finish - n, _finish);
                        std::copy_backward(position.base(), old_finish - n, old_finish);
                        std::copy(first, last, position);
                    }
                    else
                    {
						ForwardIt mid = first;
						std::advance(mid, elems_after);
						_finish = construct_range(_finish, mid, last);
						_finish = construct_range(_finish, position.base(), old_finish);
						std::copy(first, mid, position);
                    }
                }
                else
                {
					const size_type old_size = size();
					size_type len = old_size + std::max(old_size, n);
					check_len(len);
					pointer new_start = _alloc.allocate(len);
					pointer new_finish = new_start;
					new_finish = construct_range(new_start, _start, position.base());
					new_finish = construct_range(new_finish, first, last);
					new_finish = construct_range(new_finish, position.base(), _finish);

					 my_deallocate();
					_start = new_start;
					_finish = new_finish;
					_end_storage = _start + len;
				}
            }
        }
    };

	/* NON MEMBER FUNCTIONS*/

	template <typename T, typename Alloc>
	inline bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename T, typename Alloc>
	inline bool operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename T, typename Alloc>
	inline bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}
	
	template <typename T, typename Alloc>
	inline bool operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return rhs < lhs;
	}

	template <typename T, typename Alloc>
	inline bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <typename T, typename Alloc>
	inline bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template <typename T, typename Alloc>
	inline void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{
		x.swap(y);
	}

} //namespace

#endif
