/*
 * qualified_name.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_NAMES_COMPLEX_NAMES_HPP_
#define LIB_IO_NAMES_COMPLEX_NAMES_HPP_


#include <string>
#include <sstream>

#include "../utility/vector_join.hpp"
#include "../separator.hpp"
#include "names.hpp"
#include "root.hpp"
#include "path.hpp"


namespace io {
namespace names {

template<typename CharT>
class basic_complex_names : public basic_names<CharT> {
public:
    typedef CharT char_type;
    typedef basic_complex_names<char_type> self_type;
    typedef basic_names<char_type> base_type;
    typedef std::basic_string<char_type> string_type;
    typedef std::basic_stringstream<char_type> stringstream_type;
    typedef basic_separator<char_type> separator_type;
    typedef basic_root<char_type> root_type;
    typedef basic_path<char_type> path_type;

    static const separator_type default_separator;

    inline
    basic_complex_names() :
        base_type(),
        mSeparator(default_separator),
        mRoot(),
        mPath()
    {}
    inline
    basic_complex_names(const separator_type& separator) :
        base_type(),
        mSeparator(separator),
        mRoot(),
        mPath()
    {}
    inline
    basic_complex_names(const self_type& other) :
        base_type(other),
        mSeparator(other.mSeparator),
        mRoot(other.mRoot),
        mPath(other.mPath)
    {}

    inline
    self_type&
    operator= (const self_type& other) {
        as_tuple() = other.as_tuple();
        return *this;
    }

    inline
    const auto
    as_tuple() const {
        return std::tuple_cat(base_type::as_tuple(), std::tie(mRoot, mPath, mSeparator));
    }
    inline
    auto
    as_tuple() {
        return std::tuple_cat(base_type::as_tuple(), std::tie(mRoot, mPath, mSeparator));
    }

    string_type
    prefix() const {
        stringstream_type ss;
        ss << mRoot.root << mPath.build(mSeparator);
        return ss.str();
    }

    inline
    self_type&
    operator<< (const root_type& root) {
        mRoot = root;
        return *this;
    }
    inline
    self_type&
    operator<< (const path_type& path) {
        mPath = path;
        return *this;
    }
    inline
    self_type&
    operator<< (const base_type& names) {
        base_type::as_tuple() = names.as_tuple();
        return *this;
    }

    inline
    const separator_type&
    separator() const {
        return mSeparator;
    }
    inline
    separator_type&
    separator() {
        return mSeparator;
    }

    inline
    const root_type&
    root() const {
        return mRoot;
    }
    inline
    root_type&
    root() {
        return mRoot;
    }

    inline
    const path_type&
    path() const {
        return mPath;
    }
    inline
    path_type&
    path() {
        return mPath;
    }

private:
    separator_type mSeparator;
    root_type mRoot;
    path_type mPath;
};

template<typename CharT>
const typename basic_complex_names<CharT>::separator_type
basic_complex_names<CharT>::default_separator = basic_complex_names<CharT>::separator_type::space;

}   //-- namespace names --
}   //-- namespace io --


#endif /* LIB_IO_NAMES_COMPLEX_NAMES_HPP_ */
