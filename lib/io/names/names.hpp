/*
 * name.hpp
 *
 *  Created on: Sep 23, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_NAMES_NAMES_HPP_
#define LIB_IO_NAMES_NAMES_HPP_


#include <string>
#include <tuple>
#include <utility>


namespace io {
namespace names {

template<typename CharT>
struct basic_names {
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;

    inline
    basic_names() :
        name(name),
        shortname(shortname)
    {}
    inline
    basic_names(std::basic_string_view<char_type> name) :
        name(name),
        shortname(shortname)
    {}
    inline
    basic_names(std::basic_string_view<char_type> name, std::basic_string_view<char_type> shortname) :
        name(name),
        shortname(shortname)
    {}

    inline
    const auto
    as_tuple() const {
        return std::tie(name, shortname);
    }
    inline
    auto
    as_tuple() {
        return std::tie(name, shortname);
    }

    string_type name, shortname;
};

}   //-- namespace names --
}   //-- namespace io --


#endif /* LIB_IO_NAMES_NAMES_HPP_ */
