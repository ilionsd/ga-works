/*
 * main.cpp
 *
 *  Created on: Jul 14, 2017
 *      Author: ilion
 */

#include <cstddef>
#include <functional>
#include <iostream>


#include "../lib/utility/valarray.hpp"
#include "../lib/genetic_algorithm/common/space.hpp"
#include "../lib/genetic_algorithm/cmn_ga/cmn_ga.hpp"


#include "../test/test.hpp"


auto main(int argc, char** argv) -> int {

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
    auto realSpace = genetic_algorithm::common::make_space_real(spaceSize, realLeftBound, realRightBound);

    const std::size_t geneSize = 10;
    auto uintSpace = genetic_algorithm::common::make_space_uint_from_gene_sizes<unsigned long>(spaceSize, geneSize);

    std::function<double(std::valarray<double>)> f = [](const std::valarray<double> x)
            -> double { return -x[0]*x[0] - x[1]*x[1] - x[2] * x[2]; };

    genetic_algorithm::cmn_ga::cmn_ga alg ( params, realSpace, uintSpace, f );

    return 0;
}
