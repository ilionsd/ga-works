/*
 * definition.hpp
 *
 *  Created on: Sep 6, 2017
 *      Author: ilion
 */

#ifndef SRC_OPTIONS_DESCRIPTION_HPP_
#define SRC_OPTIONS_DESCRIPTION_HPP_


#include <boost/program_options.hpp>

#include "general.hpp"
#include "algorithm.hpp"
#include "cmn_ga.hpp"
#include "io.hpp"
#include "ga.hpp"


namespace options {

struct description {
    static const ::boost::program_options::options_description
        general,
        io,
        algorithm,
        ga,
        cmnga;
};

}


#endif /* SRC_OPTIONS_DESCRIPTION_HPP_ */
