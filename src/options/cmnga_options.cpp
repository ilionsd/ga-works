/*
 * cmnga_options.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: ilion
 */

#include "cmnga_options.hpp"

namespace options {

const std::string cmn_ga::max_size = "max-size";
const std::string cmn_ga::initial_size = "initial-size";
const std::string cmn_ga::crossover = "crossover";
const std::string cmn_ga::mutation = "mutation";
const std::string cmn_ga::nearest = "nearest";
const std::string cmn_ga::crowd = "crowd";
const std::string cmn_ga::crossover_tries = "crossover-tries";
const std::string cmn_ga::mutation_tries = "mutation-tries";

const std::vector<std::string> cmn_ga::all {
    cmn_ga::max_size,
    cmn_ga::initial_size,
    cmn_ga::crossover,
    cmn_ga::mutation,
    cmn_ga::nearest,
    cmn_ga::crowd,
    cmn_ga::crossover_tries,
    cmn_ga::mutation_tries
};

}   //-- namespace options --

