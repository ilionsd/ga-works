/*
 * definition.hpp
 *
 *  Created on: Sep 22, 2017
 *      Author: ilion
 */

#ifndef INCLUDE_PROGRAM_OPTIONS2_DESCRIPTION_HPP_
#define INCLUDE_PROGRAM_OPTIONS2_DESCRIPTION_HPP_


#include "../../lib/program_options2/description/option.hpp"
#include "../../lib/program_options2/description/options_group.hpp"


namespace program_options2 {
namespace description {

template<typename CharT> class basic_option;
using  option = basic_option<char>;
using woption = basic_option<wchar_t>;

template<typename CharT> class basic_options_group;
using  options_group = basic_options_group<char>;
using woptions_group = basic_options_group<wchar_t>;

}   //-- namespace description --
}   //-- namespace program_options2 --


#endif /* INCLUDE_PROGRAM_OPTIONS2_DESCRIPTION_HPP_ */
