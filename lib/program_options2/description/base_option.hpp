/*
 * base_option.hpp
 *
 *  Created on: Nov 4, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_DESCRIPTION_BASE_OPTION_HPP_
#define LIB_PROGRAM_OPTIONS2_DESCRIPTION_BASE_OPTION_HPP_


#include <memory>
#include <sstream>
#include <string_view>

#include "../../io/names/complex_names.hpp"
#include "../../io/model/concept.hpp"


namespace program_options2 {
namespace description {

template<typename CharT>
class base_option {
public:
    typedef CharT char_type;
    typedef base_option<char_type> self_type;
    typedef std::basic_stringstream<char_type> stringstream_type;
    typedef std::basic_string_view<char_type> stringview_type;
    typedef ::io::names::basic_complex_names<char_type> names_type;
    typedef ::io::model::basic_concept<char_type> concept_type;

    inline
    base_option() :
        mNames(),
        mDescription()
    {}
    inline
    base_option(const names_type& name) :
        mNames(name),
        mDescription()
    {}
    inline
    base_option(const names_type& name, const stringview_type& description) :
        mNames(name),
        mDescription(description)
    {}
    inline
    base_option(const base_option<char_type>& other) :
        mNames(other.mNames),
        mDescription(other.mDescription.str())
    {}
    inline
    base_option(base_option<char_type>&& other) :
        mNames(std::move(other.mNames)),
        mDescription(std::move(other.mDescription))
    {}
    inline
    base_option<char_type>&
    operator= (const base_option<char_type>& other) {
        mNames  = other.mNames;
        mDescription.str(other.mDescription.str());
        return *this;
    }
    inline
    base_option<char_type>&
    operator= (base_option<char_type>&& other) {
        mNames  = std::move(other.mNames);
        mDescription = std::move(other.mDescription);
        return *this;
    }

    virtual ~base_option() = default;

    inline
    self_type&
    operator<< (const names_type& names) {
        mNames = names;
        return *this;
    }
    inline
    self_type&
    operator<< (const stringview_type& description) {
        mDescription << description;
        return *this;
    }

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

    inline
    bool
    is_present() const {
        return mIsPresent;
    }
    inline
    bool
    is_missing() const {
        return !mIsPresent;
    }

    virtual
    void
    mark_present() = 0;
    virtual
    void
    mark_missing() = 0;

    virtual
    const std::shared_ptr<concept_type>
    concept() const = 0;
    virtual
    std::shared_ptr<concept_type>
    concept() = 0;

protected:
    names_type mNames;
    stringstream_type mDescription;
    bool mIsPresent = false;
};

}   //-- namespace description --
}   //-- namespace program_options2 --


#endif /* LIB_PROGRAM_OPTIONS2_DESCRIPTION_BASE_OPTION_HPP_ */
