/*
 * tuple_to_string.hpp
 *
 *  Created on: Sep 20, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_UTILITY_TUPLE_TO_STRING_HPP_
#define LIB_IO_UTILITY_TUPLE_TO_STRING_HPP_


#include <string>

#include "../separator.hpp"
#include "../enclosure.hpp"
#include "../../fn/io/utility/tuple_to_string.hpp"


namespace io {
namespace utility {

template<class Tuple, typename CharT>
inline
auto tuple_to_string(
        const Tuple& t,
        ::io::basic_enclosure<CharT> enclosure = ::io::basic_enclosure<CharT>::curly_braces,
        ::io::basic_separator<CharT> separator = ::io::basic_separator<CharT>::space)
-> std::basic_string<CharT> {
    return ::fn::io::utility::basic_tuple_to_string<CharT>()(t, enclosure, separator);
}

}   //-- namespace utility --
}   //-- namespace io --


#endif /* LIB_IO_UTILITY_TUPLE_TO_STRING_HPP_ */
