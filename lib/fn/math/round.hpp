/*
 * round.hpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_ROUND_HPP_
#define LIB_FN_MATH_ROUND_HPP_


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
struct round;

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( round , float ,       std::round(arg0) )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( round , double ,      std::round(arg0) )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( round , long double , std::round(arg0) )

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( round , signed int ,       arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( round , signed long ,      arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( round , signed long long , arg0 )

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( round , unsigned int ,       arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( round , unsigned long ,      arg0 )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( round , unsigned long long , arg0 )

}   //-- namespace math --
}   //-- namespace fn --


#ifdef FN_MATH_UNARY_FUNC_TEMPLATE_SPEC
#undef FN_MATH_UNARY_FUNC_TEMPLATE_SPEC
#endif


#endif /* LIB_FN_MATH_ROUND_HPP_ */
