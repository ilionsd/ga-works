/*
 * generator.hpp
 *
 *  Created on: Jul 18, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_COMMON_GENERATING_BASE_GENERATOR_HPP_
#define LIB_GENETIC_ALGORITHM_COMMON_GENERATING_BASE_GENERATOR_HPP_

#include <cstddef>
#include <cassert>
#include <random>
#include <valarray>
#include <algorithm>


#include "../space.hpp"


namespace genetic_algorithm {
namespace common {
namespace generating {

template<typename T>
class base_generator {
public:
    typedef T value_type;
    typedef ::genetic_algorithm::common::space<value_type> space_type;
    typedef typename space_type::vector_type vector_type;

    inline constexpr base_generator(
            const space_type& space) :
        mGenerator ( std::mt19937_64( std::random_device()() ) ),
        mSpace ( space )
    {}
    inline constexpr base_generator(
            const space_type& space,
            std::mt19937_64& generator) :
        mGenerator ( generator ),
        mSpace ( space )
    {}

    inline constexpr std::mt19937_64&
    generator() const {
        return mGenerator;
    }

    inline constexpr const space_type&
    space() const {
        return mSpace;
    }

private:
    mutable std::mt19937_64 mGenerator;
    const space_type& mSpace;

};

}   //-- namespace generating --
}   //-- namespace common --
}   //-- namespace genetic_algorithm --


#endif /* LIB_GENETIC_ALGORITHM_COMMON_GENERATING_BASE_GENERATOR_HPP_ */
