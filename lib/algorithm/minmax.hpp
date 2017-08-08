/*
 * minmax.hpp
 *
 *  Created on: Aug 5, 2017
 *      Author: ilion
 */

#ifndef LIB_ALGORITHM_MINMAX_HPP_
#define LIB_ALGORITHM_MINMAX_HPP_

#include <algorithm>
#include <iterator>

namespace algorithm {

template<typename T>
struct min {
    typedef T container_type;
    typedef typename container_type::size_type size_type;
    typedef typename container_type::value_type value_type;

    inline constexpr size_type operator() (const container_type& array) const {
        return std::distance(std::begin(array), std::min_element(std::begin(array), std::end(array)));
    }
};
template<typename T>
struct max {
    typedef T container_type;
    typedef typename container_type::size_type size_type;
    typedef typename container_type::value_type value_type;

    inline constexpr size_type operator() (const container_type& array) const {
        return std::distance(std::begin(array), std::max_element(std::begin(array), std::end(array)));
    }
};
template<typename T>
struct minmax {
    typedef T container_type;
    typedef typename container_type::size_type size_type;
    typedef typename container_type::value_type value_type;

    struct result {
        value_type minIndex, maxIndex;
    };

    inline constexpr result operator() (const container_type& array) const {
        auto minmax = std::distance(std::begin(array), std::minmax_element(std::begin(array), std::end(array)));
        return (minmax.first, minmax.second);
    }
};

}   //-- namespace algorithm --


#endif /* LIB_ALGORITHM_MINMAX_HPP_ */
