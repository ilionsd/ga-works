/*
 * stlceil.hpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STLCEIL_HPP_
#define LIB_UTILITY_STLMATH_STLCEIL_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>


#include "function_specialization_helper.hpp"


namespace utility {
namespace stlmath {

template<typename T>
struct ceil;

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , float ,       std::ceil(x) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , double ,      std::ceil(x) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , long double , std::ceil(x) )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , signed int ,       x )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , signed long ,      x )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , signed long long , x )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , unsigned int ,       x )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , unsigned long ,      x )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ceil , unsigned long long , x )

}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STLCEIL_HPP_ */
