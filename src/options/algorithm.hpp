/*
 * method_options.hpp
 *
 *  Created on: Aug 31, 2017
 *      Author: ilion
 */

#ifndef SRC_OPTIONS_ALGORITHM_HPP_
#define SRC_OPTIONS_ALGORITHM_HPP_


#include <vector>
#include <string>


namespace options {

struct algorithm {
    static const std::string
        method,
        precision;

    static const std::vector<std::string> all;
};

}   //-- namespace options --


#endif /* SRC_OPTIONS_ALGORITHM_HPP_ */
