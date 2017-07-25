/*
 * numeric_coder.hpp
 *
 *  Created on: Jul 14, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_HPP_
#define LIB_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_HPP_


#include <cstddef>
#include <cmath>
#include <array>
#include <bits/stl_function.h>
#include <algorithm>


#include "../../../utility/array.hpp"
#include "../../../utility/function.hpp"


namespace genetic_algorithm {
namespace common {
namespace coding {


template<typename T, std::size_t N>
inline std::array<T, N> calc_interval_sizes(
        const std::array<std::size_t, N>& geneSize,
        const std::array<T, N>& leftBounds,
        const std::array<T, N>& rightBounds)
{
    using utility::array::op;
    std::size_t intervalNumber = op(std::minus<std::size_t>{},
            op(utility::function::bit_shift_left<std::size_t>{}, 1, geneSize), 1);
    std::array<T, N> dimSize = op(std::minus<T>{}, rightBounds, leftBounds);
    std::array<T, N> intervalSize = op(std::divides<T>{}, dimSize, intervalNumber);
    return intervalSize;
};


template<typename T1, typename T2, std::size_t N>
class numeric_coder {
public:
    typedef T1 fp_type;
    typedef T2 nm_type;
    constexpr static std::size_t space_size = N;
    typedef std::array<nm_type, space_size> array_nm_type;
    typedef std::array<fp_type, space_size> array_fp_type;

    inline constexpr numeric_coder(
            const std::size_t geneSize,
            const array_fp_type& leftBounds,
            const array_fp_type& rightBounds) noexcept :
        mLeftBounds {},
        mIntervalSizes {}
    {
        mLeftBounds = leftBounds;
        mIntervalSizes = cals_interval_sizes(utility::array::fill<std::size_t, space_size>(geneSize), leftBounds, rightBounds);
    };

    inline constexpr numeric_coder(
            const std::array<std::size_t, space_size>& geneSizes,
            const array_fp_type& leftBounds,
            const array_fp_type& rightBounds) noexcept :
        mLeftBounds {},
        mIntervalSizes {}
    {
        mLeftBounds = leftBounds;
        mIntervalSizes = cals_interval_sizes(geneSizes, leftBounds, rightBounds);
    };

    inline constexpr const array_fp_type&
    left_bounds() const {
        return mLeftBounds;
    };
    inline constexpr array_fp_type&
    left_bounds() {
        return mLeftBounds;
    };

    inline constexpr const array_fp_type&
    interval_sizes() const {
        return mIntervalSizes;
    };
    inline constexpr array_fp_type&
    interval_sizes() {
        return mIntervalSizes;
    };

    constexpr array_nm_type encode(const array_fp_type& point) const {
        using utility::array::op;
        array_fp_type scaledPoint = op(std::divides<fp_type>{},
                op(std::minus<fp_type>{}, point, left_bounds()), interval_sizes());
        array_nm_type numericCodes = utility::array::map([](fp_type x) {return nm_type{std::round(x)};}, scaledPoint);
        return numericCodes;
    };

    constexpr array_fp_type decode(const array_nm_type& numericCodes) const {
        using utility::array::op;
        array_fp_type point = op(std::plus<fp_type>{},
                left_bounds(), op(std::multiplies<fp_type>{},
                        interval_sizes(), numericCodes));
        return point;
    };

private:
    array_fp_type mLeftBounds, mIntervalSizes;

};  //-- class numeric_coder --

};  //-- namespace coding --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --

#endif /* LIB_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_HPP_ */
