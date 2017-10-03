/*
 * general.cpp
 *
 *  Created on: Sep 22, 2017
 *      Author: ilion
 */


#include "general.hpp"


namespace options2 {

using ::io::separator;
using ::io::names::root;
using ::io::names::path;
using ::io::names::names;
using ::io::names::complex_names;
using ::program_options2::description::option;
using ::program_options2::description::options_group;

const option common::help    (
        std::move(complex_names(separator::dot) << names{ "help"    , "h" }),
        "Produce help message"    );
const option common::version (
        std::move(complex_names(separator::dot) << names{ "version" , "v" }),
        "Outputs program version" );
const options_group common::group = options_group("Common Options") << common::help << common::version;

const option io::input  (
        std::move(complex_names(separator::dot) << names{ "input"  , "i" }),
        "Input file", true  );
const option io::output (
        std::move(complex_names(separator::dot) << names{ "output" , "o" }),
        "Output file", true );
const options_group io::group = options_group("I/O Options") << io::input << io::output;

const option algorithm::method    (
        std::move(complex_names(separator::dot) << names{ "method"    , "m" }),
        "Method", true    );
const option algorithm::precision (
        std::move(complex_names(separator::dot) << names{ "precision" , "p" }),
        "Precision", true );
const options_group algorithm::group = options_group("Algorithm Options") << algorithm::method << algorithm::precision;

}   //-- namespace options2 --

