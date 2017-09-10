/*
 * general_options.hpp
 *
 *  Created on: Aug 31, 2017
 *      Author: ilion
 */

#ifndef SRC_OPTIONS_GENERAL_HPP_
#define SRC_OPTIONS_GENERAL_HPP_


#include <vector>
#include <string>


namespace options {

struct general {
    static const std::string
        help,
        version;

    static const std::vector<std::string> all;
};

}   //-- namespace options --


#endif /* SRC_OPTIONS_GENERAL_HPP_ */
