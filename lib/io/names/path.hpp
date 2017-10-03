/*
 * path.hpp
 *
 *  Created on: Sep 23, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_NAMES_PATH_HPP_
#define LIB_IO_NAMES_PATH_HPP_


#include <string>
#include <vector>

#include "../utility/string_slice.hpp"
#include "../utility/vector_join.hpp"
#include "../separator.hpp"

namespace io {
namespace names {

template<typename CharT>
struct basic_path {
    typedef CharT char_type;
    typedef basic_path<char_type> self_type;
    typedef std::basic_string<char_type> string_type;
    typedef ::io::basic_separator<char_type> separator_type;

    static const separator_type default_separator;

    inline
    basic_path() :
        slices()
    {}
    inline
    basic_path(const self_type& other) :
        slices(other.slices)
    {}

    inline
    self_type&
    operator= (const self_type& other) {
        slices = other.slices;
        return *this;
    }

    inline
    string_type
    build(const separator_type& separator) const {
        return ::io::utility::vector_join(slices, separator);
    }

    self_type&
    add(const string_type& str) {
        slices.push_back(str);
        return *this;
    }
    self_type&
    add(const string_type& str, const separator_type& separator) {
        slices.push_back(::io::utility::string_slice(str, separator));
        return *this;
    }
    inline
    self_type&
    add(const self_type& other) {
        slices.push_back(other.slices);
        return *this;
    }

    inline
    typename std::vector<string_type>::size_type
    size() const {
        return slices.size();
    }

    std::vector<string_type> slices;
};

}   //-- namespace names --
}   //-- namespace io --


#endif /* LIB_IO_NAMES_PATH_HPP_ */
