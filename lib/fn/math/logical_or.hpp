/*
 * logical_or.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_LOGICAL_OR_HPP_
#define LIB_FN_MATH_LOGICAL_OR_HPP_


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
struct logical_or;

FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_or , bool , arg0 || arg1 )

FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_or , signed int ,           bool(arg0) || bool(arg1) )
FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_or , signed long int ,      bool(arg0) || bool(arg1) )
FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_or , signed long long int , bool(arg0) || bool(arg1) )

FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_or , unsigned int ,           bool(arg0) || bool(arg1) )
FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_or , unsigned long int ,      bool(arg0) || bool(arg1) )
FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC( logical_or , unsigned long long int , bool(arg0) || bool(arg1) )

}   //-- namespace math --
}   //-- namespace fn --


#ifdef FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC
#undef FN_MATH_BINARY_LOGICAL_FUNC_TEMPLATE_SPEC
#endif


#endif /* LIB_FN_MATH_LOGICAL_OR_HPP_ */
