/*
 * root.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_NAMES_ROOT_HPP_
#define LIB_IO_NAMES_ROOT_HPP_


#include <string>


namespace io {
namespace names {

template<typename CharT>
struct basic_root {
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;

    string_type value;
};

}   //-- namespace names --
}   //-- namespace io --


#endif /* LIB_IO_NAMES_ROOT_HPP_ */
