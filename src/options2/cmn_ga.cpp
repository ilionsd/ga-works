/*
 * cmn_ga.cpp
 *
 *  Created on: Sep 26, 2017
 *      Author: ilion
 */


#include "cmn_ga.hpp"


namespace options2 {

using ::io::separator;
using ::io::names::root;
using ::io::names::path;
using ::io::names::names;
using ::io::names::complex_names;
using ::program_options2::description::option;
using ::program_options2::description::options_group;

const option cmn_ga::max_size (
        std::move(complex_names(separator::dot) << path().add("cmn-ga") << names{"max-size"}),
        "Max population size", true);
const option cmn_ga::initial_size (
        std::move(complex_names(separator::dot) << path().add("cmn-ga") << names{"initial-size"}),
        "Initial population size", true);
const option cmn_ga::crossover (
        std::move(complex_names(separator::dot) << path().add("cmn-ga") << names{"crossover"}),
        "Crossover pairs number", true);
const option cmn_ga::mutation (
        std::move(complex_names(separator::dot) << path().add("cmn-ga") << names{"mutation"}),
        "Mutated individuals number", true);
const option cmn_ga::nearest (
        std::move(complex_names(separator::dot) << path().add("cmn-ga") << names{"nearest"}),
        "Nearest individuals number for optima criteria", true);
const option cmn_ga::crowd (
        std::move(complex_names(separator::dot) << path().add("cmn-ga") << names{"crowd"}),
        "Number of individuals for proximity based selection", true);
const option cmn_ga::crossover_tries (
        std::move(complex_names(separator::dot) << path().add("cmn-ga") << names{"crossover-tries"}),
        "Number of attempts to perform crossovers", true);
const option cmn_ga::mutation_tries (
        std::move(complex_names(separator::dot) << path().add("cmn-ga") << names{"mutation-tries"}),
        "Number of attempts to perform mutations", true);
const options_group cmn_ga::group = options_group("CMN-GA Options") << cmn_ga::max_size << cmn_ga::initial_size << cmn_ga::crossover
        << cmn_ga::mutation << cmn_ga::nearest << cmn_ga::crowd << cmn_ga::crossover_tries << cmn_ga::mutation_tries;

}   //-- namespace options2 --

