/*
 * options_group.hpp
 *
 *  Created on: Sep 11, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_DEFINITION_TUPLE_OPTIONS_GROUP_HPP_
#define LIB_PROGRAM_OPTIONS2_DEFINITION_TUPLE_OPTIONS_GROUP_HPP_


#include <string>
#include <ostream>
#include <map>
#include <vector>
#include <tuple>

#include "../../io/utility/tuple_join.hpp"
#include "option.hpp"


namespace program_options2 {
namespace definition {

template<typename CharT, typename... Ts>
class basic_tuple_options_group {
public:
    typedef CharT char_type;
    typedef std::tuple<Ts> tuple_type;
    typedef basic_tuple_options_group<char_type> self_type;
    typedef std::basic_string<char_type> string_type;
    typedef basic_option<char_type> option_type;

    inline
    basic_tuple_options_group() :
            mCaption(),
            mChildren()
    {}
    inline
    basic_tuple_options_group(const string_type& caption) :
            mCaption(caption),
            mChildren()
    {}
    inline
    basic_tuple_options_group(const string_type& caption, tuple_type&& children) :
            mCaption(caption),
            mChildren(std::move(children))
    {}

    inline
    auto
    add_option(const option_type& option) {
        typedef basic_tuple_options_group<char_type, Ts, option_type> next_group;
        return next_group( caption(), std::tuple_cat( children(), option ) );;
    }

    template<typename... otherTs>
    inline
    auto
    add_group(const basic_tuple_options_group<char_type, otherTs>& group) {
        typedef basic_tuple_options_group<char_type, otherTs> other_group;
        typedef basic_tuple_options_group<char_type, Ts, other_group> next_group;
        return next_group( caption(), std::tuple_cat( children(), group ) );
    }

    inline
    auto
    operator<< (const option_type& option) {
        return add_option(option);
    }
    inline
    auto
    operator<< (const self_type& group) {
        return add_group(group);
    }

    inline
    const string_type&
    caption() const {
        return mCaption;
    }
    inline
    string_type&
    caption() {
        return mCaption;
    }

    inline
    const tuple_type&
    children() const {
        return mChildren;
    }
    inline
    tuple_type&
    children() {
        return mChildren;
    }

private:
    string_type mCaption;
    tuple_type mChildren;
};

template<typename... Ts>
using tuple_options_group = basic_tuple_options_group<char, Ts>;

template<typename... Ts>
using wtuple_options_group = basic_tuple_options_group<wchar_t, Ts>;

template<typename CharT, typename... Ts>
std::basic_ostream<CharT>&
operator<< (std::basic_ostream<CharT>& os, const basic_tuple_options_group<CharT, Ts...>& group) {
    os << group.caption() << std::endl;
    os << ::io::utility::tuple_join(group.children(), ::io::basic_separator<CharT>::endline);
    os << std::endl;
    return os;
}

}   //-- namespace definition --
}   //-- namespace program_options2 --


#endif /* LIB_PROGRAM_OPTIONS2_DEFINITION_TUPLE_OPTIONS_GROUP_HPP_ */
