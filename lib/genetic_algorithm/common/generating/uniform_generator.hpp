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
    typedef typename base_type::space_type space_type;
    typedef typename base_type::vector_type vector_type;
    typedef typename std::conditional_t<std::is_floating_point<value_type>::value,
            types::incomplete<std::uniform_real_distribution>,
            types::incomplete<std::uniform_int_distribution>>::template type<value_type> distribution_type;

    using base_type::base_type;
    using base_type::generator;
    using base_type::space;

    inline auto operator() (const std::size_t amount) const -> std::vector<vector_type> {
        std::vector<vector_type> v ( amount, vector_type( space().size() ) );
        for (std::size_t dim = 0; dim < space().size(); ++dim) {
            value_type a = std::min( space().left_bounds()[dim], space().right_bounds()[dim] ),
                    b = std::max( space().left_bounds()[dim], space().right_bounds()[dim] );
            distribution_type dist { a, b };
            for (auto& el : v)
                el[dim] = dist( generator() );
        }
        return v;
    };

};  //-- class uniform_generator --


};  //-- namespace generating --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --


#endif /* LIB_GENETIC_ALGORITHM_COMMON_GENERATING_UNIFORM_GENERATOR_HPP_ */
