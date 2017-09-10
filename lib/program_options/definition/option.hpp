/*
 * option.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS_DEFINITION_OPTION_HPP_
#define LIB_PROGRAM_OPTIONS_DEFINITION_OPTION_HPP_


#include <memory>
#include <string>
#include <sstream>

#include "../../io/model/concept.hpp"
#include "../../io/names/complex_name.hpp"


namespace program_options {
namespace definition {

template<typename CharT>
class basic_option {
public:
    typedef CharT char_type;
    typedef ::io::model::concept<char_type> concept_type;
    typedef ::io::names::basic_complex_name<char_type> name_type;
    typedef std::basic_string<char_type> string_type;
    typedef std::basic_stringstream<char_type> stringstream_type;
    typedef std::basic_ostringstream<char_type> ostringstream_type;

    inline
    std::unique_ptr<concept_type>&
    model() {
        return mModel;
    }
    inline
    const std::unique_ptr<concept_type>&
    model() const {
        return mModel;
    }

    inline
    const ostringstream_type
    description() const {
        return mDescription;
    }
    inline
    ostringstream_type&
    description() {
        return mDescription;
    }

private:
    name_type mName;
    std::unique_ptr<concept_type> mModel;
    ostringstream_type mDescription;
};

using option  = basic_option<char>;
using woption = basic_option<wchar_t>;

}   //-- namespace definition --
}   //-- namespace program_options --


#endif /* LIB_PROGRAM_OPTIONS_DEFINITION_OPTION_HPP_ */
