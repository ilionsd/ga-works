/*
 * test.hpp
 *
 *  Created on: Jul 18, 2017
 *      Author: ilion
 */

#ifndef TEST_TEST_HPP_
#define TEST_TEST_HPP_


#include <cstddef>
#include <iostream>
#include <utility>
#include <tuple>

#include "../lib/genetic_algorithm/common/generating/uniform_generator.hpp"
#include "../lib/genetic_algorithm/common/coding/numeric_coder.hpp"

#include "genetic_algorithm/common/generating/uniform_generator_test.hpp"
#include "genetic_algorithm/common/coding/numeric_coder_test.hpp"
#include "genetic_algorithm/common/coding/gray_coder_test.hpp"


#define TEST_CLASS_NAME(CLASS_NAME) ::test CLASS_NAME ## _test

#define TEST_RUN_ALL(CLASS_NAME) \
    std::cout << #CLASS_NAME << " test... " << std::endl; \
    ::test::run_all<TEST_CLASS_NAME(CLASS_NAME)>(TEST_CLASS_NAME(CLASS_NAME)::test_cases); \
    std::cout << "OK" << std::endl;


namespace test {


template<std::size_t I>
inline constexpr void print_test_index() {
    std::cout << "Running test " << I << std::endl;
};

template<typename TestT, typename... Ts, std::size_t... I>
inline constexpr void run_test(const std::tuple<Ts...>& testCases, std::index_sequence<I...>) {
    auto l = { (
            print_test_index<I>(),
            TestT{}(std::get<I>(testCases)), 0 )... };
};

template<typename TestT, typename... Ts>
inline constexpr void run_all(const std::tuple<Ts...>& testCases) {
    run_test<TestT>(testCases, std::index_sequence_for<Ts...>{});
};

void testing() {
    using std::cout;
    using std::endl;

#ifndef NDEBUG

    cout << "Debug build" << endl;

    TEST_RUN_ALL( ::genetic_algorithm::common::generating::uniform_generator )
    TEST_RUN_ALL( ::genetic_algorithm::common::coding::numeric_coder )
    TEST_RUN_ALL( ::genetic_algorithm::common::coding::gray_coder )

#endif
}


}   //-- namespace test --





#endif /* TEST_TEST_HPP_ */
