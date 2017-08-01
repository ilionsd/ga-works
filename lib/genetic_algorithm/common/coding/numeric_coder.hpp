/*
 * numeric_coder.hpp
 *
 *  Created on: Jul 14, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_HPP_
#define LIB_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_HPP_


#include <cstddef>
#include <cassert>
#include <cmath>
#include <valarray>
#include <bits/stl_function.h>
#include <algorithm>


#include "../../../types/primitive_types.hpp"
#include "../../../utility/valarray.hpp"
#include "../../../utility/stlmath.hpp"


namespace genetic_algorithm {
namespace common {
namespace coding {


template<typename SrcT, typename DstT>
class numeric_coder {
public:
    typedef types::floating_point_t<SrcT>   fp_type;
    typedef types::unsigned_integer_t<DstT> nm_type;
    typedef std::valarray<nm_type> array_nm_type;
    typedef std::valarray<fp_type> array_fp_type;

    inline constexpr numeric_coder(
            const std::size_t geneSize,
            const array_fp_type& leftBounds,
            const array_fp_type& rightBounds) :
        mSpaceSize { leftBounds.size() },
        mLeftBounds { leftBounds },
        mIntervalSizes {}
    {
        assert(leftBounds.size() == rightBounds.size());
        mIntervalSizes = (rightBounds - leftBounds) / ((1ul << geneSize) - 1ul);
    };

    inline constexpr numeric_coder(
            const std::valarray<std::size_t>& geneSizes,
            const array_fp_type& leftBounds,
            const array_fp_type& rightBounds) :
        mSpaceSize { leftBounds.size() },
        mLeftBounds { leftBounds },
        mIntervalSizes {}
    {
        assert(geneSizes.size() == leftBounds.size());
        assert(leftBounds.size() == rightBounds.size());
        mIntervalSizes = (rightBounds - leftBounds) / utility::valarray::convert_to<fp_type>((1ul << geneSizes) - 1ul);
    };

    inline constexpr std::size_t space_size() const {
        return mSpaceSize;
    };
    inline constexpr const array_fp_type&
    left_bounds() const {
        return mLeftBounds;
    };
    inline constexpr const array_fp_type&
    interval_sizes() const {
        return mIntervalSizes;
    };

    constexpr array_nm_type encode(const array_fp_type& point) const {
        using utility::valarray::convert_to;
        using utility::valarray::round;
        array_fp_type scaledPoint = (point - left_bounds()) / interval_sizes();
        array_nm_type code = convert_to<nm_type>(round(scaledPoint));
        return code;
    };
    constexpr array_fp_type decode(const array_nm_type& code) const {
        array_fp_type scaledPoint = utility::valarray::convert_to<fp_type>(code);
        array_fp_type point = left_bounds() + scaledPoint * interval_sizes();
        return point;
    };

private:
    std::size_t mSpaceSize;
    array_fp_type mLeftBounds, mIntervalSizes;

};  //-- class numeric_coder --

};  //-- namespace coding --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --

#endif /* LIB_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_HPP_ */
