/*
 * string_slice.hpp
 *
 *  Created on: Sep 24, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_UTILITY_STRING_SLICE_HPP_
#define LIB_IO_UTILITY_STRING_SLICE_HPP_


#include <string>
#include <vector>

#include "../../fn/io/utility/string_slice.hpp"


namespace io {
namespace utility {

template<typename CharT>
inline
std::vector<std::basic_string<CharT>>
string_slice(const std::basic_string<CharT>& str, const std::basic_string<CharT>& separator) {
    return ::fn::io::utility::string_slice<CharT>()(str, separator);
}

}   //-- namespace utility --
}   //-- namespace io --


#endif /* LIB_IO_UTILITY_STRING_SLICE_HPP_ */
