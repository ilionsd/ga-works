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
#include <array>
#include <valarray>
#include <numeric>

namespace genetic_algorithm {
namespace common {
namespace coding {

template<typename T, std::size_t SpaceSize>
class gray_coder {
public:
    typedef T numeric_type;
    constexpr static std::size_t space_size = SpaceSize;
    typedef std::array<numeric_type, space_size> array_type;

    static_assert(std::is_unsigned<numeric_type>::value, "Numeric type should be unsigned");

    inline constexpr gray_coder(const numeric_type geneSize) noexcept :
        mGeneSizes {geneSize, space_size}
    {};
    inline constexpr gray_coder(const array_type& geneSizes) noexcept :
        mGeneSizes {geneSizes}
    {};

    inline constexpr const array_type&
    gene_sizes() const {
        return mGeneSizes;
    };
    inline constexpr array_type&
    gene_sizes() {
        return mGeneSizes;
    };

    constexpr std::vector<bool> encode(const array_type& numericCodes) const {
        assert(numericCodes.size() == space_size);

        std::size_t codeSize = std::accumulate(std::begin(gene_sizes()), std::end(gene_sizes()), 0);
        std::vector<bool> grayCodes {codeSize};

        std::size_t geneIndex = 0;
        for (std::size_t dim = 0; dim < space_size; ++dim) {
            numeric_type div = numericCodes[dim];
            numeric_type prevRem = div & 0x1;
            for (std::size_t bitIndex = 0; bitIndex < gene_sizes()[dim]; ++bitIndex) {
                div >>= 1;
                T nextRem = div & 0x1;
                grayCodes[geneIndex + bitIndex] = bool(nextRem ^ prevRem);
            }
            geneIndex += gene_sizes()[dim];
        }

        return grayCodes;
    };

    constexpr array_type decode(const std::vector<bool>& grayCodes) const {
        array_type numericCodes {space_size};

        std::size_t geneIndex = 0;
        for (std::size_t dim = 0; dim < space_size; ++dim) {
            numeric_type num = 0;
            bool sum = 0;
            geneIndex += gene_sizes()[dim];
            for (std::size_t bitIndex = 0; bitIndex < gene_sizes()[dim]; ++bitIndex) {
                sum ^= grayCodes[geneIndex - 1 - bitIndex];
                num <<= 1;
                num += sum;
            }
            numericCodes[dim] = num;
        }

        return numericCodes;
    };

private:
    array_type mGeneSizes;

};  //-- class gray_coder --

};  //-- namespace coding --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --

#endif /* LIB_GENETIC_ALGORITHM_COMMON_CODING_GRAY_CODER_HPP_ */
