/*
 * concept.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_MODEL_CONCEPT_HPP_
#define LIB_IO_MODEL_CONCEPT_HPP_


#include <istream>
#include <ostream>
#include <memory>
#include <type_traits>

#include "../../type_traits/is_base_of_any.hpp"


namespace io {
namespace model {

template<typename CharT>
struct basic_concept {
    typedef CharT char_type;
    typedef std::basic_istream<char_type> istream_type;
    typedef std::basic_ostream<char_type> ostream_type;

    virtual ~basic_concept() = default;

    virtual void write(ostream_type& os) const = 0;
    virtual void read (istream_type& is) = 0;

    inline
    operator bool() {
        return has_value();
    }

    virtual bool has_value() const = 0;
};

template<typename CharT>
std::basic_istream<CharT>&
operator>> (std::basic_istream<CharT>& is, const basic_concept<CharT>& c) {
    c.read(is);
    return is;
}

template<typename CharT>
std::basic_ostream<CharT>&
operator<< (std::basic_ostream<CharT>& os, const basic_concept<CharT>& c) {
    c.write(os);
    return os;
}

}   //-- namespace model --
}   //-- namespace io --


#endif /* LIB_IO_MODEL_CONCEPT_HPP_ */
