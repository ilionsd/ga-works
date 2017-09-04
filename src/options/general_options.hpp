/*
 * general_options.hpp
 *
 *  Created on: Aug 31, 2017
 *      Author: ilion
 */

#ifndef SRC_OPTIONS_GENERAL_OPTIONS_HPP_
#define SRC_OPTIONS_GENERAL_OPTIONS_HPP_


#include <vector>
#include <string>


namespace options {

struct general {
    static const std::string
        help,
        version,
        input,
        output,
        method,
        precision;

    static const std::vector<std::string> all;
};

}   //-- namespace options --


#endif /* SRC_OPTIONS_GENERAL_OPTIONS_HPP_ */
