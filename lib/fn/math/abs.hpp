/*
 * abs.hpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_ABS_HPP_
#define LIB_FN_MATH_ABS_HPP_


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
struct abs;

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( abs , float ,       std::fabs(arg0) )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( abs , double ,      std::fabs(arg0) )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( abs , long double , std::fabs(arg0) )

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( abs , signed int ,       std::abs(arg0)   )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( abs , signed long ,      std::labs(arg0)  )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( abs , signed long long , std::llabs(arg0) )

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( abs , unsigned int ,       arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( abs , unsigned long ,      arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( abs , unsigned long long , arg0 )

}   //-- namespace math --
}   //-- namespace fn --


#ifdef FN_MATH_UNARY_FUNC_TEMPLATE_SPEC
#undef FN_MATH_UNARY_FUNC_TEMPLATE_SPEC
#endif


#endif /* LIB_FN_MATH_ABS_HPP_ */
