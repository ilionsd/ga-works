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

#include "../../../tuple/for_each.hpp"
#include "stream_join.hpp"
#include "stream_wrapper.hpp"


namespace fn {
namespace io {
namespace utility {

template<typename CharT>
struct tuple_join {
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;
    typedef std::basic_ostringstream<char_type> ostringstream_type;
    typedef basic_stream_join<char_type> joiner_type;

    template<class Tuple>
    string_type
    operator() (
            const Tuple& t,
            const string_type& separator) const {
        ostream_wrapper<joiner_type> joiner(separator);
        ::tuple::for_each(joiner, t);
        return joiner.get().str();
    }
};

}   //-- namespace utility --
}   //-- namespace io --
}   //-- namespace fn --


#endif /* LIB_FN_IO_UTILITY_TUPLE_JOIN_HPP_ */
