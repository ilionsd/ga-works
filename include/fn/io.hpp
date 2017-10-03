/*
 * io.hpp
 *
 *  Created on: Sep 18, 2017
 *      Author: ilion
 */

#ifndef INCLUDE_FN_IO_HPP_
#define INCLUDE_FN_IO_HPP_


#include "../../lib/fn/io/utility/vector_join.hpp"
#include "../../lib/fn/io/utility/vector_to_string.hpp"


namespace fn {
namespace io {
namespace utility {

template<class IS> class istream_wrapper;
template<class OS> class ostream_wrapper;

template<typename CharT> class basic_stream_join;
using stream_join  = basic_stream_join<char>;
using wstream_join = basic_stream_join<wchar_t>;

template<typename CharT> struct vector_join;
template<typename CharT> struct vector_to_string;
template<typename CharT> struct tuple_join;
template<typename CharT> struct tuple_to_string;

}   //-- namespace utility --
}   //-- namespace io --
}   //-- namespace fn --


#endif /* INCLUDE_FN_IO_HPP_ */
