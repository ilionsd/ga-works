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
                    utility::array::make_of<std::size_t>(5, 5, 6, 3, 10),
                    utility::array::make_of<double>( 0.0, 10.0,  1.0, 9.00, -1.0),
                    utility::array::make_of<double>(20.0, 30.0, 15.0, 9.99,  1.0),
                    100
            )
    );

    template<typename... Ts>
    constexpr void operator() (const std::tuple<Ts...>& testCase) const {
        auto geneSizes = std::get<0>(testCase);
        auto leftBounds = std::get<1>(testCase);
        auto rightBounds = std::get<2>(testCase);
        auto amount = std::get<3>(testCase);

        namespace gen = ::genetic_algorithm::common::generating;
        auto dGen = gen::make_uniform(leftBounds, rightBounds);
        auto points = dGen(amount);

        auto codes = fp_to_nm(points, geneSizes, leftBounds, rightBounds);
        auto pointsDec = nm_to_fp(codes, geneSizes, leftBounds, rightBounds);
    };

    template<typename NT, typename FT, std::size_t N>
    std::vector<std::array<NT, N>> fp_to_nm(
            const std::vector<std::array<FT, N>>& points,
            const std::array<std::size_t, N>& geneSizes,
            const std::array<FT, N>& leftBounds,
            const std::array<FT, N>& rightBounds) const
    {
        namespace code = ::genetic_algorithm::common::coding;
        code::numeric_coder<FT, NT, N> coder { geneSizes, leftBounds, rightBounds };

        std::vector<std::array<NT, N>> codes { points.size() };
        for (std::size_t k = 0; k < points.size(); ++k) {
            codes[k] = coder.encode(points[k]);
        }
        return codes;
    };

    template<typename FT, typename NT, std::size_t N>
    std::vector<std::array<FT, N>> nm_to_fp(
            const std::vector<std::array<NT, N>>& codes,
            const std::array<std::size_t, N>& geneSizes,
            const std::array<FT, N>& leftBounds,
            const std::array<FT, N>& rightBounds) const
    {
        namespace code = ::genetic_algorithm::common::coding;
        code::numeric_coder<FT, NT, N> coder { geneSizes, leftBounds, rightBounds };

        std::vector<std::array<FT, N>> points { codes.size() };
        for (std::size_t k = 0; k < codes.size(); ++k) {
            points[k] = coder.decode(codes[k]);
        }
        return points;
    };

};  //-- struct numeric_coder_test --

constexpr auto numeric_coder_test::test_cases;

};  //-- namespace coding --
};  //-- namespace common --
};  //-- namespace genetic_algorithm --
};  //-- namespace test --


#endif /* TEST_GENETIC_ALGORITHM_COMMON_CODING_NUMERIC_CODER_TEST_HPP_ */
