/*
 * available_methods.cpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ilion
 */

#include "available_methods.hpp"


namespace options {

const std::string available_methods::ga = "GA";
const std::string available_methods::cmn_ga = "CMN-GA";

const std::vector<std::string> available_methods::all {
    available_methods::ga,
    available_methods::cmn_ga
};

}   //-- namespace options --


