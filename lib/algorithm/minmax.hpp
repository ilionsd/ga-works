/*
 * minmax.hpp
 *
 *  Created on: Aug 5, 2017
 *      Author: ilion
 */

#ifndef LIB_ALGORITHM_MINMAX_HPP_
#define LIB_ALGORITHM_MINMAX_HPP_


#include <cstddef>
#include <algorithm>
#include <iterator>


namespace algorithm {

template<typename T>
struct min {
    typedef T value_type;
    typedef std::size_t size_type;

    template<typename V>
    inline constexpr size_type operator() (const V& vec) const {
        auto b = std::begin(vec), e = std::end(vec);
        return std::distance(b, std::min_element(b, e));
    }
};
template<typename T>
struct max {
    typedef T value_type;
    typedef std::size_t size_type;

    template<typename V>
    inline constexpr size_type operator() (const V& vec) const {
        auto b = std::begin(vec), e = std::end(vec);
        return std::distance(b, std::max_element(b, e));
    }
};
template<typename T>
struct minmax {
    typedef T value_type;
    typedef std::size_t size_type;

    template<typename V>
    inline constexpr std::pair<size_type, size_type> operator() (const V& vec) const {
        auto b = std::begin(vec), e = std::end(vec);
        auto minmax = std::minmax_element(b, e);
        return std::make_pair(std::distance(b, minmax.first), std::distance(b, minmax.second));
    }
};

}   //-- namespace algorithm --


#endif /* LIB_ALGORITHM_MINMAX_HPP_ */
