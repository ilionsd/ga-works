/*
 * generate.hpp
 *
 *  Created on: Jul 15, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_COMMON_GENERATING_UNIFORM_GENERATOR_HPP_
#define LIB_GENETIC_ALGORITHM_COMMON_GENERATING_UNIFORM_GENERATOR_HPP_


#include <cstddef>
#include <valarray>
#include <random>
#include <type_traits>


#include "base_generator.hpp"


namespace genetic_algorithm {
namespace common {
namespace generating {

template<typename T, std::size_t SpaceSize>
class uniform_generator :
        public base_generator<T, SpaceSize>
{
public:
    typedef T value_type;
    constexpr static std::size_t space_size = SpaceSize;

    typedef base_generator<value_type, space_size> base_type;

    using base_type::base_type;
    using base_type::left_bounds;
    using base_type::right_bounds;
    using base_type::generator;

    inline auto operator() (const std::size_t amount) const {
        return generate(amount);
    };

    std::vector<std::array<value_type, space_size>> generate(const std::size_t amount) const {
        std::vector<std::array<value_type, space_size>> v { amount, std::array<value_type, space_size>{} };
        for (std::size_t dim = 0; dim < space_size; ++dim) {
            value_type a = std::min( left_bounds()[dim], right_bounds()[dim] ),
                    b = std::max( left_bounds()[dim], right_bounds()[dim] );
            std::conditional_t<std::is_same<value_type, double>::value,
                std::uniform_real_distribution<value_type>,
                std::uniform_int_distribution<value_type>> dist { a, b };
            for (auto& el : v)
                el[dim] = dist( generator() );
        }
        return v;
    };

};  //-- class uniform_generator --

template<std::size_t SpaceSize, typename T>
inline constexpr uniform_generator<T, SpaceSize> make_uniform(const T leftBound, const T rightBound) {
    return uniform_generator<T, SpaceSize> { leftBound, rightBound };
};
template<std::size_t SpaceSize, typename T>
inline constexpr uniform_generator<T, SpaceSize> make_uniform(
        const std::array<T, SpaceSize>& leftBounds,
        const std::array<T, SpaceSize>& rightBounds) {
    return uniform_generator<T, SpaceSize> { leftBounds, rightBounds };
}

};  //-- namespace generating --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --


#endif /* LIB_GENETIC_ALGORITHM_COMMON_GENERATING_UNIFORM_GENERATOR_HPP_ */
