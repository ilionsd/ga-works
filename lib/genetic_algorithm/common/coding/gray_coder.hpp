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
#include <numeric>

#include "../../../types/primitive_types.hpp"
#include "../../../utility/valarray.hpp"

namespace genetic_algorithm {
namespace common {
namespace coding {

template<typename T>
class gray_coder {
public:
    typedef types::unsigned_integer_t<T> numeric_type;
    typedef std::valarray<numeric_type> array_type;

    inline constexpr gray_coder(const std::size_t spaceSize, const std::size_t geneSize) noexcept :
        mGeneSizes { geneSize, spaceSize }
    {};
    inline constexpr gray_coder(const std::valarray<std::size_t>& geneSizes) noexcept :
        mGeneSizes { geneSizes }
    {};

    inline constexpr std::size_t space_size() const {
        return gene_sizes().size();
    };
    inline constexpr const std::valarray<std::size_t>&
    gene_sizes() const {
        return mGeneSizes;
    };

    constexpr std::valarray<bool> encode(const array_type& ncode) const {
        assert(ncode.size() == space_size());

        std::size_t codeSize = utility::valarray::reduce(std::plus<numeric_type>{}, gene_sizes());
        std::valarray<bool> gcode {codeSize};

        std::size_t geneIndex = 0;
        for (std::size_t dim = 0; dim < space_size; ++dim) {
            numeric_type div = ncode[dim];
            numeric_type prevRem = div & 0x1;
            for (std::size_t bitIndex = 0; bitIndex < gene_sizes()[dim]; ++bitIndex) {
                div >>= 1;
                T nextRem = div & 0x1;
                gcode[geneIndex + bitIndex] = bool(nextRem ^ prevRem);
            }
            geneIndex += gene_sizes()[dim];
        }

        return gcode;
    };

    constexpr array_type decode(const std::valarray<bool>& gcode) const {
        array_type ncode {space_size()};

        std::size_t geneIndex = 0;
        for (std::size_t dim = 0; dim < space_size; ++dim) {
            numeric_type num = 0;
            bool sum = 0;
            geneIndex += gene_sizes()[dim];
            for (std::size_t bitIndex = 0; bitIndex < gene_sizes()[dim]; ++bitIndex) {
                sum ^= gcode[geneIndex - 1 - bitIndex];
                num <<= 1;
                num += sum;
            }
            ncode[dim] = num;
        }

        return ncode;
    };

private:
    std::valarray<std::size_t> mGeneSizes;

};  //-- class gray_coder --

};  //-- namespace coding --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --

#endif /* LIB_GENETIC_ALGORITHM_COMMON_CODING_GRAY_CODER_HPP_ */
