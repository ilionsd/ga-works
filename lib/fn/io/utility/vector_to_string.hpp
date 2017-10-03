/*
 * to_string.hpp
 *
 *  Created on: Sep 18, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_IO_UTILITY_VECTOR_TO_STRING_HPP_
#define LIB_FN_IO_UTILITY_VECTOR_TO_STRING_HPP_


#include <string>
#include <utility>

#include "vector_join.hpp"


namespace fn {
namespace io {
namespace utility {

template<typename CharT>
struct vector_to_string {
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;
    typedef std::basic_stringstream<char_type> stringstream_type;
    typedef vector_join<char_type> join_type;

    template<class Vector>
    auto operator() (
            const Vector& v,
            const std::pair<string_type, string_type>& enclosure,
            const string_type& separator) const
    -> string_type {
        stringstream_type ss;
        ss << enclosure.first;
        ss << join_type()(v, separator);
        ss << enclosure.second;
        return ss.str();
    }

    template<class ForwardIterator>
    auto operator() (
            ForwardIterator begin,
            ForwardIterator end,
            const std::pair<string_type, string_type>& enclosure,
            const string_type& separator) const
    -> string_type {
        stringstream_type ss;
        ss << enclosure.left();
        ss << join_type()(begin, end, separator);
        ss << enclosure.right();
        return ss.str();
    }
};

}   //-- namespace utility --
}   //-- namespace io --
}   //-- namespace fn --


#endif /* LIB_FN_IO_UTILITY_VECTOR_TO_STRING_HPP_ */
