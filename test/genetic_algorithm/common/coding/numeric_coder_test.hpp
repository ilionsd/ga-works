/*
 * numeric_coder_test.hpp
 *
 *  Created on: Jul 18, 2017
 *      Author: ilion
 */

#ifndef TEST_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_TEST_HPP_
#define TEST_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_TEST_HPP_


#include <tuple>
#include <array>

#include "../../../../lib/utility/array.hpp"

#include "../../../../lib/genetic_algorithm/common/generating/uniform_generator.hpp"
#include "../../../../lib/genetic_algorithm/common/coding/numeric_coder.hpp"


namespace test {
namespace genetic_algorithm {
namespace common {
namespace coding {

struct numeric_coder_test {
    static constexpr auto test_cases = std::make_tuple(
            std::make_tuple(
                    utility::make_array_of<double>(0.0, 10.0, 1.0, 9.0, -1.0),
                    utility::make_array_of<double>(20.0, 30.0, 15.0, 9.99, 1.0)
            )
    );

    template<typename... Ts>
    constexpr void operator() (const std::tuple<Ts...>& testCase) const {
        auto leftBounds = std::get<0>(testCase);
        auto rightBounds = std::get<1>(testCase);


    };

    template<typename T, std::size_t N>
    void double_to_numeric(const std::array<T, N>& leftBounds, const std::array<T, N>& rightBounds) const {
        namespace gen = ::genetic_algorithm::common::generating;
        namespace code = ::genetic_algorithm::common::coding;

        auto generator = gen::make_uniform(leftBounds, rightBounds);
    };

};  //-- struct numeric_coder_test --

constexpr auto numeric_coder_test::test_cases;

};  //-- namespace coding --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --
};  //-- namespace test --


#endif /* TEST_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_TEST_HPP_ */
