/*
 * method_options.hpp
 *
 *  Created on: Aug 31, 2017
 *      Author: ilion
 */

#ifndef SRC_OPTIONS_METHOD_OPTIONS_HPP_
#define SRC_OPTIONS_METHOD_OPTIONS_HPP_


#include <vector>
#include <string>


namespace options {

struct method {
    static const std::string ga;
    static const std::string cmn_ga;

    static const std::vector<std::string> all;
};

}   //-- namespace options --


#endif /* SRC_OPTIONS_METHOD_OPTIONS_HPP_ */
