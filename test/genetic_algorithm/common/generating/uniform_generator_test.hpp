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
            std::make_tuple<std::size_t, std::size_t>(0, 100, 1000),
            std::make_tuple(
                    utility::make_array_of<std::size_t>(0, 10, 70),
                    utility::make_array_of<std::size_t>(10, 50, 100),
                    1000),
            std::make_tuple<double, double>(-10.0, 100.0, 1000),
            std::make_tuple(
                    utility::make_array_of<double>(0, -10, -100),
                    utility::make_array_of<double>(10.0, 50, 100),
                    1000)
    );

    template<typename... Ts>
    void operator() (const std::tuple<Ts...>& testCase) const {
        auto leftBounds = std::get<0>(testCase);
        auto rightBounds = std::get<1>(testCase);
        auto amount = std::get<2>(testCase);

        namespace gen = ::genetic_algorithm::common::generating;
        auto generator = gen::make_uniform<3>(leftBounds, rightBounds);
        auto codes = generator.generate(amount);
        for (std::size_t k = 0; k < codes.size(); ++k) {
            auto ge = utility::array_compare<std::greater_equal>(codes[k], generator.left_bounds());
            auto le = utility::array_compare<std::less_equal>(codes[k], generator.right_bounds());
            auto cmp = utility::array_map(std::logical_and<bool>{}, ge, le);
            bool result = utility::array_reduce(cmp, std::logical_and<bool>{});
            if (!result)
                int breakPoint = 0;
            assert(result);
        }
    };

};  //-- struct uniform_generator_test --

constexpr decltype(uniform_generator_test::test_cases) uniform_generator_test::test_cases;

};  //-- namespace generating --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --
};  //-- namespace test --


#endif /* TEST_GENETIC_ALGORITHM_COMMON_GENERATING_UNIFORM_GENERATOR_TEST_HPP_ */
