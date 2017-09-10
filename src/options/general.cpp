/*
 * general_options.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: ilion
 */


#include "general.hpp"

namespace options {

const std::string general::help      = "help";
const std::string general::version   = "version";

const std::vector<std::string> general::all {
    general::help,
    general::version
};

}   //-- namespace options --

