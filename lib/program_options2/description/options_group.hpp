/*
 * options_group.hpp
 *
 *  Created on: Sep 20, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTIONS_GROUP_HPP_
#define LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTIONS_GROUP_HPP_


#include <set>
#include <string>
#include <ostream>
#include <variant>

#include "../utility/compare.hpp"
#include "option.hpp"

namespace program_options2 {
namespace description {

template<typename CharT>
class basic_options_group {
public:
    typedef CharT char_type;
    typedef basic_options_group<char_type> self_type;
    typedef std::basic_string<char_type> string_type;
    typedef basic_option<char_type> option_type;

    inline
    basic_options_group() :
        mCaption(),
        mChildren()
    {}
    inline
    basic_options_group(const string_type& caption) :
        mCaption(caption),
        mChildren()
    {}
    inline
    basic_options_group(const string_type& caption, const std::vector<std::variant<option_type, self_type>>& children) :
        mCaption(caption),
        mChildren(children)
    {}

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
    self_type&
    add_option(const option_type& option) {
        mChildren.emplace_back(option);
        return *this;
    }
    inline
    self_type&
    add_group(const self_type& group) {
        mChildren.emplace_back(group);
        return *this;
    }

    inline
    self_type&
    operator<< (const option_type& val) {
        return add_option(val);
    }
    inline
    self_type&
    operator<< (const self_type& val) {
        return add_group(val);
    }

    inline
    const std::vector<std::variant<option_type, self_type>>&
    children() const {
        return mChildren;
    }
    inline
    std::vector<std::variant<option_type, self_type>>&
    children() {
        return mChildren;
    }

private:
    string_type mCaption;
    std::vector<std::variant<option_type, self_type>> mChildren;
};

template<typename CharT>
std::basic_ostream<CharT>&
operator<< (std::basic_ostream<CharT>& os, const basic_options_group<CharT>& val) {
    os << val.caption() << std::endl;
    for (const auto& child : val.children())
        os << child << std::endl;
    return os;
}

template<typename CharT>
inline
std::set<::program_options2::description::basic_option<CharT>, utility::less<CharT>>
options(const ::program_options2::description::basic_option<CharT>& option) {
    return { option };
}
template<typename CharT>
std::set<::program_options2::description::basic_option<CharT>, utility::less<CharT>>
options(const ::program_options2::description::basic_options_group<CharT>& group) {
    std::set<::program_options2::description::basic_option<CharT>, utility::less<CharT>> set;
    for (auto&& child : group.children())
        std::visit([&set](auto&& val) {
            auto inner = options(val);
            set.insert(inner.begin(), inner.end());
        }, child);
    return set;
}

}   //-- namespace description --
}   //-- namespace program_options2 --


#endif /* LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTIONS_GROUP_HPP_ */
