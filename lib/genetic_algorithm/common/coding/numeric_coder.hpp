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
#include <functional>
#include <algorithm>
#include <type_traits>
#include <tuple>


#include "../../../types/primitive.hpp"
#include "../../../utility/valarray.hpp"
#include "../../../utility/stlmath.hpp"
#include "../space.hpp"


namespace genetic_algorithm {
namespace common {
namespace coding {


template<typename T1, typename T2>
class numeric_coder {
public:
    typedef std::conditional_t<std::is_floating_point<T1>::value,
            T1,
            std::conditional_t<std::is_floating_point<T2>::value, T2, void>> real_type;
    typedef std::conditional_t<std::is_unsigned<T1>::value,
            T1,
            std::conditional_t<std::is_unsigned<T2>::value, T2, void>> uint_type;

    static_assert(!std::is_void<real_type>::value, "Invalid Real type");
    static_assert(!std::is_void<uint_type>::value, "Invalid UInt type");

    typedef ::genetic_algorithm::common::space<real_type> real_space_type;
    typedef ::genetic_algorithm::common::space<uint_type> uint_space_type;
    typedef typename real_space_type::vector_type real_vector_type;
    typedef typename uint_space_type::vector_type uint_vector_type;

    inline constexpr numeric_coder(
            const ::genetic_algorithm::common::space<T1>& space1,
            const ::genetic_algorithm::common::space<T2>& space2) :
        mSpaces (space1, space2),
        mIntervalSizes ()
    {
        assert(space1.size() == space2.size());
        mIntervalSizes = (real_space().right_bounds() - real_space().left_bounds()) / utility::valarray::convert_to<real_type>(uint_space().right_bounds());
    }

    inline constexpr const real_space_type&
    real_space() const {
        return std::get<real_space_type>(mSpaces);
    }
    inline constexpr const uint_space_type&
    uint_space() const {
        return std::get<uint_space_type>(mSpaces);
    }
    inline constexpr const real_vector_type&
    interval_sizes() const {
        return mIntervalSizes;
    }

    inline constexpr auto uint_coder() const
    -> std::function<uint_vector_type(const real_vector_type&)> {
        return [this](const real_vector_type& point) -> uint_vector_type { return this->to_uint(point); };
    }
    inline constexpr auto real_coder() const
    -> std::function<real_vector_type(const uint_vector_type&)> {
        return [this](const uint_vector_type& icode) -> real_vector_type { return this->to_real(icode); };
    }

    constexpr uint_vector_type
    to_uint(const real_vector_type& point) const {
        using utility::valarray::convert_to;
        using utility::valarray::round;
        real_vector_type scaledPoint = (point - real_space().left_bounds()) / interval_sizes();
        uint_vector_type icode = convert_to<uint_type>(round(scaledPoint));
        return icode;
    }
    constexpr real_vector_type
    to_real(const uint_vector_type& icode) const {
        real_vector_type scaledPoint = utility::valarray::convert_to<real_type>(icode);
        real_vector_type point = real_space().left_bounds() + scaledPoint * interval_sizes();
        return point;
    }

private:
    std::tuple<space<T1>, space<T2>> mSpaces;
    real_vector_type mIntervalSizes;

};  //-- class numeric_coder --

}   //-- namespace coding --
}   //-- namespace common --
}   //-- namespace genetic_algorithm --

#endif /* LIB_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_HPP_ */
