/*
 * join.hpp
 *
 *  Created on: Sep 18, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_IO_UTILITY_VECTOR_JOIN_HPP_
#define LIB_FN_IO_UTILITY_VECTOR_JOIN_HPP_


#include <string>
#include <sstream>

#include "../../../io/separator.hpp"


namespace fn {
namespace io {
namespace utility {

template<typename CharT>
struct basic_vector_join {
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;
    typedef std::basic_stringstream<char_type> stringstream_type;
    typedef ::io::basic_separator<char_type> separator_type;

    template<class Vector>
    auto operator() (
            const Vector& v,
            separator_type separator = separator_type::space) const
    -> string_type {
        stringstream_type ss;
        bool first = true;
        for (const auto& val : v) {
            if (!first)
                ss << separator;
            ss << val;
            first = false;
        }
        return ss.str();
    }

    template<class ForwardIterator>
    auto operator() (
            ForwardIterator begin,
            ForwardIterator end,
            separator_type separator = separator_type::space) const
    -> string_type {
        stringstream_type ss;
        bool first = true;
        for (ForwardIterator it = begin; it != end; ++it) {
            if (!first)
                ss << separator;
            ss << *it;
            first = false;
        }
        return ss.str();
    }

};

using join  = basic_vector_join<char>;
using wjoin = basic_vector_join<wchar_t>;

}   //-- namespace utility --
}   //-- namespace io --
}   //-- namespace fn --


#endif /* LIB_FN_IO_UTILITY_VECTOR_JOIN_HPP_ */
