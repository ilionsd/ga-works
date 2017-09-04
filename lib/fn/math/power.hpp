/*
 * power.hpp
 *
 *  Created on: Aug 10, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_POWER_HPP_
#define LIB_FN_MATH_POWER_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>


#ifndef FN_MATH_BINARY_FUNC_TEMPLATE_SPEC
#define FN_MATH_BINARY_FUNC_TEMPLATE_SPEC( NAME , TYPE , REALISATION )            \
template<>                                                                        \
struct NAME<TYPE> : std::binary_function<TYPE, TYPE, TYPE> {                      \
    inline constexpr TYPE operator() (const TYPE arg0, const TYPE arg1) const {   \
        return REALISATION ;                                                      \
    }                                                                             \
};
#endif


namespace fn {
namespace math {

template<typename T>
struct power;

FN_MATH_BINARY_FUNC_TEMPLATE_SPEC( power, float,       std::pow(arg0, arg1) )
FN_MATH_BINARY_FUNC_TEMPLATE_SPEC( power, double,      std::pow(arg0, arg1) )
FN_MATH_BINARY_FUNC_TEMPLATE_SPEC( power, long double, std::pow(arg0, arg1) )

}   //-- namespace math --
}   //-- namespace fn --


#ifdef FN_MATH_BINARY_FUNC_TEMPLATE_SPEC
#undef FN_MATH_BINARY_FUNC_TEMPLATE_SPEC
#endif


#endif /* LIB_FN_MATH_POWER_HPP_ */
