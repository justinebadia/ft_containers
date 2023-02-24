/*The type pair is used whenever 2 values need to be treated as single unit,
for example if a function has to return 2 values; The containers classes map
and multimap use pairs to manage their elements which are key/value pairs

The type is declared as struct so that all members are public.*/

#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace ft
{

    template <typename T1, typename T2>
    struct pair
    {
        typedef T1 first_type;
        typedef T2 second_type;

        first_type first;
        second_type second;

        /*default constructor: creates a value pair with values that are initialized by the
        default constructor of their type.*/
        pair() : first(first_type()), second(second_type()){}

        /*constructor for 2 values*/
        pair(const first_type &a, const second_type &b) : first(a), second(b){}

		pair(const pair& p) : first(p.first), second(p.second){}

        /*copy constructor with implicit conversions*/
        template <class U, class V>
        pair(const pair<U, V> &p) : first(p.first), second(p.second){}

        pair &operator=(const pair &other)
        {
			if (this != &other)
			{
				first = other.first;
				second = other.second;
			}
            return *this;
        }
    };

    /*Comparisons : The first value has higher priority. If the first values of 2 pairs are equals,
    the comparison of the second yields the result*/
    template <class T1, class T2>
    bool operator==(const pair<T1, T2> &a, const pair<T1, T2> &b)
    {
        return a.first == b.first && a.second == b.second;
    }

    template <class T1, class T2>
    bool operator!=(const pair<T1, T2> &a, const pair<T1, T2> &b)
    {
        return !(b == a);
    }

    template <class T1, class T2>
    bool operator<(const pair<T1, T2> &a, const pair<T1, T2> &b)
    {
        return a.first < b.first || (!(b.first < a.first) && a.second < b.second);
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &a, const pair<T1, T2> &b)
    {
        return !(b < a);
    }

    template <class T1, class T2>
    bool operator>(const pair<T1, T2> &a, const pair<T1, T2> &b)
    {
        return b < a;
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &a, const pair<T1, T2> &b)
    {
        return !(b < a);
    }

    /*The make_pair() enables you tu create a value pair without the types explicitly*/
    template <typename T1, typename T2>
    pair<T1, T2> make_pair(T1 a, T2 b)
    {
        return pair<T1, T2>(a, b);
    }

    /*lexicographically_compare: returns true if range 1 is lexicographically less than range2 */
    template <class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        return (first1 == last1) && (first2 != last2);
    }

    /*equal: return true if the range1 is equal to
    the range [first2, first2 + (last1 - first1)), and false otherwise.*/
    template <class InputIt1, class InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        for (; first1 != last1; first1++, first2++)
        {
            if (!(*first1 == *first2))
                return false;
        }
        return true;
    }


} // namespace

#endif