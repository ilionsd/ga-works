/*
 * command_line_parser.hpp
 *
 *  Created on: Sep 11, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_PARSING_COMMAND_LINE_PARSER_HPP_
#define LIB_PROGRAM_OPTIONS2_PARSING_COMMAND_LINE_PARSER_HPP_


#include <cstddef>
#include <functional>
#include <string>
#include <set>
#include <map>
#include <vector>

#include "../../fn/casting.hpp"
#include "../utility/compare.hpp"
#include "../description/base_option.hpp"


namespace program_options2 {
namespace parsing {

template<typename CharT>
class basic_command_line_parser {
public:
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;
    typedef description::base_option<char_type> option_type;
    typedef std::set<
            std::reference_wrapper<option_type>,
                utility::less<CharT>> set;
    typedef std::vector<option_type> vector;

    inline
    basic_command_line_parser(set&& options) :
        mOptions(options)
    {}

    vector
    operator() (const std::vector<string_type>& args) const {
        vector options;

        return options;
    }

private:
    set mOptions;
};

template<typename CharT>
typename basic_command_line_parser<CharT>::vector
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
