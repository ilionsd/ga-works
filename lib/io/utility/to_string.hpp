/*
 * to_string.hpp
 *
 *  Created on: Aug 2, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_TO_STRING_HPP_
#define LIB_IO_TO_STRING_HPP_

#include <string>
#include <sstream>

#include <vector>
#include <valarray>


#include "join.hpp"


namespace io {
namespace utility {

template<typename V>
constexpr std::string to_string(const V& v) {
    std::stringstream ss;
    {
        using namespace std::literals::string_literals;
        ss << "{" << join(v, ", "s) << "}";
    }
    return ss.str();
}

}   //-- namespace utility --
}   //-- namespace io --


#endif /* LIB_IO_TO_STRING_HPP_ */
