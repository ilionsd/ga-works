/*
 * tuple_join.hpp
 *
 *  Created on: Sep 18, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_UTILITY_TUPLE_JOIN_HPP_
#define LIB_IO_UTILITY_TUPLE_JOIN_HPP_


#include <string>
#include <sstream>

#include "../separator.hpp"
#include "../../fn/io/utility/tuple_join.hpp"


namespace io {
namespace utility {

template<class Tuple, typename CharT>
inline
auto tuple_join(
        const Tuple& t,
        const ::io::basic_separator<CharT> separator = ::io::basic_separator<CharT>::space)
-> std::basic_string<CharT> {
    return ::fn::io::utility::basic_tuple_join<CharT>()(t, separator);
}

}   //-- namespace utility --
}   //-- namespace io --


#endif /* LIB_IO_UTILITY_TUPLE_JOIN_HPP_ */
