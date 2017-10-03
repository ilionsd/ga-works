/*
 * order.hpp
 *
 *  Created on: Oct 3, 2017
 *      Author: ilion
 */

#ifndef LIB_ORDERING_ORDER_HPP_
#define LIB_ORDERING_ORDER_HPP_


#include <iterator>
#include <type_traits>


#ifndef ORDERING_INTEGRAL_TYPE_DEFINITION
#define ORDERING_INTEGRAL_TYPE_DEFINITION( TYPE ) \
inline int order(TYPE a, TYPE b) {                       \
    return static_cast<int>(a - b);               \
}
#endif


namespace ordering {

ORDERING_INTEGRAL_TYPE_DEFINITION( const   signed      char )
ORDERING_INTEGRAL_TYPE_DEFINITION( const   signed     short )
ORDERING_INTEGRAL_TYPE_DEFINITION( const   signed       int )
ORDERING_INTEGRAL_TYPE_DEFINITION( const   signed      long )
ORDERING_INTEGRAL_TYPE_DEFINITION( const   signed long long )
ORDERING_INTEGRAL_TYPE_DEFINITION( const unsigned      char )
ORDERING_INTEGRAL_TYPE_DEFINITION( const unsigned     short )
ORDERING_INTEGRAL_TYPE_DEFINITION( const unsigned       int )
ORDERING_INTEGRAL_TYPE_DEFINITION( const unsigned      long )
ORDERING_INTEGRAL_TYPE_DEFINITION( const unsigned long long )

template<typename ForwardIterator>
int order(ForwardIterator, ForwardIterator, ForwardIterator, ForwardIterator);
template<typename Iteratable>
std::enable_if_t<std::is_compound<Iteratable>::value, int>
order(const Iteratable& a, const Iteratable& b);

template<typename ForwardIterator>
int order(ForwardIterator aBegin, ForwardIterator aEnd, ForwardIterator bBegin, ForwardIterator bEnd) {
    int cmp = 0;
    while (!cmp && aBegin != aEnd && bBegin != bEnd)
        cmp = order(*aBegin++, *bBegin++);
    if (!cmp)
        cmp = order(std::distance(aBegin, aEnd), std::distance(bBegin, bEnd));
    return cmp;
}

template<typename Iteratable>
inline
std::enable_if_t<std::is_compound<Iteratable>::value, int>
order(const Iteratable& a, const Iteratable& b) {
    return order(a.cbegin(), a.cend(), b.cbegin(), b.cend());
}

}   //-- namespace ordering --


#ifdef ORDERING_INTEGRAL_TYPE_DEFINITION
#undef ORDERING_INTEGRAL_TYPE_DEFINITION
#endif

#endif /* LIB_ORDERING_ORDER_HPP_ */
