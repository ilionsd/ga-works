/*
 * tuple_join.hpp
 *
 *  Created on: Sep 18, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_IO_UTILITY_TUPLE_JOIN_HPP_
#define LIB_FN_IO_UTILITY_TUPLE_JOIN_HPP_


#include <string>
#include <sstream>
#include <tuple>

#include "../../../io/separator.hpp"
#include "../../../tuple/for_each.hpp"
#include "stream_join.hpp"
#include "stream_wrapper.hpp"


namespace fn {
namespace io {
namespace utility {

template<typename CharT>
struct basic_tuple_join {
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;
    typedef std::basic_ostringstream<char_type> ostringstream_type;
    typedef basic_stream_join<char_type> joiner_type;
    typedef ::io::basic_separator<char_type> separator_type;

    template<class Tuple>
    string_type
    operator() (
            const Tuple& t,
            const separator_type& separator = separator_type::space) const {
        ostream_wrapper<joiner_type> joiner(separator);
        ::tuple::for_each(joiner, t);
        return joiner.get().str();
    }
};

using tuple_join  = basic_tuple_join<char>;
using tuple_wjoin = basic_tuple_join<wchar_t>;

}   //-- namespace utility --
}   //-- namespace io --
}   //-- namespace fn --


#endif /* LIB_FN_IO_UTILITY_TUPLE_JOIN_HPP_ */
