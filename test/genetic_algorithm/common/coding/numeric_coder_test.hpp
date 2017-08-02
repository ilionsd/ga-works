/*
 * numeric_coder_test.hpp
 *
 *  Created on: Jul 18, 2017
 *      Author: ilion
 */

#ifndef TEST_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_TEST_HPP_
#define TEST_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_TEST_HPP_


#include <cstddef>
#include <cassert>
#include <tuple>
#include <array>
#include <valarray>
#include <type_traits>

#include "../../../../lib/utility/valarray.hpp"
#include "../../../../lib/utility/vector.hpp"
#include "../../../../lib/utility/stlmath.hpp"

#include "../../../../lib/genetic_algorithm/common/generating/uniform_generator.hpp"
#include "../../../../lib/genetic_algorithm/common/coding/encoder.hpp"
#include "../../../../lib/genetic_algorithm/common/coding/decoder.hpp"
#include "../../../../lib/genetic_algorithm/common/coding/numeric_coder.hpp"


namespace test {
namespace genetic_algorithm {
namespace common {
namespace coding {

struct numeric_coder_test {
    static constexpr auto test_cases = std::make_tuple(
            std::make_tuple(
                    ::utility::array::make_of<std::size_t>(5, 5, 6, 3, 10),
                    ::utility::array::make_of<double>( 0.0, 10.0,  1.0, 9.00, -1.0),
                    ::utility::array::make_of<double>(20.0, 30.0, 15.0, 9.99,  1.0),
                    std::size_t(1000)
            ),
            std::make_tuple(
                    ::utility::array::make_of<std::size_t>(5, 5, 6, 3, 10),
                    ::utility::array::make_of<unsigned long>( 0,  0,  0, 0,    0),
                    ::utility::array::make_of<unsigned long>(31, 31, 63, 7, 1023),
                    std::size_t(1000)
            )
    );

    template<typename... Ts>
    constexpr void operator() (const std::tuple<Ts...>& testCase) const {
        auto geneSizes   = convert_if_array(std::get<0>(testCase));
        auto leftBounds  = convert_if_array(std::get<1>(testCase));
        auto rightBounds = convert_if_array(std::get<2>(testCase));
        auto amount = std::get<3>(testCase);

        std::size_t spaceSize = geneSizes.size();

        auto generator = ::genetic_algorithm::common::generating::make_uniform(spaceSize, leftBounds, rightBounds);

        typedef typename decltype(generator)::value_type generator_type;
        selector<generator_type, std::remove_reference_t<decltype(geneSizes)>>{}(generator, geneSizes, amount);
    };

    template<typename T1, typename T2>
    struct selector;

    template<typename T, std::size_t N>
    constexpr auto convert_if_array(const std::array<T, N>& arr) const -> std::valarray<T> {
        return ::utility::valarray::from(arr);
    }
    template<typename T>
    constexpr auto convert_if_array(const T val) const -> T {
        return val;
    }


};  //-- struct numeric_coder_test --

constexpr decltype(numeric_coder_test::test_cases) numeric_coder_test::test_cases;


template<typename T2>
struct numeric_coder_test::selector<double, T2> {
    void operator() (
        const ::genetic_algorithm::common::generating::uniform_generator<double>& generator,
        const T2& geneSizes,
        const std::size_t amount) const
    {
        typedef double        src_type;
        typedef unsigned long dst_type;

        std::vector<std::valarray<src_type>> ref = generator(amount);

        namespace code = ::genetic_algorithm::common::coding;
        code::numeric_coder<src_type, dst_type> coder ( geneSizes, generator.left_bounds(), generator.right_bounds() );
        auto enc = ::utility::vector::map(coder.encoder(), ref);
        auto dec = ::utility::vector::map(coder.decoder(), enc);

        for (std::size_t k = 0; k < amount; ++k) {
            std::valarray<bool> cmp = std::abs(ref[k] - dec[k]) < (coder.interval_sizes() / 2.0);
            bool result = ::utility::valarray::reduce(std::logical_and<bool>{}, cmp);
            assert(result);
        }
    }
};

template<typename T2>
struct numeric_coder_test::selector<unsigned long, T2> {
    void operator() (
        const ::genetic_algorithm::common::generating::uniform_generator<unsigned long>& generator,
        const T2& geneSizes,
        const std::size_t amount) const
    {
        typedef unsigned long src_type;
        typedef double        dst_type;

        std::vector<std::valarray<src_type>> ref = generator(amount);

        namespace code = ::genetic_algorithm::common::coding;
        namespace valarr= ::utility::valarray;
        code::numeric_coder<dst_type, src_type> coder ( geneSizes, valarr::convert_to<dst_type>(generator.left_bounds()), valarr::convert_to<dst_type>(generator.right_bounds()) );
        std::vector<std::valarray<dst_type>> enc = ::utility::vector::map(coder.decoder(), ref);
        std::vector<std::valarray<src_type>> dec = ::utility::vector::map(coder.encoder(), enc);

        for (std::size_t k = 0; k < amount; ++k) {
            std::valarray<bool> cmp = ref[k] == dec[k];
            bool result = utility::valarray::reduce(std::logical_and<bool>{}, cmp);
            assert(result);
        }
    }
};

};  //-- namespace coding --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --
};  //-- namespace test --


#endif /* TEST_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_TEST_HPP_ */
