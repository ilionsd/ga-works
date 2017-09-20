/*
 * separator.hpp
 *
 *  Created on: Sep 9, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_NAMES_SEPARATOR_HPP_
#define LIB_IO_NAMES_SEPARATOR_HPP_


#include <string>
#include <ostream>

#include "../language/anybase_enum.hpp"


namespace io {

template<typename CharT>
class basic_separator final :
        public ::language::anybase_enum<std::basic_string<CharT>, basic_separator<CharT>> {
public:
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;
    typedef basic_separator<char_type> self_type;
    typedef ::language::anybase_enum<string_type, self_type> base_type;

    friend
    ::language::add_value<self_type>;

    using base_type::base_type;

    static const self_type space;
    static const self_type coma;
    static const self_type dot;
    static const self_type colon;
    static const self_type doublecolon;
    static const self_type slash;
    static const self_type backslash;
    static const self_type endline;
    static const self_type tab;
};

template<typename CharT>
const basic_separator<CharT> basic_separator<CharT>::space(" ");
template<typename CharT>
const basic_separator<CharT> basic_separator<CharT>::coma(",");
template<typename CharT>
const basic_separator<CharT> basic_separator<CharT>::dot(".");
template<typename CharT>
const basic_separator<CharT> basic_separator<CharT>::colon(":");
template<typename CharT>
const basic_separator<CharT> basic_separator<CharT>::doublecolon("::");
template<typename CharT>
const basic_separator<CharT> basic_separator<CharT>::slash("/");
template<typename CharT>
const basic_separator<CharT> basic_separator<CharT>::backslash("\\");
template<typename CharT>
const basic_separator<CharT> basic_separator<CharT>::endline("\n");
template<typename CharT>
const basic_separator<CharT> basic_separator<CharT>::tab("\t");

using separator = basic_separator<char>;
using wseparator = basic_separator<wchar_t>;

template<typename CharT>
std::basic_ostream<CharT>&
operator<< (std::basic_ostream<CharT>& os, const basic_separator<CharT>& val) {
    os << val.value();
    return os;
}

}   //-- namespace io --


#endif /* LIB_IO_NAMES_SEPARATOR_HPP_ */
