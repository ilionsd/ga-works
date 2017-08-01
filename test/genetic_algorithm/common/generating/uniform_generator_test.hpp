/*
 * uniform_generator_test.hpp
 *
 *  Created on: Jul 15, 2017
 *      Author: ilion
 */

#ifndef TEST_GENETIC_ALGORITHM_COMMON_GENERATING_UNIFORM_GENERATOR_TEST_HPP_
#define TEST_GENETIC_ALGORITHM_COMMON_GENERATING_UNIFORM_GENERATOR_TEST_HPP_

#include <cassert>
#include <cstddef>
#include <tuple>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <utility>

#include "../../../../lib/genetic_algorithm/common/generating/uniform_generator.hpp"
#include "../../../../lib/utility/tuple.hpp"
#include "../../../../lib/utility/array.hpp"

namespace test {
namespace genetic_algorithm {
namespace common {
namespace generating {

struct uniform_generator_test {

    static constexpr auto test_cases = std::make_tuple(
            std::make_tuple(3, 0, 100, 1000),
            std::make_tuple(
                    3,
                    utility::array::make_of<std::size_t>( 0, 10,  70),
                    utility::array::make_of<std::size_t>(10, 50, 100),
                    1000),
            std::make_tuple(3, -10.0, 100.0, 1000),
            std::make_tuple(
                    3,
                    utility::array::make_of<double>( 0,  -10, -100),
                    utility::array::make_of<double>(10.0, 50,  100),
                    1000)
    );

    template<typename... Ts>
    void operator() (const std::tuple<Ts...>& testCase) const {
        auto spaceSize   = std::get<0>(testCase);
        auto leftBounds  = convert_if_array(std::get<1>(testCase));
        auto rightBounds = convert_if_array(std::get<2>(testCase));
        auto amount      = std::get<3>(testCase);

        namespace gen = ::genetic_algorithm::common::generating;
        auto generator = gen::make_uniform(spaceSize, leftBounds, rightBounds);
        auto codes = generator(amount);

        for (std::size_t k = 0; k < codes.size(); ++k) {
            std::valarray<bool> cmp = (generator.left_bounds() <= codes[k]) && (codes[k] <= generator.right_bounds());
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

};  //-- struct uniform_generator_test --

constexpr decltype(uniform_generator_test::test_cases) uniform_generator_test::test_cases;

}  //-- namespace generating --
}  //-- namespace common --
}  //-- namespace genetic_algorithm --
}  //-- namespace test --


#endif /* TEST_GENETIC_ALGORITHM_COMMON_GENERATING_UNIFORM_GENERATOR_TEST_HPP_ */
