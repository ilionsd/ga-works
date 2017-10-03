/*
 * option.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_HPP_
#define LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_HPP_


#include <string>
#include <ostream>
#include <sstream>
#include <functional>

#include "../../io/names/complex_names.hpp"


namespace program_options2 {
namespace description {

template<typename CharT>
class basic_option {
public:
    typedef CharT char_type;
    typedef basic_option<char_type> self_type;
    typedef ::io::names::basic_complex_names<char_type> names_type;
    typedef std::basic_string<char_type> string_type;
    typedef std::basic_stringstream<char_type> stringstream_type;
    typedef std::basic_ostringstream<char_type> ostringstream_type;

    inline
    basic_option() :
        mNames(),
        mDescription(),
        mHasValue(false)
    {}
    inline
    basic_option(names_type&& name) :
        mNames(name),
        mDescription(),
        mHasValue(false)
    {}
    inline
    basic_option(names_type&& name, string_type&& description) :
        mNames(name),
        mDescription(description),
        mHasValue(false)
    {}
    inline
    basic_option(names_type&& name, string_type&& description, bool hasValue) :
        mNames(name),
        mDescription(description),
        mHasValue(hasValue)
    {}

    inline
    basic_option(const self_type& other) :
        mNames(other.mNames),
        mDescription(other.mDescription.str()),
        mHasValue(other.mHasValue)
    {}

    inline
    self_type&
    operator= (const self_type& other) {
        mNames  = other.mNames;
        mDescription.str(other.mDescription.str());
        mHasValue = other.mHasValue;
        return *this;
    }

    inline
    const names_type&
    names() const {
        return mNames;
    }
    inline
    names_type&
    names() {
        return mNames;
    }

    inline
    const bool
    has_value() const {
        return mHasValue;
    }
    inline
    bool&
    has_value() {
        return mHasValue;
    }

    inline
    const ostringstream_type&
    description() const {
        return mDescription;
    }
    inline
    ostringstream_type&
    description() {
        return mDescription;
    }

private:
    names_type mNames;
    stringstream_type mDescription;
    bool mHasValue;
};

template<typename CharT>
std::basic_ostream<CharT>&
operator<< (std::basic_ostream<CharT>& os, const basic_option<CharT>& option) {
    os << "\t" << option.format_short_name() << "," << option.format_full_name() << " :\t" << option.description();
    return os;
}

}   //-- namespace description --
}   //-- namespace program_options2 --


#endif /* LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_HPP_ */
