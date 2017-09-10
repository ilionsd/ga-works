/*
 * join.hpp
 *
 *  Created on: Sep 4, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_JOIN_HPP_
#define LIB_IO_JOIN_HPP_


#include <string>
#include <sstream>


namespace io {
namespace utility {

template<class V, typename CharT>
inline auto join(const V& v, const std::basic_string<CharT>& separator = " ")
-> std::basic_string<CharT> {
    std::basic_stringstream<CharT> ss;
    bool first = true;
    for (const auto& val : v) {
        if (!first)
            ss << separator;
        ss << val;
        first = false;
    }
    return ss.str();
}

template<class ForwardIterator, typename CharT>
inline auto join(ForwardIterator begin, ForwardIterator end, const std::basic_string<CharT>& separator = " ")
-> std::basic_string<CharT> {
    std::basic_stringstream<CharT> ss;
    bool first = true;
    for (ForwardIterator it = begin; it != end; ++it) {
        if (!first)
            ss << separator;
        ss << *it;
        first = false;
    }
    return ss.str();
}

}   //-- namespace utility --
}   //-- namespace io --


#endif /* LIB_IO_JOIN_HPP_ */
