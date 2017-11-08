/*
 * base_option.hpp
 *
 *  Created on: Oct 22, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_BASE_OPTION_HPP_
#define LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_BASE_OPTION_HPP_


#include <string>
#include <sstream>

#include "../../../io/names/complex_names.hpp"


namespace program_options2 {
namespace description {
namespace option {
namespace detail2 {

template<typename CharT>
class basic_base_option {
public:
    typedef CharT char_type;
    typedef std::basic_stringstream<char_type> stringstream_type;
    typedef ::io::names::basic_complex_names<char_type> names_type;

    inline
    basic_base_option() :
        mNames(),
        mDescription()
    {}
    inline
    basic_base_option(const names_type& name) :
        mNames(name),
        mDescription()
    {}
    inline
    basic_base_option(const names_type& name, const std::basic_string<char_type>& description) :
        mNames(name),
        mDescription(description)
    {}
    inline
    basic_base_option(const basic_base_option<char_type>& other) :
        mNames(other.mNames),
        mDescription(other.mDescription.str())
    {}
    inline
    basic_base_option(basic_base_option<char_type>&& other) :
        mNames(std::move(other.mNames)),
        mDescription(std::move(other.mDescription))
    {}
    inline
    basic_base_option<char_type>&
    operator= (const basic_base_option<char_type>& other) {
        mNames  = other.mNames;
        mDescription.str(other.mDescription.str());
        return *this;
    }
    inline
    basic_base_option<char_type>&
    operator= (basic_base_option<char_type>&& other) {
        mNames  = std::move(other.mNames);
        mDescription = std::move(other.mDescription);
        return *this;
    }

    virtual ~basic_base_option() = default;

    virtual
    operator bool() const = 0;

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
    const stringstream_type&
    description() const {
        return mDescription;
    }
    inline
    stringstream_type&
    description() {
        return mDescription;
    }

private:
    names_type mNames;
    stringstream_type mDescription;
};

}   //-- namespace detail2 --
}   //-- namespace option --
}   //-- namespace description --
}   //-- namespace program_options2 --


#endif /* LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_BASE_OPTION_HPP_ */
