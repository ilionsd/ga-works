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

#include "../../domain/any.hpp"
#include "concept.hpp"


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
        mValue(),
        mDefault(),
        mValidator()
    {}
    inline
    basic_model(self_type&& other) :
        mValue(other.mValue),
        mDefault(other.mDefault),
        mValidator(other.mValidator)
    {}

    virtual ~basic_model() override = default;

    inline
    self_type&
    add_default(value_type&& val) {
        mDefault = val;
        return *this;
    }
    inline
    self_type&
    add_validator(validator_type&& f) {
        mValidator = f;
        return *this;
    }

    inline
    const std::optional<value_type>&
    default_value() const {
        return mDefault;
    }
    inline
    std::optional<value_type>&
    default_value() {
        return mDefault;
    }
    inline
    const std::optional<validator_type>&
    validator() const {
        return mValidator;
    }
    inline
    std::optional<validator_type>&
    validator() {
        return mValidator;
    }
    inline virtual
    void
    write(ostream_type& os) const override {
        os << value();
    }
    inline virtual
    void
    read(istream_type& is) override {
        is >> value();
    }

    bool validate() const {
        return mValidator(value());
    }

    inline value_type value() const {
        return mValue;
    }
    inline value_type& value() {
        return mValue;
    }

private:
    std::optional<value_type> mValue;
    std::optional<value_type> mDefault;
    std::optional<validator_type> mValidator;
};

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
        return;
    }
    inline virtual
    void
    read(istream_type& is) override {
        return;
    }
};

}   //-- namespace model --
}   //-- namespace io --


#endif /* LIB_IO_MODEL_MODEL_HPP_ */
