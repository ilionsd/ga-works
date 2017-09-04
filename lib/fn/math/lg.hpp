/*
 * lg.hpp
 *
 *  Created on: Aug 4, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_LG_HPP_
#define LIB_FN_MATH_LG_HPP_


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
struct lg;

FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( lg , float ,       std::log10(arg0) )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( lg , double ,      std::log10(arg0) )
FN_MATH_UNARY_FUNC_TEMPLATE_SPEC( lg , long double , std::log10(arg0) )

}   //-- namespace math --
}   //-- namespace fn --


#ifdef FN_MATH_UNARY_FUNC_TEMPLATE_SPEC
#undef FN_MATH_UNARY_FUNC_TEMPLATE_SPEC
#endif


#endif /* LIB_FN_MATH_LG_HPP_ */
