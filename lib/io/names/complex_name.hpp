/*
 * qualified_name.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_NAMES_COMPLEX_NAME_HPP_
#define LIB_IO_NAMES_COMPLEX_NAME_HPP_


#include <string>
#include <vector>
#include <experimental/optional>

#include "../utility/vector_join.hpp"
#include "../separator.hpp"


namespace io {
namespace names {

template<typename CharT>
class basic_complex_name {
public:
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;
    typedef basic_separator<char_type> separator_type;

    typedef basic_complex_name<char_type> self_type;

    static const separator_type default_separator;

    inline
    basic_complex_name() :
        mSeparator(default_separator),
        mName()
    {}
    inline
    basic_complex_name(const string_type& separator) :
        mSeparator(separator),
        mName()
    {}
    inline
    basic_complex_name(const self_type& other) :
        mSeparator(other.mSeparator),
        mName(other.mName)
    {}

    inline
    bool
    operator== (const self_type& other) const {
        return name() == other.name();
    }
    inline
    bool
    operator!= (const self_type& other) const {
        return name() != other.name();
    }
    inline
    bool
    operator< (const self_type& other) const {
        return name() < other.name();
    }
    inline
    bool
    operator> (const self_type& other) const {
        return name() > other.name();
    }
    inline
    bool
    operator<= (const self_type& other) const {
        return name() <= other.name();
    }
    inline
    bool
    operator>= (const self_type& other) const {
        return name() >= other.name();
    }

    inline
    const string_type&
    short_name() const {
        if (!mShortName)
            mShortName = mName[mName.size() - 1];
        return mShortName.value();
    }
    inline
    void short_name(const string_type& val) {
        invalidate();
        mShortName = val;
    }
    inline
    const string_type&
    prefix() const {
        if (!mPrefix)
            mPrefix = ::io::utility::vector_join(name().cbegin(), --name().cend(), separator());
        return mPrefix.value();
    }
    inline const string_type&
    full_name() const {
        return prefix() + short_name();
    }

    inline
    self_type&
    add(const char_type* path) {
        return add(string_type(path));
    }
    self_type&
    add(const string_type& path) {
        invalidate();
        typedef typename string_type::size_type size_type;
        size_type pos = 0;
        do {
            size_type next = path.find_first_of(separator(), pos);
            name().push_back(path.substr(pos, next - pos));
            pos = next + 1;
        }
        while (string_type::npos == pos);
        return *this;
    }
    inline
    self_type&
    add(const self_type& path) {
        invalidate();
        name().push_back(path.name());
        return *this;
    }

    inline
    void
    separator(const separator_type& val) {
        invalidate();
        mSeparator = val;
    }
    inline
    const separator_type&
    separator() const {
        return mSeparator;
    }

    inline
    const std::vector<string_type>&
    name() const {
        return mName;
    }

protected:
    void invalidate() {
        mShortName.reset();
        mPrefix.reset();
    }

private:
    separator_type mSeparator;
    std::vector<string_type> mName;

    mutable std::experimental::optional<string_type> mShortName;
    mutable std::experimental::optional<string_type> mPrefix;
};

template<typename CharT>
const typename basic_complex_name<CharT>::separator_type
basic_complex_name<CharT>::default_separator = basic_complex_name<CharT>::separator_type::space;

using complex_name = basic_complex_name<char>;
using complex_wname = basic_complex_name<wchar_t>;

}   //-- namespace names --
}   //-- namespace io --


#endif /* LIB_IO_NAMES_COMPLEX_NAME_HPP_ */
