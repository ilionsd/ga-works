/*
 * ceil.hpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_CEIL_HPP_
#define LIB_FN_MATH_CEIL_HPP_


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
struct ceil;

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( ceil , float ,       std::ceil(arg0) )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( ceil , double ,      std::ceil(arg0) )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( ceil , long double , std::ceil(arg0) )

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( ceil , signed int ,       arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( ceil , signed long ,      arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( ceil , signed long long , arg0 )

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( ceil , unsigned int ,       arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( ceil , unsigned long ,      arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( ceil , unsigned long long , arg0 )

}   //-- namespace math --
}   //-- namespace fn --


#ifdef FN_MATH_UNARY_FUNC_TEMPLATE_SPEC
#undef FN_MATH_UNARY_FUNC_TEMPLATE_SPEC
#endif


#endif /* LIB_FN_MATH_CEIL_HPP_ */
