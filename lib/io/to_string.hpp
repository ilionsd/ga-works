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

template<typename T>
constexpr std::string to_string(const std::valarray<T>& array) {
    std::stringstream ss;
    {
        using namespace std::literals::string_literals;
        ss << "{" << join<std::valarray<T>>()(array, ", "s) << "}";
    }
    return ss.str();
}

template<typename T>
constexpr std::string to_string(const std::vector<T>& vector) {
    std::stringstream ss;
    {
        using namespace std::literals::string_literals;
        ss << "{" << join<std::vector<T>>()(vector, ", "s) << "}";
    }
    return ss.str();
}

}   //-- namespace io --


#endif /* LIB_IO_TO_STRING_HPP_ */
