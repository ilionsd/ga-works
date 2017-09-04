/*
 * general_options.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: ilion
 */


#include "general_options.hpp"

namespace options {

const std::string general::help      = "help";
const std::string general::version   = "version";
const std::string general::input     = "input";
const std::string general::output    = "output";
const std::string general::method    = "method";
const std::string general::precision = "precision";

const std::vector<std::string> general::all {
    general::help,
    general::version,
    general::input,
    general::output,
    general::method,
    general::precision
};

}   //-- namespace options --

