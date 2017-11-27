/*
 * bad_model_access.hpp
 *
 *  Created on: Nov 25, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_MODEL_INVALID_MODEL_VALUE_HPP_
#define LIB_IO_MODEL_INVALID_MODEL_VALUE_HPP_


#include <exception>

namespace io {
namespace model {

class invalid_model_value : public std::exception {
public:
    invalid_model_value() { }
    inline
    virtual
    const char* what() const noexcept override {
        return "invalid model value";
    }
    virtual ~invalid_model_value() noexcept = default;
};

}   //-- namespace model --
}   //-- namespace io --


#endif /* LIB_IO_MODEL_INVALID_MODEL_VALUE_HPP_ */
