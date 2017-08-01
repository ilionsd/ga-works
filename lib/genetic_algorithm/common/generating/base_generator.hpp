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

namespace genetic_algorithm {
namespace common {
namespace generating {

template<typename T>
class base_generator {
public:
    typedef T value_type;
    typedef std::valarray<value_type> array_type;

    inline constexpr base_generator(const std::size_t spaceSize, const value_type leftBound, const value_type rightBound) :
            mGenerator (),
            mSpaceSize ( spaceSize ),
            mLeftBounds  ( leftBound , spaceSize ),
            mRightBounds ( rightBound, spaceSize )
    {};
    inline constexpr base_generator(const std::size_t spaceSize, const array_type& leftBounds, const array_type& rightBounds) :
            mGenerator (),
            mSpaceSize ( spaceSize ),
            mLeftBounds  ( leftBounds  ),
            mRightBounds ( rightBounds )
    {
        assert(mSpaceSize == mLeftBounds .size());
        assert(mSpaceSize == mRightBounds.size());
    };

    inline constexpr std::mt19937_64& generator() const {
        return mGenerator;
    };

    inline constexpr std::size_t space_size() const {
        return mSpaceSize;
    };

    inline constexpr const array_type& left_bounds() const {
        return mLeftBounds;
    };
    inline constexpr const array_type& right_bounds() const {
        return mRightBounds;
    };


private:
    mutable std::mt19937_64 mGenerator;
    std::size_t mSpaceSize;
    array_type mLeftBounds, mRightBounds;

};

};  //-- namespace generating --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --


#endif /* LIB_GENETIC_ALGORITHM_COMMON_GENERATING_BASE_GENERATOR_HPP_ */
