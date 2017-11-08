/*
 * base_option.hpp
 *
 *  Created on: Oct 15, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_BASE_VALUED_HPP_
#define LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_BASE_VALUED_HPP_


#include <memory>
#include <string>
#include <sstream>

#include "../../../io/names/complex_names.hpp"
#include "../../../io/model/concept.hpp"
#include "base_option.hpp"


namespace program_options2 {
namespace description {
namespace option {
namespace detail2 {

template<typename CharT>
class basic_base_valued :
        public basic_base_option<CharT> {
public:
    typedef CharT char_type;
    typedef basic_base_option<char_type> base_type;
    typedef ::io::model::basic_concept<char_type> concept_type;

    using base_type::base_type;
    using base_type::operator =;

    virtual ~basic_base_valued() override = default;

    virtual
    const std::shared_ptr<concept_type>
    concept() const = 0;
    virtual
    std::shared_ptr<concept_type>
    concept() = 0;
};

}   //-- namespace detail2 --
}   //-- namespace option --
}   //-- namespace description --
}   //-- namespace program_options2 --


#endif /* LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_BASE_VALUED_HPP_ */
