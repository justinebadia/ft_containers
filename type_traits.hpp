#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft{

	/*is_integral: Checks whether T is an integral type. Provides the member constant value which is equal to true, 
	if T is the type bool, char, char16_t, char32_t, wchar_t, short, int, long, long long, 
	or any implementation-defined extended integer types, including any signed, unsigned, and cv-qualified variants. 
	Otherwise, value is equal to false*/

template<class T, bool v>
struct integral_constant
{
	static const bool value = v;
	typedef T value_type;
	typedef integral_constant type;
	operator value_type() const {return value;}
};



template<class T> 
struct is_integral : public ft::integral_constant<T, false>{};

template<> 
struct is_integral<bool> : public ft::integral_constant<bool, true>{};

template<> 
struct is_integral<char> : public ft::integral_constant<bool, true>{};

template<> 
struct is_integral<signed char> : public ft::integral_constant<bool, true>{};

template<> 
struct is_integral<unsigned char> : public ft::integral_constant<bool, true>{};

template<> 
struct is_integral<wchar_t> : public ft::integral_constant<bool, true>{};

template<> 
struct is_integral<short> : public ft::integral_constant<bool, true>{};

template<> 
struct is_integral<unsigned short> : public ft::integral_constant<bool, true>{};

template<> 
struct is_integral<int> : public ft::integral_constant<bool, true>{};

template<> 
struct is_integral<unsigned int> : public ft::integral_constant<bool, true>{};

template<> 
struct is_integral<long> : public ft::integral_constant<bool, true>{};

template<> 
struct is_integral<unsigned long> : public ft::integral_constant<bool, true>{};

template<> 
struct is_integral<long long> : public ft::integral_constant<bool, true>{};

template<> 
struct is_integral<unsigned long long> : public ft::integral_constant<bool, true>{};

struct true_type {
	static const bool value = true;
	typedef true_type type;
};

struct false_type {
	static const bool value = false;
	typedef false_type type;
};

/*If T and U name the same type, provides the member constant value equal to true. 
Otherwise value is false.*/
template<typename T, typename U>
struct is_same : public false_type {};
 
template<typename T>
struct is_same<T, T> : public true_type {};

/*enable_if: If B is true, std::enable_if has a public member typedef type, equal to T; otherwise, there is no member typedef.*/
/*SFINAE = Substitution Failure Is Not An Error: */
template<bool, typename T = void>
struct enable_if{};

template<typename T>
struct enable_if<true, T>
{
	typedef T type;
};

} //namespace
	

#endif