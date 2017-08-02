/*
 * cmn_ga.hpp
 *
 *  Created on: Jul 14, 2017
 *      Author: ilion
 */

#ifndef LIB_GENETIC_ALGORITHM_CMN_GA_CMN_GA_HPP_
#define LIB_GENETIC_ALGORITHM_CMN_GA_CMN_GA_HPP_

#include <cstddef>

namespace genetic_algorithm {
namespace cmn_ga {

struct cmn_ga {
    std::size_t
    initial_population_size,
    crossover_pair_number,
    mutated_individuals_number,
    nearest_individuals_number,
    crowd_size,
    try_number,
    max_population_size,
    precision;


};

}   //-- namespace cmn_ga --
}   //-- namespace genetic_algorithm --


#endif /* LIB_GENETIC_ALGORITHM_CMN_GA_CMN_GA_HPP_ */
