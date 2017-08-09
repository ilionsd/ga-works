/*
 * binary_search.hpp
 *
 *  Created on: Aug 4, 2017
 *      Author: ilion
 */

#ifndef LIB_ALGORITHM_BINARY_SEARCH_HPP_
#define LIB_ALGORITHM_BINARY_SEARCH_HPP_


#include <cstddef>


namespace algorithm {

template<typename T>
struct binary_search {
    typedef T value_type;
    typedef std::size_t size_type;

    template<typename V>
    constexpr size_type operator() (const V& vec, const value_type val) const {
        register size_type left = 0, right = vec.size() - 1, middle = 0;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (vec[middle] == val)
                break;
            else if (vec[middle] < val)
                left = middle + 1;
            else
                right = middle - 1;
        }
        return left + (right - left) / 2;
    }
};

}   //-- namespace algorithm --


#endif /* LIB_ALGORITHM_BINARY_SEARCH_HPP_ */
