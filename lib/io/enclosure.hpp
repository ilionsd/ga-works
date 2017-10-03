/*
 * enclosure.hpp
 *
 *  Created on: Sep 9, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_NAMES_ENCLOSURE_HPP_
#define LIB_IO_NAMES_ENCLOSURE_HPP_


#include <string>
#include <ostream>
#include <utility>

#include "../language/anybase_enum.hpp"


namespace io {

template<typename CharT>
class basic_enclosure final :
        public ::language::anybase_enum<
            std::pair<std::basic_string<CharT>, std::basic_string<CharT>>,
            basic_enclosure<CharT>> {
public:
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;
    typedef basic_enclosure<char_type> self_type;
    typedef ::language::anybase_enum<std::pair<string_type, string_type>, self_type> base_type;
    typedef typename base_type::underlying_type underlying_type;

    friend
    ::language::add_value<self_type>;

    inline
    operator underlying_type() const {
        return this->value();
    }

    inline
    const string_type&
    left() const {
        return this->value().first;
    }
    inline
    const string_type&
    right() const {
        return this->value().second;
    }

    static const self_type curly_braces;
    static const self_type round_braces;
    static const self_type square_braces;
};

template<typename CharT>
const basic_enclosure<CharT>
basic_enclosure<CharT>::curly_braces ( std::make_pair("{", "}") );
template<typename CharT>
const basic_enclosure<CharT>
basic_enclosure<CharT>::round_braces ( std::make_pair("(", ")") );
template<typename CharT>
const basic_enclosure<CharT>
basic_enclosure<CharT>::square_braces ( std::make_pair("[", "]") );

template<typename CharT>
std::basic_ostream<CharT>&
operator<< (std::basic_ostream<CharT>& os, const basic_enclosure<CharT>& val) {
    os << val.left() << val.right();
    return os;
}

}   //-- namespace io --


#endif /* LIB_IO_NAMES_ENCLOSURE_HPP_ */
