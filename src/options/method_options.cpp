/*
 * method_options.cpp
 *
 *  Created on: Aug 31, 2017
 *      Author: ilion
 */

#include "method_options.hpp"

namespace options {

const std::string method::ga = "GA";
const std::string method::cmn_ga = "CMN-GA";

const std::vector<std::string> method::all {
    method::ga,
    method::cmn_ga
};

}   //-- namespace options --


