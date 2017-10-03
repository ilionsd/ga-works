/*
 * ga.hpp
 *
 *  Created on: Sep 22, 2017
 *      Author: ilion
 */

#ifndef SRC_OPTIONS2_GA_HPP_
#define SRC_OPTIONS2_GA_HPP_


#include "../../include/io/io.hpp"
#include "../../include/io/names.hpp"
#include "../../include/program_options2/description.hpp"


namespace options2 {

struct ga {
    static const ::program_options2::description::option
        max_size,
        initial_size,
        crossover,
        mutation;

    static const ::program_options2::description::options_group group;
};

}   //-- namespace options2 --


#endif /* SRC_OPTIONS2_GA_HPP_ */
