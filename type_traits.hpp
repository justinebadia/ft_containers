#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft{

/* enable_if: If B is true, std::enable_if has a public member typedef type, 
* equal to T; otherwise, there is no member typedef.*/
/* SFINAE = Substitution Failure Is Not An Error: */
template <bool B, class T = void>
struct enable_if{};

template<typename T>
struct enable_if<true, T>
{
	typedef T type;
};

struct true_type 
{ 
	static const bool value = true; 
	operator bool(){ return value; };
	bool	operator()() { return value; };
};
struct false_type 
{	
	static const bool value = false;
	operator bool(){ return value; };
	bool	operator()() { return value; };
};

/* If T and U name the same type, provides 
* the member constant value equal to true. 
* Otherwise value is false.*/
template <class T, class U> 
struct is_same: public false_type {};

template <class T> 
struct is_same<T, T>: public true_type {};


/*Mik tester*/
template <class T> 
struct is_integral : public false_type {};

template <class T> 
struct is_integral<const T> : public is_integral<T> {};

template <class T> 
struct is_integral<volatile const T> : public is_integral<T>{};

template <class T> 
struct is_integral<volatile T> : public is_integral<T>{};


/*is_integral: Checks whether T is an integral type. Provides the member constant value which is equal to true, 
if T is the type bool, char, char16_t, char32_t, wchar_t, short, int, long, long long, 
or any implementation-defined extended integer types, including any signed, unsigned, and cv-qualified variants. 
Otherwise, value is equal to false*/
template<> 
struct is_integral<char> 						: public true_type{};

template<> 
struct is_integral<signed char> 				: public true_type{};

template<> 
struct is_integral<unsigned char> 				: public true_type{};

template<> 
struct is_integral<wchar_t> 					: public true_type {};

template<> 
struct is_integral<char16_t> 					: public true_type{};

template<> 
struct is_integral<char32_t> 					: public true_type{};

template<> 
struct is_integral<short> 						: public true_type{};

template<> 
struct is_integral<unsigned short>				: public true_type{};

template<> 
struct is_integral<int> 						: public true_type{};

template<> 
struct is_integral<unsigned int> 				: public true_type{};

template<> 
struct is_integral<long> 						: public true_type{};

template<> 
struct is_integral<unsigned long> 				: public true_type{};

template<> 
struct is_integral<bool> 						: public true_type{};
} //namespace

#endif