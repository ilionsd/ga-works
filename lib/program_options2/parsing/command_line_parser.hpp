/*
 * command_line_parser.hpp
 *
 *  Created on: Sep 11, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_PARSING_COMMAND_LINE_PARSER_HPP_
#define LIB_PROGRAM_OPTIONS2_PARSING_COMMAND_LINE_PARSER_HPP_


#include <cstddef>
#include <string>
#include <vector>
#include <unordered_map>

#include "../definition/option.hpp"


namespace program_options2 {
namespace parsing {

template<typename CharT>
class basic_command_line_parser;

template<typename CharT>
auto parse_command_line(const basic_command_line_parser<CharT>&, std::size_t, CharT**);

template<typename CharT>
class basic_command_line_parser {
public:
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;

    inline
    basic_command_line_parser()
    {}

    auto parse(const std::vector<string_type>& args) const -> int {
        //std::map<>
        return 0;
    }

private:

};

using command_line_parser = basic_command_line_parser<char>;
using wcommand_line_parser = basic_command_line_parser<wchar_t>;

template<typename CharT>
auto parse_command_line(basic_command_line_parser<CharT>& parser, std::size_t argc, CharT** argv) -> int {
    typedef std::basic_string<CharT> string_type;
    std::vector<string_type> args;
    for (std::size_t k = 0; k < argc; ++k)
        args.push_back(argv[k]);
    return parser.parse(args);
}

}   //-- namespace parsing --
}   //-- namespace program_options --


#endif /* LIB_PROGRAM_OPTIONS2_PARSING_COMMAND_LINE_PARSER_HPP_ */
