/*
 * model.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_MODEL_MODEL_HPP_
#define LIB_IO_MODEL_MODEL_HPP_


#include <istream>
#include <ostream>

#include "../../domain/any.hpp"
#include "concept.hpp"


namespace io {
namespace model {

template<typename T, class F = ::domain::any<T>, typename CharT>
class model final : public concept<CharT> {
public:
    typedef T value_type;
    typedef F validator_type;

    inline model(validator_type validator) :
            mValidator(validator)
    {}

    virtual ~model() override = default;

    virtual void write(ostream_type& os) const override {
        os << value();
    }
    virtual void  read(istream_type& is) override {
        is >> value();
    }
    virtual bool validate() const override {
        return mValidator(value());
    }

    inline value_type value() const {
        return mValue;
    }
    inline value_type& value() {
        return mValue;
    }

private:
    value_type mValue;
    validator_type mValidator;
};

}   //-- namespace model --
}   //-- namespace io --


#endif /* LIB_IO_MODEL_MODEL_HPP_ */
