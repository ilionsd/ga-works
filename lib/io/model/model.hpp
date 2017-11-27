/*
 * model.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_MODEL_MODEL_HPP_
#define LIB_IO_MODEL_MODEL_HPP_


#include <functional>
#include <istream>
#include <ostream>
#include <optional>

#include "concept.hpp"
#include "invalid_model_value.hpp"


namespace io {
namespace model {

template<typename CharT, typename T>
class basic_model final : public basic_concept<CharT> {
public:
    typedef CharT char_type;
    typedef T value_type;
    typedef basic_model<char_type, value_type> self_type;
    typedef basic_concept<char_type> base_type;
    typedef typename base_type::istream_type istream_type;
    typedef typename base_type::ostream_type ostream_type;
    typedef std::function<bool(value_type)> validator_type;

    inline
    basic_model() :
        mOptionalValue(),
        mOptionalDefault(),
        mOptionalValidator()
    {}
    inline
    basic_model(const self_type& other) :
        mOptionalValue(other.mOptionalValue),
        mOptionalDefault(other.mOptionalDefault),
        mOptionalValidator(other.mOptionalValidator)
    {}

    virtual ~basic_model() override = default;

    inline
    self_type&
    add_default(const value_type& val) {
        mOptionalDefault = val;
        return *this;
    }
    inline
    self_type&
    add_validator(const validator_type& f) {
        mOptionalValidator = f;
        return *this;
    }

    inline virtual
    void
    write(ostream_type& os) const override {
        os << value();
    }
    inline virtual
    void
    read(istream_type& is) override {
        value_type val;
        is >> val;
        mOptionalValue = val;
    }

    bool validate() const {
        return ovalue().has_value() && (!mOptionalValidator.has_value() || mOptionalValidator.value()(ovalue().value()));
    }

    inline
    const std::optional<value_type>&
    odefault() const {
        return mOptionalDefault;
    }
    inline
    std::optional<value_type>&
    odefault() {
        return mOptionalDefault;
    }

    inline
    const std::optional<value_type>&
    ovalue() const {
        return mOptionalValue;
    }
    inline
    std::optional<value_type>&
    ovalue() {
        return mOptionalValue;
    }

    inline
    value_type
    value() const {
        if (validate())
            return ovalue().value();
        else if (odefault())
            return odefault().value();
        throw invalid_model_value();
    }
    inline
    value_type
    value_or(const value_type& other) const {
        if (validate())
            return ovalue().value();
        else if (odefault())
            return odefault().value();
        else
            return other;
    }

    virtual
    bool
    has_value() const override {
        return validate() || mOptionalDefault.has_value();
    }

protected:
    auto as_tuple() {
        return std::tie(mOptionalValue, mOptionalDefault, mOptionalValidator);
    }

private:
    std::optional<value_type> mOptionalValue;
    std::optional<value_type> mOptionalDefault;
    std::optional<validator_type> mOptionalValidator;
};

/*
template<typename CharT>
class basic_model<CharT, void> final : public basic_concept<CharT> {
public:
    typedef CharT char_type;
    typedef void value_type;
    typedef basic_model<char_type, value_type> self_type;
    typedef basic_concept<char_type> base_type;
    typedef typename base_type::istream_type istream_type;
    typedef typename base_type::ostream_type ostream_type;

    virtual ~basic_model() override = default;

    inline virtual
    void
    write(ostream_type& os) const override {
        os << mHasValue;
    }
    inline virtual
    void
    read(istream_type& is) override {
        mHasValue = true;
    }



    inline virtual
    bool
    has_value() const override {
        return mHasValue;
    }

private:
    bool mHasValue = false;
};
*/

}   //-- namespace model --
}   //-- namespace io --


#endif /* LIB_IO_MODEL_MODEL_HPP_ */
