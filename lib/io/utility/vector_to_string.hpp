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

#include "../separator.hpp"
#include "../enclosure.hpp"
#include "../../fn/io/utility/vector_to_string.hpp"


namespace io {
namespace utility {

template<class Vector, typename CharT>
inline
auto vector_to_string(
        const Vector& v,
        ::io::basic_enclosure<CharT> enclosure = ::io::basic_enclosure<CharT>::curly_braces,
        ::io::basic_separator<CharT> separator = ::io::basic_separator<CharT>::space)
-> std::basic_string<CharT> {
    return ::fn::io::utility::basic_vector_to_string<CharT>()(v, enclosure, separator);
}

template<class ForwardIterator, typename CharT>
inline
auto vector_to_string(
        ForwardIterator begin,
        ForwardIterator end,
        ::io::basic_enclosure<CharT> enclosure = ::io::basic_enclosure<CharT>::curly_braces,
        ::io::basic_separator<CharT> separator = ::io::basic_separator<CharT>::space)
-> std::basic_string<CharT> {
    return ::fn::io::utility::basic_vector_to_string<CharT>()(begin, end, enclosure, separator);
}

}   //-- namespace utility --
}   //-- namespace io --


#endif /* LIB_IO_VECTOR_TO_STRING_HPP_ */
