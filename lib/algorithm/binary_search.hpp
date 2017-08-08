/*
 * binary_search.hpp
 *
 *  Created on: Aug 4, 2017
 *      Author: ilion
 */

#ifndef LIB_ALGORITHM_BINARY_SEARCH_HPP_
#define LIB_ALGORITHM_BINARY_SEARCH_HPP_


namespace algorithm {

template<typename T>
struct binary_search {
    typedef T container_type;
    typedef typename container_type::value_type value_type;
    typedef typename container_type::size_type size_type;

    constexpr size_type operator() (const container_type& array, const value_type val) const {
        register size_type left = 0, right = array.size() - 1, middle;
        while (left < right) {
            middle = left + (right - left) / 2;
            if (array[middle] == val)
                break;
            else if (array[middle] < val)
                left = middle + 1;
            else
                right = middle - 1;
        }
        return left + (right - left) / 2;
    }

};

}   //-- namespace algorithm --


#endif /* LIB_ALGORITHM_BINARY_SEARCH_HPP_ */
