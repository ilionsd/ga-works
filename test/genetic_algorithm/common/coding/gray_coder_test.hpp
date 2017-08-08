/*
 * gray_coder_test.hpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ilion
 */

#ifndef TEST_GENETIC_ALGORITHM_COMMON_CODING_GRAY_CODER_TEST_HPP_
#define TEST_GENETIC_ALGORITHM_COMMON_CODING_GRAY_CODER_TEST_HPP_


#include <cstddef>
#include <tuple>
#include <valarray>
#include <type_traits>

#include "../../../../lib/utility/array.hpp"
#include "../../../../lib/utility/vector.hpp"
#include "../../../../lib/utility/to_string.hpp"
#include "../../../../lib/genetic_algorithm/common/space.hpp"
#include "../../../../lib/genetic_algorithm/common/coding/gray_coder.hpp"
#include "../../../../lib/genetic_algorithm/common/generating/uniform_generator.hpp"


namespace test {
namespace genetic_algorithm {
namespace common {
namespace coding {


struct gray_coder_test {
    static constexpr auto test_cases = std::make_tuple(
             std::make_tuple(
                     ::utility::array::make_of<std::size_t>(2, 3, 4, 5, 6, 7, 8, 9),
                     std::size_t(1000)
             ),
             std::make_tuple(
                     ::utility::array::make_of<std::size_t>(10, 15, 20, 25, 30, 32),
                     std::size_t(1000)
             )
    );

    template<typename... Ts>
    constexpr void operator() (const std::tuple<Ts...>& testCase) {
        auto geneSizes = convert_if_array(std::get<0>(testCase));
        auto amount = std::get<1>(testCase);

        auto space = ::genetic_algorithm::common::make_space_uint_from_gene_sizes<unsigned long>(geneSizes);
        typedef typename decltype(space)::value_type value_type;

        auto generator = ::genetic_algorithm::common::generating::uniform_generator<value_type>(space);
        auto coder = ::genetic_algorithm::common::coding::gray_coder<std::size_t>(space);

        std::vector<std::valarray<value_type>> ref = generator(amount);
        std::vector<std::vector<bool>>         enc = ::utility::vector::map(coder.code_coder(), ref);
        std::vector<std::valarray<value_type>> dec = ::utility::vector::map(coder.uint_coder(), enc);

        for (std::size_t k = 0; k < amount; ++k) {
            bool result = utility::valarray::reduce(std::logical_and<bool>{}, ref[k] == dec[k]);
            assert(result);
        }
    }

    template<typename T, std::size_t N>
    constexpr auto convert_if_array(const std::array<T, N>& arr) const -> std::valarray<T> {
        return ::utility::valarray::from(arr);
    }
    template<typename T>
    constexpr auto convert_if_array(const T val) const -> T {
        return val;
    }
};

constexpr decltype(gray_coder_test::test_cases) gray_coder_test::test_cases;

}   //-- namespace coding --
}   //-- namespace common --
}   //-- namespace genetic_algorithm --
}   //-- namespace test --


#endif /* TEST_GENETIC_ALGORITHM_COMMON_CODING_GRAY_CODER_TEST_HPP_ */
