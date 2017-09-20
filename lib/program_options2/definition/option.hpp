/*
 * option.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_DEFINITION_OPTION_HPP_
#define LIB_PROGRAM_OPTIONS2_DEFINITION_OPTION_HPP_


#include <memory>
#include <string>
#include <ostream>
#include <sstream>
#include <functional>

#include "../../io/model/concept.hpp"
#include "../../io/names/complex_name.hpp"


namespace program_options2 {
namespace definition {

template<typename CharT>
class basic_option {
public:
    typedef CharT char_type;
    typedef basic_option<char_type> self_type;
    typedef ::io::model::concept<char_type> concept_type;
    typedef ::io::names::basic_complex_name<char_type> name_type;
    typedef std::basic_string<char_type> string_type;
    typedef std::basic_stringstream<char_type> stringstream_type;
    typedef std::basic_ostringstream<char_type> ostringstream_type;

    inline
    basic_option() :
        mNameRef(),
        mModelPtr(),
        mDescriptionRef()
    {}
    inline
    basic_option(const string_type& name) :
        mNameRef(name),
        mModelPtr(),
        mDescriptionRef()
    {}
    inline
    basic_option(const string_type& name, const std::shared_ptr<concept_type>& model) :
        mNameRef(name),
        mModelPtr(model),
        mDescriptionRef()
    {}
    inline
    basic_option(const string_type& name, const std::shared_ptr<concept_type>& model, const string_type& description) :
        mNameRef(name),
        mModelPtr(model),
        mDescriptionRef(description)
    {}

    inline
    basic_option(const self_type& other) :
        mNameRef(other.mNameRef),
        mModelPtr(other.mModelPtr),
        mDescriptionRef(other.mDescriptionRef)
    {}

    inline
    self_type&
    operator= (const self_type& other) {
        mNameRef  = other.mNameRef;
        mModelPtr = other.mModelPtr;
        mDescriptionRef = other.mDescriptionRef;
        return *this;
    }

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
    string_type
    format_short_name() const {
        return "-" + name().short_name();
    }
    inline
    string_type
    format_full_name() const {
        return "--" + name().full_name();
    }

    inline
    const name_type&
    name() const {
        return mNameRef.get();
    }
    inline
    name_type&
    name() {
        return mNameRef.get();
    }

    inline
    const std::shared_ptr<concept_type>&
    model() const {
        return mModelPtr;
    }
    inline
    std::shared_ptr<concept_type>&
    model() {
        return mModelPtr;
    }

    inline
    const ostringstream_type&
    description() const {
        return mDescriptionRef.get();
    }
    inline
    ostringstream_type&
    description() {
        return mDescriptionRef.get();
    }

private:
    std::reference_wrapper<name_type> mNameRef;
    std::shared_ptr<concept_type> mModelPtr;
    std::reference_wrapper<ostringstream_type> mDescriptionRef;
};

using option  = basic_option<char>;
using woption = basic_option<wchar_t>;

template<typename CharT>
std::basic_ostream<CharT>&
operator<< (std::basic_ostream<CharT>& os, const basic_option<CharT>& option) {
    os << "\t" << option.format_short_name() << "," << option.format_full_name() << " :\t" << option.description();
    return os;
}

}   //-- namespace definition --
}   //-- namespace program_options2 --


#endif /* LIB_PROGRAM_OPTIONS2_DEFINITION_OPTION_HPP_ */
