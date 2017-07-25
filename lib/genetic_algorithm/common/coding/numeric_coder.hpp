/*
 * numeric_coder.hpp
 *
 *  Created on: Jul 14, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_HPP_
#define LIB_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_HPP_

#include <cassert>
#include <cstddef>
#include <cmath>
#include <valarray>
#include <algorithm>

namespace genetic_algorithm {
namespace common {
namespace coding {

template<typename T, std::size_t SpaceSize>
class numeric_coder {
public:
    typedef T numeric_type;
    constexpr static std::size_t space_size = SpaceSize;

    inline constexpr numeric_coder(
            const std::size_t geneSize,
            const std::valarray<double> leftBounds,
            const std::valarray<double> rightBounds) noexcept :
        mLeftBounds {leftBounds},
        mIntervalSizes {}
    {
        assert(leftBounds.size() == space_size);
        assert(rightBounds.size() == space_size);
        mIntervalSizes = (rightBounds - leftBounds) / ((1 << geneSize) - 1);
    };

    inline constexpr numeric_coder(
            const std::valarray<std::size_t>& geneSizes,
            const std::valarray<double> leftBounds,
            const std::valarray<double> rightBounds) noexcept :
        mLeftBounds {leftBounds},
        mIntervalSizes {}
    {
        assert(leftBounds.size() == space_size);
        assert(rightBounds.size() == space_size);
        mIntervalSizes = (rightBounds - leftBounds) / ((1 << geneSizes) - 1);
    };

    inline constexpr const std::valarray<numeric_type>&
    left_bounds() const {
        return mLeftBounds;
    };
    inline constexpr std::valarray<numeric_type>&
    left_bounds() {
        return mLeftBounds;
    };

    inline constexpr const std::valarray<numeric_type>&
    interval_sizes() const {
        return mIntervalSizes;
    };
    inline constexpr std::valarray<numeric_type>&
    interval_sizes() {
        return mIntervalSizes;
    };

    constexpr std::valarray<numeric_type> encode(const std::valarray<double>& point) const {
        std::valarray<double> scaledPoint = ((point - left_bounds()) / interval_sizes());
        std::valarray<numeric_type> numericCodes {space_size};
        std::transform(std::begin(scaledPoint), std::end(scaledPoint), std::begin(numericCodes), std::round);
        return numericCodes;
    };

    constexpr std::valarray<double> decode(const std::valarray<numeric_type>& numericCodes) const {
        return left_bounds() + numericCodes * interval_sizes();
    };

private:
    std::valarray<double> mLeftBounds, mIntervalSizes;

};  //-- class numeric_coder --

};  //-- namespace coding --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --

#endif /* LIB_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_HPP_ */
