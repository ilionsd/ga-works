/*
 * io.hpp
 *
 *  Created on: Sep 6, 2017
 *      Author: ilion
 */

#ifndef SRC_OPTIONS_IO_HPP_
#define SRC_OPTIONS_IO_HPP_


#include <string>
#include <vector>


namespace options {

struct io {
    static const std::string
        input,
        output;

    static const std::vector<std::string> all;
};

}


#endif /* SRC_OPTIONS_IO_HPP_ */
