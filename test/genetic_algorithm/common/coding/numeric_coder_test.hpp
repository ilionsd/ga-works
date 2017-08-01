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


namespace test {
namespace genetic_algorithm {
namespace common {
namespace coding {

struct numeric_coder_test {
    static constexpr auto test_cases = std::make_tuple(
            std::make_tuple(
                    utility::array::make_of<std::size_t>(5, 5, 6, 3, 10),
                    utility::array::make_of<double>( 0.0, 10.0,  1.0, 9.00, -1.0),
                    utility::array::make_of<double>(20.0, 30.0, 15.0, 9.99,  1.0),
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

        namespace gen = ::genetic_algorithm::common::generating;
        auto dGen = gen::make_uniform(spaceSize, leftBounds, rightBounds);
        auto pointsRef = dGen(amount);

        typedef typename decltype(pointsRef)::value_type::value_type fp_type;
        typedef unsigned long nm_type;


        namespace code = ::genetic_algorithm::common::coding;
        code::numeric_coder<fp_type, nm_type> coder ( geneSizes, leftBounds, rightBounds );

        auto codes = utility::vector::map([&coder](typename decltype(pointsRef)::value_type x){return coder.encode(x);}, pointsRef);
        auto pointsDec = utility::vector::map([&coder](typename decltype(codes)::value_type x){return coder.decode(x);}, codes);

        for (std::size_t k = 0; k < amount; ++k) {
            std::valarray<bool> cmp = std::abs(pointsRef[k] - pointsDec[k]) < (coder.interval_sizes() / 2.0);
            bool result = utility::valarray::reduce(std::logical_and<bool>{}, cmp);
            assert(result);
        }
    };

    template<typename T, std::size_t N>
    constexpr auto convert_if_array(const std::array<T, N>& arr) const -> std::valarray<T> {
        return utility::valarray::from(arr);
    }
    template<typename T>
    constexpr auto convert_if_array(const T val) const -> T {
        return val;
    }


};  //-- struct numeric_coder_test --

constexpr decltype(numeric_coder_test::test_cases) numeric_coder_test::test_cases;

};  //-- namespace coding --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --
};  //-- namespace test --


#endif /* TEST_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_TEST_HPP_ */
