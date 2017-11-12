/*
 * formatter.hpp
 *
 *  Created on: Sep 25, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_PARSING_FORMATTER_HPP_
#define LIB_PROGRAM_OPTIONS2_PARSING_FORMATTER_HPP_


#include <string>


namespace program_options2 {
namespace parsing {

template<typename CharT>
struct basic_name_formatter {
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;

    inline
    string_type
    operator() (const string_type& name) const {
        return string_type("--") + name;
    }

};

template<typename CharT>
struct basic_shortname_formatter {
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;

    inline
    string_type
    operator() (const string_type& name) const {
        return string_type("-") + name;
    }

};

}   //-- namespace parsing --
}   //-- namespace program_options2 --


#endif /* LIB_PROGRAM_OPTIONS2_PARSING_FORMATTER_HPP_ */
