/*
 * names.hpp
 *
 *  Created on: Sep 21, 2017
 *      Author: ilion
 */

#ifndef INCLUDE_IO_NAMES_HPP_
#define INCLUDE_IO_NAMES_HPP_

#include "../../lib/io/names/root.hpp"
#include "../../lib/io/names/path.hpp"
#include "../../lib/io/names/names.hpp"
#include "../../lib/io/names/complex_names.hpp"
//#include "../../lib/io/names/qualified_name.hpp"


namespace io {
namespace names {

template<typename CharT> class basic_root;
using  root = basic_root<char>;
using wroot = basic_root<wchar_t>;

template<typename CharT> class basic_path;
using  path = basic_path<char>;
using wpath = basic_path<wchar_t>;

template<typename CharT> class basic_names;
using  names = basic_names<char>;
using wnames = basic_names<wchar_t>;

template<typename CharT> class basic_complex_names;
using complex_names  = basic_complex_names<char>;
using complex_wnames = basic_complex_names<wchar_t>;

//template<typename CharT> class basic_xmlns;
//using xmlns  = basic_xmlns<char>;
//using wxmlns = basic_xmlns<wchar_t>;
//
//template<typename CharT> class basic_qualified_name;
//using qualified_name  = basic_qualified_name<char>;
//using wqualified_name = basic_qualified_name<wchar_t>;

}   //-- namespace names --
}   //-- namespace io --


#endif /* INCLUDE_IO_NAMES_HPP_ */
