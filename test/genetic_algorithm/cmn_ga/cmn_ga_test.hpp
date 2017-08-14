/*
 * cmn_ga_test.hpp
 *
 *  Created on: Aug 9, 2017
 *      Author: ilion
 */

#ifndef TEST_GENETIC_ALGORITHM_CMN_GA_CMN_GA_TEST_HPP_
#define TEST_GENETIC_ALGORITHM_CMN_GA_CMN_GA_TEST_HPP_


#include <cstddef>
#include <tuple>


namespace test {
namespace genetic_algorithm {
namespace cmn_ga {

struct cmn_ga_test {
    static constexpr auto test_cases = std::make_tuple(

    );

    template<typename... Ts>
    void operator() (const std::tuple<Ts...>& testCase) {

    }
};

constexpr decltype(cmn_ga_test::test_cases) cmn_ga_test::test_cases;

}   //-- namespace cmn_ga --
}   //-- namespace genetic_algorithm --
}   //-- namespace test --


#endif /* TEST_GENETIC_ALGORITHM_CMN_GA_CMN_GA_TEST_HPP_ */
