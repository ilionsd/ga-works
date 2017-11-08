/*
 * options_group.hpp
 *
 *  Created on: Sep 20, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTIONS_GROUP_HPP_
#define LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTIONS_GROUP_HPP_


#include <functional>
#include <set>
#include <string>
#include <ostream>
#include <variant>

#include "../../language/overloaded.hpp"
#include "../../fn/casting.hpp"
#include "../utility/compare.hpp"
#include "base_option.hpp"


namespace program_options2 {
namespace description {

template<typename CharT>
class basic_options_group {
public:
    typedef CharT char_type;
    typedef basic_options_group<char_type> self_type;
    typedef std::basic_string<char_type> string_type;
    typedef base_option<char_type> option_type;
    typedef std::variant<self_type, std::reference_wrapper<option_type>> variant_type;

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
    basic_options_group(const string_type& caption, const std::vector<variant_type>& children) :
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
    add_option(option_type& option) {
        mChildren.emplace_back(std::ref(option));
        return *this;
    }
    inline
    self_type&
    add_group(self_type& group) {
        mChildren.emplace_back(group);
        return *this;
    }

    inline
    self_type&
    operator<< (option_type& val) {
        return add_option(val);
    }
    inline
    self_type&
    operator<< (self_type& val) {
        return add_group(val);
    }

    inline
    const std::vector<variant_type>&
    children() const {
        return mChildren;
    }
    inline
    std::vector<variant_type>&
    children() {
        return mChildren;
    }

private:
    string_type mCaption;
    std::vector<variant_type> mChildren;
};

template<typename CharT>
std::basic_ostream<CharT>&
operator<< (std::basic_ostream<CharT>& os, const basic_options_group<CharT>& val) {
    os << val.caption() << std::endl;
    for (const auto& child : val.children())
        os << child << std::endl;
    return os;
}

template<typename T, typename Compare>
struct variant_compare {
    template<typename... T1s, typename... T2s>
    auto operator() (const std::variant<T1s...>& a, const std::variant<T2s...>& b) const {
        return Compare() (std::visit(::fn::static_cast_f<T>(), a), std::visit(::fn::static_cast_f<T>(), b));
    }
};

template<typename CharT>
inline
std::set<
    std::reference_wrapper<typename basic_options_group<CharT>::option_type>,
    utility::less<CharT>>
options(const std::reference_wrapper<typename basic_options_group<CharT>::option_type>& option) {
    return { std::ref(option) };
}
template<typename CharT>
std::set<
    std::reference_wrapper<typename basic_options_group<CharT>::option_type>,
    utility::less<CharT>>
options(const basic_options_group<CharT>& group) {
    std::set<
        std::reference_wrapper<typename basic_options_group<CharT>::option_type>,
        utility::less<CharT>> set;
    for (const auto& child : group.children())
        std::visit([&set](const auto& item) {
                auto childrenSet = options<CharT>(item);
                set.insert(childrenSet.begin(), childrenSet.end());}, child);
    return set;
}

}   //-- namespace description --
}   //-- namespace program_options2 --


#endif /* LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTIONS_GROUP_HPP_ */
