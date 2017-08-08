/*
 * gray_coder.hpp
 *
 *  Created on: Jul 14, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_COMMON_CODING_GRAY_CODER_HPP_
#define LIB_GENETIC_ALGORITHM_COMMON_CODING_GRAY_CODER_HPP_

#include <cassert>
#include <cstddef>
#include <type_traits>
#include <valarray>
#include <vector>
#include <numeric>


#include "../../../types/primitive.hpp"
#include "../../../utility/valarray.hpp"
#include "../../../utility/stlmath.hpp"
#include "../space.hpp"


namespace genetic_algorithm {
namespace common {
namespace coding {

template<typename T>
class gray_coder {
public:
    typedef types::unsigned_integer_t<T> uint_type;
    typedef ::genetic_algorithm::common::uint_space<uint_type> uint_space_type;
    typedef std::valarray<uint_type> uint_vector_type;
    typedef std::vector<bool>        code_vector_type;

    inline constexpr gray_coder(const uint_space_type& space) noexcept :
        mUintSpace ( space ),
        mGeneSizes ( space.size() )
    {
        typedef typename uint_space_type::size_type size_type;
        for (size_type dim = 0; dim < space.size(); ++dim) {
            namespace math = ::utility::stlmath;
            mGeneSizes[dim] = size_type(
                    math::ceil<double>()(
                            math::log2<double>()(space.right_bounds()[dim])
                    )
            );
        }
    }

    inline constexpr const uint_space_type&
    uint_space() const {
        return mUintSpace;
    }
    inline constexpr const std::valarray<std::size_t>&
    gene_sizes() const {
        return mGeneSizes;
    }

    inline constexpr auto code_coder() const
    -> std::function<code_vector_type(const uint_vector_type&)> {
        return [this](const uint_vector_type& icode) -> code_vector_type { return this->to_code(icode); };
    }
    inline constexpr auto uint_coder() const
    -> std::function<uint_vector_type(const code_vector_type&)> {
        return [this](const code_vector_type& gcode) -> uint_vector_type { return this->to_uint(gcode); };
    }

    constexpr code_vector_type
    to_code(const uint_vector_type& icode) const {
        assert(icode.size() == uint_space().size());
        std::size_t codeSize = gene_sizes().sum();
        code_vector_type gcode ( codeSize );
        std::size_t geneIndex = 0;
        for (std::size_t dim = 0; dim < uint_space().size(); ++dim) {
            uint_type div = icode[dim];
            uint_type prevRem = div & 0x1;
            for (std::size_t bitIndex = 0; bitIndex < gene_sizes()[dim]; ++bitIndex) {
                div >>= 1;
                uint_type nextRem = div & 0x1;
                gcode[geneIndex + bitIndex] = bool(nextRem ^ prevRem);
                prevRem = nextRem;
            }
            geneIndex += gene_sizes()[dim];
        }
        return gcode;
    }

    constexpr uint_vector_type
    to_uint(const code_vector_type& gcode) const {
        uint_vector_type icode ( uint_space().size() );
        std::size_t geneIndex = 0;
        for (std::size_t dim = 0; dim < uint_space().size(); ++dim) {
            uint_type num = 0;
            bool sum = 0;
            geneIndex += gene_sizes()[dim];
            for (std::size_t bitIndex = 0; bitIndex < gene_sizes()[dim]; ++bitIndex) {
                sum ^= gcode[geneIndex - 1 - bitIndex];
                num <<= 1;
                num += sum;
            }
            icode[dim] = num;
        }
        return icode;
    }

private:
    const uint_space_type& mUintSpace;
    std::valarray<std::size_t> mGeneSizes;

};  //-- class gray_coder --

}   //-- namespace coding --
}   //-- namespace common --
}   //-- namespace genetic_algorithm --

#endif /* LIB_GENETIC_ALGORITHM_COMMON_CODING_GRAY_CODER_HPP_ */
