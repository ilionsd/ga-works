/*
 * ga_options.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: ilion
 */

#include "ga_options.hpp"

namespace options {

const std::string ga::max_size = "max-size";
const std::string ga::initial_size = "initial-size";
const std::string ga::crossover = "crossover";
const std::string ga::mutation = "mutation";

const std::vector<std::string> ga::all {
    ga::max_size,
    ga::initial_size,
    ga::crossover,
    ga::mutation
};

}   //-- namespace options --


