/*
 * logical_yes.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_LOGICAL_YES_HPP_
#define LIB_FN_MATH_LOGICAL_YES_HPP_


#include <bits/stl_function.h>


#ifndef FN_MATH_UNARY_LOGICAL_FUNC_TEMPLATE_SPEC
#define FN_MATH_UNARY_LOGICAL_FUNC_TEMPLATE_SPEC( NAME , TYPE , REALISATION ) \
template<>                                                            \
struct NAME<TYPE> : std::unary_function<TYPE, bool> {                 \
    inline constexpr bool operator() (const TYPE arg0) const {        \
        return REALISATION ;                                          \
    }                                                                 \
};
#endif


namespace fn {
namespace math {

template<typename T>
struct logical_yes;

FN_MATH_UNARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_yes , bool , arg0 )

FN_MATH_UNARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_yes , signed int ,           bool(arg0) )
FN_MATH_UNARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_yes , signed long int ,      bool(arg0) )
FN_MATH_UNARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_yes , signed long long int , bool(arg0) )

FN_MATH_UNARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_yes , unsigned int ,           bool(arg0) )
FN_MATH_UNARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_yes , unsigned long int ,      bool(arg0) )
FN_MATH_UNARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_yes , unsigned long long int , bool(arg0) )

}   //-- namespace math --
}   //-- namespace fn --


#ifdef FN_MATH_UNARY_LOGICAL_FUNC_TEMPLATE_SPEC
#undef FN_MATH_UNARY_LOGICAL_FUNC_TEMPLATE_SPEC
#endif


#endif /* LIB_FN_MATH_LOGICAL_YES_HPP_ */
