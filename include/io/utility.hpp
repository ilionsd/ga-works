/*
 * utility.hpp
 *
 *  Created on: Sep 21, 2017
 *      Author: ilion
 */

#ifndef INCLUDE_IO_UTILITY_HPP_
#define INCLUDE_IO_UTILITY_HPP_


#include "../../lib/io/utility/vector_join.hpp"
#include "../../lib/io/utility/vector_to_string.hpp"
#include "../../lib/io/utility/tuple_join.hpp"
#include "../../lib/io/utility/tuple_to_string.hpp"


namespace io {
namespace utility {

template<class Vector, typename CharT>
inline
auto vector_join(
        const Vector& v,
        ::io::basic_separator<CharT> separator = ::io::basic_separator<CharT>::space)
-> std::basic_string<CharT>;
template<class ForwardIterator, typename CharT>
inline
auto vector_join(
        ForwardIterator begin,
        ForwardIterator end,
        ::io::basic_separator<CharT> separator = ::io::basic_separator<CharT>::space)
-> std::basic_string<CharT>;

template<class Vector, typename CharT>
inline
auto vector_to_string(
        const Vector& v,
        ::io::basic_enclosure<CharT> enclosure = ::io::basic_enclosure<CharT>::curly_braces,
        ::io::basic_separator<CharT> separator = ::io::basic_separator<CharT>::space)
-> std::basic_string<CharT>;
template<class ForwardIterator, typename CharT>
inline
auto vector_to_string(
        ForwardIterator begin,
        ForwardIterator end,
        ::io::basic_enclosure<CharT> enclosure = ::io::basic_enclosure<CharT>::curly_braces,
        ::io::basic_separator<CharT> separator = ::io::basic_separator<CharT>::space)
-> std::basic_string<CharT>;

template<class Tuple, typename CharT>
inline
auto tuple_join(
        const Tuple& t,
        const ::io::basic_separator<CharT> separator = ::io::basic_separator<CharT>::space)
-> std::basic_string<CharT>;

template<class Tuple, typename CharT>
inline
auto tuple_to_string(
        const Tuple& t,
        ::io::basic_enclosure<CharT> enclosure = ::io::basic_enclosure<CharT>::curly_braces,
        ::io::basic_separator<CharT> separator = ::io::basic_separator<CharT>::space)
-> std::basic_string<CharT>;

}   //-- namespace utility --
}   //-- namespace io --


#endif /* INCLUDE_IO_UTILITY_HPP_ */
