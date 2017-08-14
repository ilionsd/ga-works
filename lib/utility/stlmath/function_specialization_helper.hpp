/*
 * function_specialization_helper.hpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_FUNCTION_SPECIALIZATION_HELPER_HPP_
#define LIB_UTILITY_STLMATH_FUNCTION_SPECIALIZATION_HELPER_HPP_


#define UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( NAME , TYPE , REALISATION ) \
template<>                                                    \
struct NAME<TYPE> : std::unary_function<TYPE, TYPE> {         \
    inline constexpr TYPE operator() (const TYPE arg0) const {   \
        return REALISATION ;                                  \
    }                                                         \
};


#define UTILITY_STLMATH_FUNC_BINARY_TEMPLATE_SPEC( NAME , TYPE , REALISATION ) \
template<>                                                    \
struct NAME<TYPE> : std::binary_function<TYPE, TYPE, TYPE> {         \
    inline constexpr TYPE operator() (const TYPE arg0, const TYPE arg1) const {   \
        return REALISATION ;                                  \
    }                                                         \
};


#endif /* LIB_UTILITY_STLMATH_FUNCTION_SPECIALIZATION_HELPER_HPP_ */
