/*
 * cyclic_shift.hpp
 *
 *  Created on: Sep 13, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_CYCLIC_SHIFT_HPP_
#define LIB_UTILITY_CYCLIC_SHIFT_HPP_


#include <cstddef>
#include <iterator>
#include <tuple>


namespace utility {

template<typename ForwardIterator>
std::size_t
cyclic_shift_left(ForwardIterator it1, ForwardIterator it2) {
    ForwardIterator first, last;
    if (std::distance(it1, it2) > 0)
        std::tie(first, last) = { it1, it2 };
    else
        std::tie(first, last) = { it2, it1 };
    std::size_t size = 1;
    auto temp = *first;
    while (first != last) {
        ForwardIterator next = std::next(first);
        *first = *next;
        first = next;
        ++size;
    }
    *last = temp;
    return size;
}

template<typename ForwardIterator>
std::size_t
cyclic_shift_right(ForwardIterator it1, ForwardIterator it2) {
    ForwardIterator first, last;
    if (std::distance(it1, it2) > 0)
        std::tie(first, last) = { it1, it2 };
    else
        std::tie(first, last) = { it2, it1 };
    std::size_t size = 1;

    auto temp = *first;
    while (first != last) {
        ForwardIterator next = std::next(first);
        std::swap(temp, *next);
        first = next;
        ++size;
    }
    *first = temp;
    return size;
}

}   //-- namespace utility --


#endif /* LIB_UTILITY_CYCLIC_SHIFT_HPP_ */
