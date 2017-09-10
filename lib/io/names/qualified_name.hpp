/*
 * qualified_name.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_NAMES_QUALIFIED_NAME_HPP_
#define LIB_IO_NAMES_QUALIFIED_NAME_HPP_


#include <string>
#include <sstream>
#include <utility>
#include <experimental/optional>

#include "separator.hpp"
#include "enclosure.hpp"


namespace io {
namespace names {

template<typename CharT>
class basic_xmlns {
public:
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;
    typedef basic_xmlns<char_type> self_type;

    inline
    basic_xmlns() :
            mUri(),
            mPrefix()
    {}
    inline
    basic_xmlns(const string_type& uri) :
            mUri(uri),
            mPrefix()
    {};
    inline
    basic_xmlns(const string_type& uri, const string_type& prefix) :
            mUri(uri),
            mPrefix(prefix)
    {}

    inline
    const string_type&
    uri() const {
        return mUri;
    }
    inline
    string_type&
    uri() {
        return mUri;
    }

    inline
    const string_type&
    prefix() const {
        return mPrefix;
    }
    inline
    string_type&
    prefix() {
        return mPrefix;
    }

private:
    string_type mUri;
    string_type mPrefix;
};

template<typename CharT>
class basic_qualified_name {
public:
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;
    typedef basic_qualified_name<char_type> self_type;
    typedef basic_xmlns<char_type> xmlns_type;
    typedef basic_enclosure<char_type> enclosure_type;
    typedef basic_separator<char_type> separator_type;
    typedef std::basic_stringstream<char_type> stringstream_type;

    static const enclosure_type default_enclosure;
    static const separator_type default_separator;

    inline basic_qualified_name() :
            mSeparator(default_separator),
            mEnclosure(default_enclosure)
    {}

    inline
    const string_type&
    short_name() const {
        return mShortName;
    }
    inline
    void
    short_name(const string_type& val) {
        invalidate();
        mShortName = val;
    }
    inline
    const string_type&
    qname() const {
        if (!mQName)
            mQName = (stringstream_type() << ns().prefix() << separator() << short_name()).str();
        return mQName.value();
    }
    inline
    const string_type&
    full_name() const {
        if (!mFullName)
            mFullName = (stringstream_type() << enclosure().left() << ns().uri() << enclosure().right() << short_name()).str();
        return mFullName.value();
    }

    inline
    const xmlns_type&
    ns() const {
        return mNS;
    }
    inline
    void ns(const xmlns_type& val) {
        invalidate();
        mNS = val;
    }

    inline
    const separator_type&
    separator() const {
        return mSeparator;
    }
    inline
    void
    separator(const separator_type& val) {
        invalidate();
        mSeparator = val;
    }

    inline
    const enclosure_type&
    enclosure() const {
        return mEnclosure;
    }
    inline
    void
    enclosure(const enclosure_type& val) {
        invalidate();
        mEnclosure = val;
    }

protected:
    void invalidate() {
        mQName.reset();
        mFullName.reset();
    }

private:
    separator_type mSeparator;
    enclosure_type mEnclosure;

    xmlns_type mNS;
    string_type mShortName;

    mutable std::experimental::optional<string_type> mQName;
    mutable std::experimental::optional<string_type> mFullName;
};

template<typename CharT>
const typename basic_qualified_name<CharT>::enclosure_type
basic_qualified_name<CharT>::default_enclosure = basic_qualified_name<CharT>::enclosure_type::curly_braces;

template<typename CharT>
const typename basic_qualified_name<CharT>::separator_type
basic_qualified_name<CharT>::default_separator = basic_qualified_name<CharT>::separator_type::doublecolon;

using xmlns  = basic_xmlns<char>;
using wxmlns = basic_xmlns<wchar_t>;

using qualified_name  = basic_qualified_name<char>;
using wqualified_name = basic_qualified_name<wchar_t>;

}   //-- namespace names --
}   //-- namespace io --


#endif /* LIB_IO_NAMES_QUALIFIED_NAME_HPP_ */
