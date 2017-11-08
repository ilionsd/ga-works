/*
 * simple_option.hpp
 *
 *  Created on: Oct 13, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_SIMPLE_HPP_
#define LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_SIMPLE_HPP_


#include <string>

#include "../../../io/names/complex_names.hpp"
#include "base_option.hpp"


namespace program_options2 {
namespace description {
namespace option {
namespace detail2 {

template<typename CharT>
class basic_simple :
        public basic_base_option<CharT> {
public:
    typedef CharT char_type;
    typedef basic_base_option<char_type> base_type;
    typedef ::io::names::basic_complex_names<char_type> names_type;

    inline
    basic_simple() :
        base_type()
    {}
    inline
    basic_simple(const names_type& name) :
        base_type(name)
    {}
    inline
    basic_simple(const names_type& name, const std::basic_string<char_type>& description) :
        base_type(name, description)
    {}
    inline
    basic_simple(const basic_simple<char_type>& other) :
        base_type(other)
    {}
    inline
    basic_simple(basic_simple<char_type>&& other) :
        base_type(other)
    {}
    inline
    basic_simple<char_type>&
    operator= (const basic_simple<char_type>& other) {
        base_type::operator =(other);
        mPresent = other.mPresent;
        return *this;
    }
    inline
    basic_simple<char_type>&
    operator= (basic_simple<char_type>&& other) {
        base_type::operator =(other);
        mPresent = std::move(other.mPresent);
        return *this;
    }

    virtual ~basic_simple() override = default;

    inline virtual
    operator bool() const override {
        return present();
    }

    inline
    bool
    present() const {
        return mPresent;
    }
    inline
    bool&
    present() {
        return mPresent;
    }

private:
    bool mPresent = false;
};

}   //-- detail2 --
}   //-- namespace option --
}   //-- namespace description --
}   //-- namespace program_options2 --


#endif /* LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_SIMPLE_HPP_ */
