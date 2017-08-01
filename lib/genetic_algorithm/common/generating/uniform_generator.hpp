/*
 * generate.hpp
 *
 *  Created on: Jul 15, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_COMMON_GENERATING_UNIFORM_GENERATOR_HPP_
#define LIB_GENETIC_ALGORITHM_COMMON_GENERATING_UNIFORM_GENERATOR_HPP_


#include <cstddef>
#include <array>
#include <valarray>
#include <random>
#include <type_traits>


#include "base_generator.hpp"
#include "../../../types/incomplete.hpp"
#include "../../../utility/valarray.hpp"


namespace genetic_algorithm {
namespace common {
namespace generating {

template<typename T>
class uniform_generator :
        public base_generator<T>
{
public:
    typedef T value_type;
    typedef base_generator<value_type> base_type;
    typedef typename std::conditional_t<std::is_floating_point<value_type>::value,
            types::incomplete<std::uniform_real_distribution>,
            types::incomplete<std::uniform_int_distribution>>::template type<value_type> distribution_type;

    using base_type::base_type;
    using base_type::space_size;
    using base_type::left_bounds;
    using base_type::right_bounds;
    using base_type::generator;

    inline auto operator() (const std::size_t amount) const {
        std::vector<std::valarray<value_type>> v ( amount, std::valarray<value_type>( space_size() ) );
        for (std::size_t dim = 0; dim < space_size(); ++dim) {
            value_type a = std::min( left_bounds()[dim], right_bounds()[dim] ),
                    b = std::max( left_bounds()[dim], right_bounds()[dim] );
            distribution_type dist { a, b };
            for (auto& el : v)
                el[dim] = dist( generator() );
        }
        return v;
    };

};  //-- class uniform_generator --

template<typename T>
inline constexpr uniform_generator<T> make_uniform(
        const std::size_t spaceSize,
        const T leftBound,
        const T rightBound) {
    return uniform_generator<T> ( spaceSize, leftBound, rightBound );
}
template<typename T>
inline constexpr uniform_generator<T> make_uniform(
        const std::size_t spaceSize,
        const std::valarray<T>& leftBounds,
        const std::valarray<T>& rightBounds) {
    return uniform_generator<T> ( spaceSize, leftBounds, rightBounds );
}

};  //-- namespace generating --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --


#endif /* LIB_GENETIC_ALGORITHM_COMMON_GENERATING_UNIFORM_GENERATOR_HPP_ */
