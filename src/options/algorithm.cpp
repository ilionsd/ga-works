/*
 * method_options.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: ilion
 */

#include "algorithm.hpp"

namespace options {

const std::string algorithm::method = "method";
const std::string algorithm::precision = "precision";

const std::vector<std::string> algorithm::all {
    algorithm::method,
    algorithm::precision
};

}   //-- namespace options --


