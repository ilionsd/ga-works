/*
 * typed.hpp
 *
 *  Created on: Oct 13, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_VALUED_HPP_
#define LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_VALUED_HPP_


#include <memory>
#include <string>

#include "../../../io/model/concept.hpp"
#include "../../../io/model/model.hpp"
#include "base_valued.hpp"


namespace program_options2 {
namespace description {
namespace option {
namespace detail2 {

template<typename CharT, typename T>
class basic_valued :
        public basic_base_valued<CharT> {
public:
    typedef T value_type;
    typedef CharT char_type;
    typedef basic_base_valued<char_type> base_type;
    typedef typename base_type::stringstream_type stringstream_type;
    typedef typename base_type::names_type names_type;
    typedef ::io::model::basic_concept<char_type> concept_type;
    typedef ::io::model::basic_model<char_type, value_type> model_type;

    inline
    basic_valued() :
        base_type(),
        mModelPtr()
    {}
    inline
    basic_valued(const names_type& names) :
        base_type(names),
        mModelPtr()
    {}
    inline
    basic_valued(const names_type& names, const std::basic_string<char_type>& description) :
        base_type(names, description),
        mModelPtr()
    {}
    inline
    basic_valued(const names_type& names, const std::basic_string<char_type>& description, const std::shared_ptr<model_type>& modelPtr) :
        base_type(names, description),
        mModelPtr(modelPtr)
    {}
    inline
    basic_valued(const basic_valued<char_type, value_type>& other) :
        base_type(other),
        mModelPtr(other.mModelPtr)
    {}
    inline
    basic_valued(basic_valued<char_type, value_type>&& other) :
        base_type(other),
        mModelPtr(std::move(other.mModelPtr))
    {}
    inline
    basic_valued<char_type, value_type>&
    operator= (const basic_valued<char_type, value_type>& other) {
        base_type::operator =(other);
        mModelPtr = other.mModelPtr;
        return *this;
    }
    inline
    basic_valued<char_type, value_type>&
    operator= (basic_valued<char_type, value_type>&& other) {
        base_type::operator =(other);
        mModelPtr = std::move(other.mModelPtr);
        return *this;
    }

    virtual ~basic_valued() override = default;

    inline virtual
    operator bool() const override {
        return bool(mModelPtr);
    }

    inline
    const std::shared_ptr<model_type>&
    model() const {
        return mModelPtr;
    }
    inline
    std::shared_ptr<model_type>&
    model() {
        return mModelPtr;
    }

    inline virtual
    const std::shared_ptr<concept_type>
    concept() const override {
        return std::static_pointer_cast<concept_type>(mModelPtr);
    }
    inline virtual
    std::shared_ptr<concept_type>
    concept() override {
        return std::static_pointer_cast<concept_type>(mModelPtr);
    }

private:
    std::shared_ptr<model_type> mModelPtr;
};

}   //-- namespace detail2 --
}   //-- namespace option --
}   //-- namespace description --
}   //-- namespace program_options2 --


#endif /* LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_VALUED_HPP_ */
