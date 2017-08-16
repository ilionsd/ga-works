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

struct min {
    typedef std::size_t size_type;

    template<typename V>
    inline constexpr size_type operator() (const V& vec) const {
        auto b = std::begin(vec), e = std::end(vec);
        return this->operator ()(b, e);
    }
    template<typename ForwardIt>
    inline constexpr size_type operator() (ForwardIt begin, ForwardIt end) const {
        return std::distance(begin, std::min_element(begin, end));
    }
};
struct max {
    typedef std::size_t size_type;

    template<typename V>
    inline constexpr size_type operator() (const V& vec) const {
        auto b = std::begin(vec), e = std::end(vec);
        return this->operator ()(b, e);
    }
    template<typename ForwardIt>
    inline constexpr size_type operator() (ForwardIt begin, ForwardIt end) const {
        return std::distance(begin, std::max_element(begin, end));
    }
};
struct minmax {
    typedef std::size_t size_type;

    template<typename V>
    inline constexpr std::pair<size_type, size_type> operator() (const V& vec) const {
        auto b = std::begin(vec), e = std::end(vec);
        return this->operator ()(b, e);
    }
    template<typename ForwardIt>
    inline constexpr std::pair<size_type, size_type> operator() (ForwardIt begin, ForwardIt end) const {
        auto minmax = std::minmax_element(begin, end);
        return std::make_pair(std::distance(begin, minmax.first), std::distance(begin, minmax.second));
    }
};

}   //-- namespace algorithm --


#endif /* LIB_ALGORITHM_MINMAX_HPP_ */
