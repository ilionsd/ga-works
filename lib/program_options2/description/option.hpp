/*
 * option.hpp
 *
 *  Created on: Nov 3, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_HPP_
#define LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_HPP_


#include <memory>
#include <string>
#include <sstream>

#include "../../io/names/complex_names.hpp"
#include "../../io/model/concept.hpp"
#include "../../io/model/model.hpp"
#include "base_option.hpp"


namespace program_options2 {
namespace description {

template<typename CharT, typename T = bool>
class basic_option : public base_option<CharT> {
public:
    typedef CharT char_type;
    typedef T value_type;
    typedef basic_option<char_type, value_type> self_type;
    typedef base_option<char_type> base_type;
    typedef typename base_type::stringview_type stringview_type;
    typedef typename base_type::stringstream_type stringstream_type;
    typedef typename base_type::names_type names_type;
    typedef typename base_type::concept_type concept_type;
    typedef ::io::model::basic_model<char_type, value_type> model_type;

    inline
    basic_option() :
        base_type(),
        mModelPtr()
    {}
    inline
    basic_option(const names_type& names) :
        base_type(names),
        mModelPtr()
    {}
    inline
    basic_option(const names_type& names, const stringview_type& description) :
        base_type(names, description),
        mModelPtr()
    {}
    inline
    basic_option(const names_type& names, const stringview_type& description, const std::shared_ptr<model_type>& modelPtr) :
        base_type(names, description),
        mModelPtr(modelPtr)
    {}
    inline
    basic_option(const basic_option<char_type, value_type>& other) :
        base_type(other),
        mModelPtr(other.mModelPtr)
    {}
    inline
    basic_option(basic_option<char_type, value_type>&& other) :
        base_type(other),
        mModelPtr(std::move(other.mModelPtr))
    {}
    inline
    basic_option<char_type, value_type>&
    operator= (const basic_option<char_type, value_type>& other) {
        base_type::operator =(other);
        mModelPtr = other.mModelPtr;
        return *this;
    }
    inline
    basic_option<char_type, value_type>&
    operator= (basic_option<char_type, value_type>&& other) {
        base_type::operator =(other);
        mModelPtr = std::move(other.mModelPtr);
        return *this;
    }

    virtual ~basic_option() override = default;

    inline virtual
    operator bool() const override {
        return bool(mModelPtr);
    }

    inline virtual
    void
    mark_present() override {
        this->mIsPresent = true;
    }
    inline virtual
    void
    mark_missing() override {
        this->mIsPresent = false;
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

template<typename CharT>
class basic_option<CharT, bool> : public base_option<CharT> {
public:
    typedef CharT char_type;
    typedef bool value_type;
    typedef base_option<char_type> base_type;
    typedef typename base_type::stringview_type stringview_type;
    typedef typename base_type::stringstream_type stringstream_type;
    typedef typename base_type::names_type names_type;
    typedef typename base_type::concept_type concept_type;
    typedef ::io::model::basic_model<char_type, value_type> model_type;

    inline
    basic_option() :
        base_type(),
        mModelPtr(std::make_shared<model_type>())
    {}
    inline
    basic_option(const names_type& names) :
        base_type(names),
        mModelPtr(std::make_shared<model_type>())
    {}
    inline
    basic_option(const names_type& names, const stringview_type& description) :
        base_type(names, description),
        mModelPtr(std::make_shared<model_type>())
    {}
    inline
    basic_option(const basic_option<char_type, void>& other) :
        base_type(other),
        mModelPtr(other.mModelPtr)
    {}
    inline
    basic_option(basic_option<char_type, void>&& other) :
        base_type(other),
        mModelPtr(std::move(other.mModelPtr))
    {}
    inline
    basic_option<char_type, void>&
    operator= (const basic_option<char_type, void>& other) {
        base_type::operator =(other);
        mModelPtr = other.mModelPtr;
        return *this;
    }
    inline
    basic_option<char_type, void>&
    operator= (basic_option<char_type, void>&& other) {
        base_type::operator =(other);
        mModelPtr = std::move(other.mModelPtr);
        return *this;
    }

    virtual ~basic_option() override = default;

    inline virtual
    operator bool() const override {
        return bool(mModelPtr);
    }

    inline virtual
    void
    mark_present() override {
        this->mIsPresent = true;
        reset_model();
    }
    inline virtual
    void
    mark_missing() override {
        this->mIsPresent = false;
        reset_model();
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

protected:
    inline
    void
    reset_model() {
        model()->ovalue() = this->mIsPresent;
    }

private:
    std::shared_ptr<model_type> mModelPtr;
};

}   //-- namespace description --
}   //-- namespace program_options2 --


#endif /* LIB_PROGRAM_OPTIONS2_DESCRIPTION_OPTION_HPP_ */
