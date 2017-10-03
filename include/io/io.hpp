/*
 * io.hpp
 *
 *  Created on: Sep 25, 2017
 *      Author: ilion
 */

#ifndef INCLUDE_IO_IO_HPP_
#define INCLUDE_IO_IO_HPP_


#include "../../lib/io/separator.hpp"
#include "../../lib/io/enclosure.hpp"


namespace io {

template<typename CharT> class basic_separator;
using separator = basic_separator<char>;
using wseparator = basic_separator<wchar_t>;

template<typename CharT> class basic_enclosure;
using enclosure = basic_enclosure<char>;
using wenclosure = basic_enclosure<wchar_t>;

}   //-- namespace io --


#endif /* INCLUDE_IO_IO_HPP_ */
