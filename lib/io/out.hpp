/*
 * out.hpp
 *
 *  Created on: Aug 21, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_OUT_HPP_
#define LIB_IO_OUT_HPP_


#include <ostream>


#include "utility/to_string.hpp"


namespace io {

template<typename T>
constexpr std::ostream& operator<< (std::ostream& out, const std::valarray<T>& v) {
    out << utility::to_string(v);
    return out;
}

template<typename T>
constexpr std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
    out << utility::to_string(v);
    return out;
}

}   //-- namespace io --


#endif /* LIB_IO_OUT_HPP_ */
