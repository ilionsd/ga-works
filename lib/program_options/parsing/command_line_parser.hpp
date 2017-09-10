/*
 * command_line_parser.hpp
 *
 *  Created on: Sep 11, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS_PARSING_COMMAND_LINE_PARSER_HPP_
#define LIB_PROGRAM_OPTIONS_PARSING_COMMAND_LINE_PARSER_HPP_


#include <string>
#include <vector>


namespace program_options {
namespace parsing {



template<typename CharT>
class basic_command_line_parser {
public:
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;


private:
    std::vector<string_type> mStringOptions;

};

}   //-- namespace parsing --
}   //-- namespace program_options --


#endif /* LIB_PROGRAM_OPTIONS_PARSING_COMMAND_LINE_PARSER_HPP_ */
