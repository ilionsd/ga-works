/*
 * logical_and.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_LOGICAL_AND_HPP_
#define LIB_FN_MATH_LOGICAL_AND_HPP_


#include <bits/stl_function.h>


#ifndef FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC
#define FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( NAME , TYPE , REALISATION )            \
template<>                                                                        \
struct NAME<TYPE> : std::binary_function<TYPE, TYPE, bool> {                      \
    inline constexpr bool operator() (const TYPE arg0, const TYPE arg1) const {   \
        return REALISATION ;                                                      \
    }                                                                             \
};
#endif


namespace fn {
namespace math {

template<typename T>
struct logical_and;

FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_and , bool , arg0 && arg1 )

FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_and , signed int ,           bool(arg0) && bool(arg1) )
FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_and , signed long int ,      bool(arg0) && bool(arg1) )
FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_and , signed long long int , bool(arg0) && bool(arg1) )

FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_and , unsigned int ,           bool(arg0) && bool(arg1) )
FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_and , unsigned long int ,      bool(arg0) && bool(arg1) )
FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_and , unsigned long long int , bool(arg0) && bool(arg1) )

}   //-- namespace math --
}   //-- namespace fn --


#ifdef FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC
#undef FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC
#endif


#endif /* LIB_FN_MATH_LOGICAL_AND_HPP_ */
