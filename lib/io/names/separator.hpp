/*
 * separator.hpp
 *
 *  Created on: Sep 9, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_NAMES_SEPARATOR_HPP_
#define LIB_IO_NAMES_SEPARATOR_HPP_


#include <string>

#include "../../language/anybase_enum.hpp"


namespace io {
namespace names {

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

    static const self_type space;
    static const self_type dot;
    static const self_type colon;
    static const self_type doublecolon;
    static const self_type slash;
    static const self_type backslash;
};

template<typename CharT>
const basic_separator<CharT> basic_separator<CharT>::space(" ");
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

using separator = basic_separator<char>;
using wseparator = basic_separator<wchar_t>;

}   //-- namespace names --
}   //-- namespace io --


#endif /* LIB_IO_NAMES_SEPARATOR_HPP_ */
