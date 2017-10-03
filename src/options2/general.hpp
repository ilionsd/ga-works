/*
 * description.hpp
 *
 *  Created on: Sep 22, 2017
 *      Author: ilion
 */

#ifndef SRC_OPTIONS2_GENERAL_HPP_
#define SRC_OPTIONS2_GENERAL_HPP_


#include "../../include/io/io.hpp"
#include "../../include/io/names.hpp"
#include "../../include/program_options2/description.hpp"


namespace options2 {

struct common {
    static const ::program_options2::description::option
        help,
        version;

    static const ::program_options2::description::options_group group;
};
struct io {
    static const ::program_options2::description::option
        input,
        output;

    static const ::program_options2::description::options_group group;
};
struct algorithm {
    static const ::program_options2::description::option
        method,
        precision;

    static const ::program_options2::description::options_group group;
};

}   //-- namespace options2 --


#endif /* SRC_OPTIONS2_GENERAL_HPP_ */
