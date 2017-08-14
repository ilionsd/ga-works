/*
 * stlceil.hpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STL_CEIL_HPP_
#define LIB_UTILITY_STLMATH_STL_CEIL_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>


#include "function_specialization_helper.hpp"


namespace utility {
namespace stlmath {

template<typename T>
struct ceil;

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , float ,       std::ceil(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , double ,      std::ceil(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , long double , std::ceil(arg0) )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , signed int ,       arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , signed long ,      arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , signed long long , arg0 )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , unsigned int ,       arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , unsigned long ,      arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , unsigned long long , arg0 )

}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STL_CEIL_HPP_ */
