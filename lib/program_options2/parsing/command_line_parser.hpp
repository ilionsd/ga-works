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
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include "../../fn/casting.hpp"
#include "../utility/compare.hpp"
#include "../description/base_option.hpp"
#include "formatter.hpp"


namespace program_options2 {
namespace parsing {

template<typename CharT>
std::basic_stringstream<CharT>
argument_stream(
        const std::vector<std::basic_string<CharT>>& args,
        const std::pair<std::size_t, std::size_t>& indices);

template<typename CharT>
class basic_command_line_parser {
public:
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;
    typedef description::base_option<char_type> option_type;
    typedef std::set<
                std::reference_wrapper<option_type>,
                utility::less<CharT>> set;
    typedef std::vector<std::reference_wrapper<option_type>> vector;

    inline
    basic_command_line_parser(const set& optionRefs) :
        formatter(basic_name_formatter<char_type>()),
        short_formatter(basic_shortname_formatter<char_type>()),
        mOptionRefs(optionRefs)
    {}
    inline
    basic_command_line_parser(const set& optionRefs, std::function<string_type(string_type)> formatter) :
        formatter(formatter),
        short_formatter(basic_shortname_formatter<char_type>()),
        mOptionRefs(optionRefs)
    {}
    inline
    basic_command_line_parser(
            const set& optionRefs,
            std::function<string_type(string_type)> formatter,
            std::function<string_type(string_type)> shortFormatter) :
        formatter(formatter),
        short_formatter(shortFormatter),
        mOptionRefs(optionRefs)
    {}

    vector
    operator() (const std::vector<string_type>& args) const {
        vector options;
        auto      nameOption = map_options(std::mem_fn(&option_type::names_type::name     ),       formatter);
        auto shortnameOption = map_options(std::mem_fn(&option_type::names_type::shortname), short_formatter);

        std::map<
            std::reference_wrapper<option_type>,
            std::pair<std::size_t, std::size_t>,
            utility::less<char_type>> optionIndices;

        typedef typename std::map<string_type, std::reference_wrapper<option_type>>::iterator nameoption_iterator;
        typedef typename decltype(optionIndices)::iterator optionindices_iterator;

        optionindices_iterator lastInserted = optionIndices.end();
        for (std::size_t k = 0; k < args.size(); ++k) {
            std::optional<nameoption_iterator> optionalNameIterator;
            if (auto temp1 = nameOption.find(args[k]); temp1 != nameOption.end())
                optionalNameIterator = temp1;
            if (auto temp2 = shortnameOption.find(args[k]); temp2 != shortnameOption.end())
                optionalNameIterator = temp2;

            if (optionalNameIterator) {
                std::tie(lastInserted, std::ignore) = optionIndices.emplace(optionalNameIterator.value()->second, std::make_pair(k + 1, k + 1));
                options.push_back(lastInserted->first);
            }
            else if (lastInserted != optionIndices.end())
                ++(lastInserted->second.second);
        }

        for (const auto [optionRef, indices] : optionIndices) {
            optionRef.get().mark_present();
            std::basic_stringstream<char_type> ss = argument_stream(args, indices);
            optionRef.get().concept()->read(ss);
        }

        return options;
    }

protected:
    template<typename DataMember, typename F>
    std::map<string_type, std::reference_wrapper<option_type>>
    map_options(DataMember nameMember, F formatter) const {
        std::map<
            string_type,
            std::reference_wrapper<option_type>> nameMappedOptions;
        for (const auto& optionRef : mOptionRefs) {
            string_type formattedName = formatter(nameMember(optionRef.get().names()));
            nameMappedOptions.emplace(formattedName, optionRef);
        }
        return nameMappedOptions;
    }

public:
    std::function<string_type(string_type)> formatter;
    std::function<string_type(string_type)> short_formatter;

private:
    set mOptionRefs;
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

template<typename CharT>
std::basic_stringstream<CharT>
argument_stream(
        const std::vector<std::basic_string<CharT>>& args,
        const std::pair<std::size_t, std::size_t>& indices) {
    std::basic_stringstream<CharT> ss;
    auto b = std::next(args.cbegin(), indices.first);
    auto e = std::next(args.cbegin(), indices.second);
    auto osit = std::ostream_iterator<std::basic_string<CharT>>(ss);
    std::copy(b, e, osit);
    return ss;
}

}   //-- namespace parsing --
}   //-- namespace program_options --


#endif /* LIB_PROGRAM_OPTIONS2_PARSING_COMMAND_LINE_PARSER_HPP_ */
