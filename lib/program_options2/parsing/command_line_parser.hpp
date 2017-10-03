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
#include <set>
#include <map>
#include <vector>

#include "../utility/compare.hpp"
#include "../description/option.hpp"


namespace program_options2 {
namespace parsing {

template<typename CharT>
class basic_command_line_parser {
public:
    typedef CharT char_type;
    typedef ::program_options2::description::basic_option<char_type> option_type;
    typedef std::basic_string<char_type> string_type;
    typedef std::set<option_type, utility::less<char_type>> set;

    inline
    basic_command_line_parser(set&& options) :
        mOptions(options)
    {}

    std::map<option_type, string_type>
    operator() (const std::vector<string_type>& args) const {
        std::map<option_type, string_type> map;
        return map;
    }

private:
    set mOptions;
};

template<typename CharT>
std::map<description::basic_option<CharT>, std::basic_string<CharT>>
parse_command_line(const basic_command_line_parser<CharT>& parser, std::size_t argc, CharT** argv) {
    typedef std::basic_string<CharT> string_type;
    std::vector<string_type> args;
    for (std::size_t k = 0; k < argc; ++k)
        args.push_back(argv[k]);

    return parser(args);
}

}   //-- namespace parsing --
}   //-- namespace program_options --


#endif /* LIB_PROGRAM_OPTIONS2_PARSING_COMMAND_LINE_PARSER_HPP_ */
