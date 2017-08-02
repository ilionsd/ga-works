/*
 * to_string.hpp
 *
 *  Created on: Aug 2, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_TO_STRING_HPP_
#define LIB_UTILITY_TO_STRING_HPP_

#include <string>
#include <sstream>
#include <ostream>


#include <valarray>


namespace utility {


template<typename T>
constexpr std::string to_string(const std::valarray<T>& array) {
    std::stringstream ss;
    ss << "{";
    for (std::size_t k = 0; k < array.size(); ++k) {
        ss << array[k];
        if (k != array.size() - 1)
            ss << ", ";
    }
    ss << "}";
    return ss.str();
}

template<typename T>
constexpr std::ostream& operator<< (std::ostream& out, const std::valarray<T>& valarr) {
    out << to_string(valarr);
}

}   //-- namespace utility --


#endif /* LIB_UTILITY_TO_STRING_HPP_ */
