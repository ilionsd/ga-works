/*
 * parsing.hpp
 *
 *  Created on: Sep 26, 2017
 *      Author: ilion
 */

#ifndef INCLUDE_PROGRAM_OPTIONS2_PARSING_HPP_
#define INCLUDE_PROGRAM_OPTIONS2_PARSING_HPP_


#include "../../lib/program_options2/parsing/formatter.hpp"
#include "../../lib/program_options2/parsing/command_line_parser.hpp"


namespace program_options2 {
namespace parsing {

template<typename CharT> class basic_command_line_parser;
using  command_line_parser = basic_command_line_parser<char>;
using wcommand_line_parser = basic_command_line_parser<wchar_t>;

template<typename CharT>
std::map<description::basic_option<CharT>, std::basic_string<CharT>>
parse_command_line(const basic_command_line_parser<CharT>&, std::size_t, CharT**);

}   //-- namespace parsing --
}   //-- namespace program_options2 --


#endif /* INCLUDE_PROGRAM_OPTIONS2_PARSING_HPP_ */
