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
#include "../../../../lib/genetic_algorithm/common/coding/numeric_coder.hpp"
#include "../../../../lib/genetic_algorithm/common/space.hpp"


namespace test {
namespace genetic_algorithm {
namespace common {
namespace coding {

struct numeric_coder_test {
    static constexpr auto test_cases = std::make_tuple(
            std::make_tuple(
                    ::utility::array::make_of<double>( 0.0, 10.0,  1.0, 9.00, -1.0),
                    ::utility::array::make_of<double>(20.0, 30.0, 15.0, 9.99,  1.0),
                    ::utility::array::make_of<unsigned long>( 0,  0,  0, 0,    0),
                    ::utility::array::make_of<unsigned long>(31, 31, 63, 7, 1023),
                    std::size_t(1000)
            ),
            std::make_tuple(
                    ::utility::array::make_of<unsigned long>( 0,  0,  0, 0,    0),
                    ::utility::array::make_of<unsigned long>(31, 31, 63, 7, 1023),
                    ::utility::array::make_of<double>( 0.0, 10.0,  1.0, 9.00, -1.0),
                    ::utility::array::make_of<double>(20.0, 30.0, 15.0, 9.99,  1.0),
                    std::size_t(1000)
            )
    );

    template<typename... Ts>
    constexpr void operator() (const std::tuple<Ts...>& testCase) const {
        auto srcLeftBounds  = convert_if_array(std::get<0>(testCase));
        auto srcRightBounds = convert_if_array(std::get<1>(testCase));
        auto dstLeftBounds  = convert_if_array(std::get<2>(testCase));
        auto dstRightBounds = convert_if_array(std::get<3>(testCase));
        auto amount = std::get<4>(testCase);

        auto srcSpace = ::genetic_algorithm::common::make_space(srcLeftBounds, srcRightBounds);
        auto dstSpace = ::genetic_algorithm::common::make_space(dstLeftBounds, dstRightBounds);
        typedef typename decltype(srcSpace)::value_type src_type;
        typedef typename decltype(dstSpace)::value_type dst_type;

        ::genetic_algorithm::common::generating::uniform_generator<src_type> generator (srcSpace);
        ::genetic_algorithm::common::coding::numeric_coder<src_type, dst_type> coder (srcSpace, dstSpace);
        std::vector<std::valarray<src_type>> ref = generator(amount);
        std::vector<std::valarray<src_type>> dec = selector<src_type, dst_type>{}(coder, ref);
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


template<>
struct numeric_coder_test::selector<double, unsigned long> {
    auto operator() (
        const ::genetic_algorithm::common::coding::numeric_coder<double, unsigned long>& coder,
        const std::vector<std::valarray<double>>& ref) const -> std::vector<std::valarray<double>>
    {
        auto enc = ::utility::vector::map(coder.uint_coder(), ref);
        auto dec = ::utility::vector::map(coder.real_coder(), enc);

        for (std::size_t k = 0; k < ref.size(); ++k) {
            std::valarray<bool> cmp = std::abs(ref[k] - dec[k]) < (coder.interval_sizes() / 2.0);
            bool result = ::utility::valarray::reduce(std::logical_and<bool>{}, cmp);
            assert(result);
        }

        return dec;
    }
};

template<>
struct numeric_coder_test::selector<unsigned long, double> {
    auto operator() (
        const ::genetic_algorithm::common::coding::numeric_coder<unsigned long, double>& coder,
        const std::vector<std::valarray<unsigned long>>& ref) const -> std::vector<std::valarray<unsigned long>>
    {
        auto enc = ::utility::vector::map(coder.real_coder(), ref);
        auto dec = ::utility::vector::map(coder.uint_coder(), enc);

        for (std::size_t k = 0; k < ref.size(); ++k) {
            std::valarray<bool> cmp = ref[k] == dec[k];
            bool result = ::utility::valarray::reduce(std::logical_and<bool>{}, cmp);
            assert(result);
        }

        return dec;
    }
};

};  //-- namespace coding --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --
};  //-- namespace test --


#endif /* TEST_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_TEST_HPP_ */
