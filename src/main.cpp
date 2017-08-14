/*
 * main.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: ilion
 */

#define _USE_MATH_DEFINES

#include <cstddef>
#include <cmath>
#include <valarray>
#include <functional>
#include <iostream>

#include "../lib/utility/stlmath.hpp"
#include "../lib/utility/valarray.hpp"
#include "../lib/genetic_algorithm/common/space.hpp"
#include "../lib/genetic_algorithm/cmn_ga/cmn_ga.hpp"


#include "../test/test.hpp"


auto main(int argc, char** argv) -> int {

    namespace math = ::utility::stlmath;

    std::function<double(double)> f1 = [](double x)
            -> double { return math::power<double>()(math::sin<double>()(5.1 * M_PI * x + 0.5), 6.0); };

    std::function<double(double)> f2 = [f1](double x)
            -> double { return math::exp<double>()(-4.0 * math::ln<double>()(2.0) * math::power<double>()(x - 0.0667, 2.0) / 0.64) * f1(x); };

    std::valarray<double> peaks = {-32, -16, 0, 16, 32};
    std::function<double(double, double)> f3 = [&peaks](double x, double y) -> double {
        double sum = 0.0;
        for (std::size_t i = 0; i < peaks.size(); ++i)
            for (std::size_t j = 0; j < peaks.size(); ++j)
                sum += 1.0 / (i + j + math::power<double>()(x - peaks[i], 6.0) + math::power<double>()(y - peaks[j], 6.0));
        return 0.002 + sum;
    };

    std::valarray<double>
        a = {-20.0 ,  -5.0,  0.0 , 30.0,  30.0 },
        b = {-20.0 , -25.0, 30.0 ,  0.0, -30.0 },
        h = {  0.4 ,   0.2,  0.7 ,  1.0,   0.05},
        w = {  0.02,   0.5,  0.01,  2.0,   0.1 };
    std::function<double(double, double)> f4 = [&a, &b, &h, &w](double x, double y) -> double {
        double sum = 0;
        for (std::size_t k = 0; k < a.size(); ++k)
            sum += h[k] / (1.0 + w[k] * (math::power<double>()(x - a[k], 2.0) + math::power<double>()(y - b[k], 2.0)));
        return sum;
    };

    auto fs = std::make_tuple(f1, f2, f3, f4);
    auto realSpaces = std::make_tuple(
            genetic_algorithm::common::make_space_real(1, 0.0, 1.0),
            genetic_algorithm::common::make_space_real(1, 0.0, 1.0),
            genetic_algorithm::common::make_space_real(2, -40.0, 40.0),
            genetic_algorithm::common::make_space_real(2, -40.0, 40.0)
    );



    ::test::testing();

    genetic_algorithm::cmn_ga::cmn_ga::parameters params;
    params.max_population_size = 10000;
    params.initial_population_size = 1000;
    params.nearest_individuals_number = 10;
    params.crossover_pair_number = 20;
    params.crowd_size = 20;
    params.mutated_individuals_number = 40;
    params.max_try_number = 40;
    params.precision = 3;

    const std::size_t spaceSize = 3;
    const double realLeftBound = -10, realRightBound = 10;
    auto realSpace = ::genetic_algorithm::common::make_space_real(spaceSize, realLeftBound, realRightBound);

    std::function<double(std::valarray<double>)> f = [](const std::valarray<double> x)
            -> double { return -x[0]*x[0] - x[1]*x[1] - x[2] * x[2]; };

    genetic_algorithm::cmn_ga::cmn_ga alg ( params, realSpace, f );
    alg.init();
    alg();

    return 0;
}
