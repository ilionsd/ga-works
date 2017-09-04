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
#include <vector>


namespace io {

template<typename V>
struct join {
    typedef V vector_type;

    template<typename CharT>
    auto operator() (const vector_type& v, const std::basic_string<CharT>& separator = " ")
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
};

}   //-- namespace io --


#endif /* LIB_IO_JOIN_HPP_ */
