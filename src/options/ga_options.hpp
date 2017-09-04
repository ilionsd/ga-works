/*
 * ga_options.hpp
 *
 *  Created on: Aug 31, 2017
 *      Author: ilion
 */

#ifndef SRC_OPTIONS_GA_OPTIONS_HPP_
#define SRC_OPTIONS_GA_OPTIONS_HPP_


#include <vector>
#include <string>


namespace options {

struct ga {
    static const std::string
        max_size,
        initial_size,
        crossover,
        mutation;

    static const std::vector<std::string> all;
};

}   //-- namespace options --


#endif /* SRC_OPTIONS_GA_OPTIONS_HPP_ */
