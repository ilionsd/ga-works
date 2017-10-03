/*
 * ga.cpp
 *
 *  Created on: Sep 22, 2017
 *      Author: ilion
 */


#include "ga.hpp"


namespace options2 {

using ::io::separator;
using ::io::names::root;
using ::io::names::path;
using ::io::names::names;
using ::io::names::complex_names;
using ::program_options2::description::option;
using ::program_options2::description::options_group;

const option ga::max_size     (
        std::move(complex_names(separator::dot) << path().add("ga") << names{"max-size"}),
        "Max population size", true);
const option ga::initial_size (
        std::move(complex_names(separator::dot) << path().add("ga") << names{"init-size"}),
        "Initial population size", true);
const option ga::crossover    (
        std::move(complex_names(separator::dot) << path().add("ga") << names{"crossover"}),
        "Crossover pairs number", true);
const option ga::mutation     (
        std::move(complex_names(separator::dot) << path().add("ga") << names{"mutation"}),
        "Mutated individuals number", true);
const options_group ga::group = options_group("GA Options") << ga::max_size << ga::initial_size
        << ga::crossover << ga::mutation;

}   //-- namespace options2 --

