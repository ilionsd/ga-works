/*
 * generator.hpp
 *
 *  Created on: Jul 18, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_COMMON_GENERATING_BASE_GENERATOR_HPP_
#define LIB_GENETIC_ALGORITHM_COMMON_GENERATING_BASE_GENERATOR_HPP_

#include <cstddef>
#include <random>
#include <array>

namespace genetic_algorithm {
namespace common {
namespace generating {

template<typename T, std::size_t SpaceSize>
class base_generator {
public:
    typedef T value_type;
    constexpr static std::size_t space_size = SpaceSize;
    typedef std::array<value_type, space_size> array_type;

    inline constexpr base_generator(const value_type leftBound, const value_type rightBound) :
            mGenerator {},
            mLeftBounds {},
            mRightBounds {}
    {
        mLeftBounds.fill(leftBound);
        mRightBounds.fill(rightBound);
    };
    inline constexpr base_generator(const array_type& leftBounds, const value_type rightBound) :
            mGenerator {},
            mLeftBounds {},
            mRightBounds {}
    {
        mLeftBounds = leftBounds;
        mRightBounds.fill(rightBound);
    };
    inline constexpr base_generator(const value_type leftBound, const array_type& rightBounds) :
            mGenerator {},
            mLeftBounds {},
            mRightBounds {}
    {
        mLeftBounds.fill(leftBound);
        mRightBounds = rightBounds;
    };
    inline constexpr base_generator(const array_type& leftBounds, const array_type& rightBounds) :
            mGenerator {},
            mLeftBounds {},
            mRightBounds {}
    {
        mLeftBounds = leftBounds;
        mRightBounds = rightBounds;
    };

    inline constexpr std::mt19937_64& generator() const {
        return mGenerator;
    };

    inline constexpr const array_type& left_bounds() const {
        return mLeftBounds;
    };
    inline constexpr const array_type& right_bounds() const {
        return mRightBounds;
    };


private:
    mutable std::mt19937_64 mGenerator;
    array_type mLeftBounds, mRightBounds;

};

};  //-- namespace generating --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --


#endif /* LIB_GENETIC_ALGORITHM_COMMON_GENERATING_BASE_GENERATOR_HPP_ */
