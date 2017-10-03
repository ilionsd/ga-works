/*
 * join.hpp
 *
 *  Created on: Sep 4, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_VECTOR_JOIN_HPP_
#define LIB_IO_VECTOR_JOIN_HPP_


#include <string>
#include <sstream>

#include "../../fn/io/utility/vector_join.hpp"


namespace io {
namespace utility {

template<class Vector, typename CharT>
inline
auto vector_join(
        const Vector& v,
        const std::basic_string<CharT>& separator)
-> std::basic_string<CharT> {
    return ::fn::io::utility::vector_join<CharT>()(v, separator);
}

template<class ForwardIterator, typename CharT>
inline
auto vector_join(
        ForwardIterator begin,
        ForwardIterator end,
        const std::basic_string<CharT>& separator)
-> std::basic_string<CharT> {
    return ::fn::io::utility::vector_join<CharT>()(begin, end, separator);
}

}   //-- namespace utility --
}   //-- namespace io --


#endif /* LIB_IO_VECTOR_JOIN_HPP_ */
