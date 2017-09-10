/*
 * available_methods.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ilion
 */

#ifndef SRC_OPTIONS_AVAILABLE_METHODS_HPP_
#define SRC_OPTIONS_AVAILABLE_METHODS_HPP_


#include <string>
#include <vector>


namespace options {

struct available_methods {
    static const std::string
        ga,
        cmn_ga;

    static const std::vector<std::string> all;
};

}   //-- namespace options --


#endif /* SRC_OPTIONS_AVAILABLE_METHODS_HPP_ */
