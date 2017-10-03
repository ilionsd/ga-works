/*
 * to_string.hpp
 *
 *  Created on: Aug 2, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_VECTOR_TO_STRING_HPP_
#define LIB_IO_VECTOR_TO_STRING_HPP_

#include <string>
#include <sstream>
#include <utility>

#include "../../fn/io/utility/vector_to_string.hpp"


namespace io {
namespace utility {

template<class Vector, typename CharT>
inline
auto vector_to_string(
        const Vector& v,
        const std::pair<std::basic_string<CharT>, std::basic_string<CharT>>& enclosure,
        const std::basic_string<CharT>& separator)
-> std::basic_string<CharT> {
    return ::fn::io::utility::vector_to_string<CharT>()(v, enclosure, separator);
}

template<class ForwardIterator, typename CharT>
inline
auto vector_to_string(
        ForwardIterator begin,
        ForwardIterator end,
        const std::pair<std::basic_string<CharT>, std::basic_string<CharT>>& enclosure,
        const std::basic_string<CharT>& separator)
-> std::basic_string<CharT> {
    return ::fn::io::utility::vector_to_string<CharT>()(begin, end, enclosure, separator);
}

}   //-- namespace utility --
}   //-- namespace io --


#endif /* LIB_IO_VECTOR_TO_STRING_HPP_ */
