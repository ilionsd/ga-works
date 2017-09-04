/*
 * sqrt.hpp
 *
 *  Created on: Aug 14, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_SQRT_HPP_
#define LIB_FN_MATH_SQRT_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>


#ifndef FN_MATH_UNARY_FUNC_TEMPLATE_SPEC
#define FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( NAME , TYPE , REALISATION ) \
template<>                                                            \
struct NAME<TYPE> : std::unary_function<TYPE, TYPE> {                 \
    inline constexpr TYPE operator() (const TYPE arg0) const {        \
        return REALISATION ;                                          \
    }                                                                 \
};
#endif


namespace fn {
namespace math {

template<typename T>
struct sqrt;

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( sqrt, float,       std::sqrt(arg0) )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( sqrt, double,      std::sqrt(arg0) )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( sqrt, long double, std::sqrt(arg0) )

}   //-- namespace math --
}   //-- namespace fn --


#ifdef FN_MATH_UNARY_FUNC_TEMPLATE_SPEC
#undef FN_MATH_UNARY_FUNC_TEMPLATE_SPEC
#endif


#endif /* LIB_FN_MATH_SQRT_HPP_ */
