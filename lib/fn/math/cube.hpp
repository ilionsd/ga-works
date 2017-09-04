/*
 * cube.hpp
 *
 *  Created on: Aug 17, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_CUBE_HPP_
#define LIB_FN_MATH_CUBE_HPP_


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
struct cube;

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( cube, signed int,       arg0 * arg0 * arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( cube, signed long,      arg0 * arg0 * arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( cube, signed long long, arg0 * arg0 * arg0 )

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( cube, unsigned int,       arg0 * arg0 * arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( cube, unsigned long,      arg0 * arg0 * arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( cube, unsigned long long, arg0 * arg0 * arg0 )

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( cube, float,       arg0 * arg0 * arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( cube, double,      arg0 * arg0 * arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( cube, long double, arg0 * arg0 * arg0 )

}   //-- namespace math --
}   //-- namespace fn --


#ifdef FN_MATH_UNARY_FUNC_TEMPLATE_SPEC
#undef FN_MATH_UNARY_FUNC_TEMPLATE_SPEC
#endif


#endif /* LIB_FN_MATH_CUBE_HPP_ */
