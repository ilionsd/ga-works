/*
 * cmn_ga.hpp
 *
 *  Created on: Sep 26, 2017
 *      Author: ilion
 */

#ifndef SRC_OPTIONS2_CMN_GA_HPP_
#define SRC_OPTIONS2_CMN_GA_HPP_


#include "../../include/io/io.hpp"
#include "../../include/io/names.hpp"
#include "../../include/program_options2/description.hpp"


namespace options2 {

struct cmn_ga {
    static const ::program_options2::description::option
        max_size,
        initial_size,
        crossover,
        mutation,
        nearest,
        crowd,
        crossover_tries,
        mutation_tries;

    static const ::program_options2::description::options_group group;
};

}   //-- namespace options2 --


#endif /* SRC_OPTIONS2_CMN_GA_HPP_ */
