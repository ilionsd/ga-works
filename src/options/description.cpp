/*
 * definition.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ilion
 */

#include "description.hpp"

namespace options {

namespace po = ::boost::program_options;

//const auto description::general   = po::options_description("General Options")
//    .add_options()
//    ( (general::help    + ",h").c_str(), "Produce a help message" )
//    ( (general::version + ",v").c_str(), "Outputs program version");
//
//const auto description::io        = po::options_description("Input/Output Options")
//    .add_options()
//    ( (io::input  + ",i").c_str(), po::value<std::string>(), "Input file" )
//    ( (io::output + ",o").c_str(), po::value<std::string>(), "Output file");
//
//const auto description::algorithm = po::options_description("Algorithm Options")
//    .add_options()
//    ( (algorithm::method    + ",m").c_str(), po::value<std::string>()
//            /*
//             * To Do: Add Description for each method or at least list of them
//             */
//    )
//    ( (algorithm::precision + ",p").c_str(), po::value<double>()     , "Precision");
//
//const auto description::ga        = po::options_description("GA Options")
//    .add_options()
//    (ga::max_size    .c_str(), po::value<std::size_t>(), "Max population size")
//    (ga::initial_size.c_str(), po::value<std::size_t>(), "Initial population size")
//    (ga::crossover.c_str(), po::value<std::size_t>(), "Crossover pairs number")
//    (ga::mutation .c_str(), po::value<std::size_t>(), "Mutated individuals number");
//
//const auto description::cmnga     = po::options_description("CMN-GA Options")
//    .add_options()
//    (cmn_ga::max_size    .c_str(), po::value<std::size_t>(), "Max population size")
//    (cmn_ga::initial_size.c_str(), po::value<std::size_t>(), "Initial population size")
//    (cmn_ga::crossover.c_str(), po::value<std::size_t>(), "Crossover pairs number")
//    (cmn_ga::mutation .c_str(), po::value<std::size_t>(), "Mutated individuals number")
//    (cmn_ga::nearest  .c_str(), po::value<std::size_t>(), "Nearest individuals number for optima criteria")
//    (cmn_ga::crowd    .c_str(), po::value<std::size_t>(), "Number of individuals for proximity based selection")
//    (cmn_ga::crossover_tries.c_str(), po::value<std::size_t>(), "Number of attempts to perform crossovers")
//    (cmn_ga::mutation_tries .c_str(), po::value<std::size_t>(), "Number of attempts to perform mutations");

}   //-- namespace options --


