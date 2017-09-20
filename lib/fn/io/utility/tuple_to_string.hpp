/*
 * tuple_to_string.hpp
 *
 *  Created on: Sep 19, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_IO_UTILITY_TUPLE_TO_STRING_HPP_
#define LIB_FN_IO_UTILITY_TUPLE_TO_STRING_HPP_


#include <string>

#include "../../../io/separator.hpp"
#include "../../../io/enclosure.hpp"
#include "tuple_join.hpp"


namespace fn {
namespace io {
namespace utility {

template<typename CharT>
struct basic_tuple_to_string {
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;
    typedef std::basic_stringstream<char_type> stringstream_type;
    typedef ::io::basic_separator<char_type> separator_type;
    typedef ::io::basic_enclosure<char_type> enclosure_type;
    typedef basic_tuple_join<char_type> join_type;


    template<class Tuple>
    auto operator() (
            const Tuple& v,
            const enclosure_type& enclosure = enclosure_type::curly_braces,
            const separator_type& separator = separator_type::space) const
    -> string_type {
        stringstream_type ss;
        ss << enclosure.left();
        ss << join_type()(v, separator);
        ss << enclosure.right();
        return ss.str();
    }
};

using tuple_to_string  = basic_tuple_to_string<char>;
using tuple_to_wstring = basic_tuple_to_string<wchar_t>;

}   //-- namespace utility --
}   //-- namespace io --
}   //-- namespace fn --


#endif /* LIB_FN_IO_UTILITY_TUPLE_TO_STRING_HPP_ */
