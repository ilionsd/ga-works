/*
 * euclidean_distance.hpp
 *
 *  Created on: Aug 14, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_MATH_EUCLIDEAN_DISTANCE_HPP_
#define LIB_UTILITY_MATH_EUCLIDEAN_DISTANCE_HPP_


#include <cassert>
#include "../../../include/fn/math.hpp"

namespace utility {
namespace math {

template<typename T>
struct euclidean_distance {
    typedef T value_type;

    template<typename V>
    inline constexpr value_type operator() (const V& v1, const V& v2) const {
        assert(v1.size() == v2.size());
        value_type sum = 0;
        for (std::size_t k = 0; k < v1.size(); ++k)
            sum += (v1[k] - v2[k]) * (v1[k] - v2[k]);
        return ::fn::math::sqrt<value_type>()( sum );
    }
};

}   //-- namespace math --
}   //-- namespace utility --


#endif /* LIB_UTILITY_MATH_EUCLIDEAN_DISTANCE_HPP_ */
