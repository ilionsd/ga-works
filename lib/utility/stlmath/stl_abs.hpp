/*
 * abs.hpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STL_ABS_HPP_
#define LIB_UTILITY_STLMATH_STL_ABS_HPP_

#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>

#include "function_specialization_helper.hpp"

namespace utility {
namespace stlmath {

template<typename T>
struct abs;

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , float ,       std::fabs(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , double ,      std::fabs(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , long double , std::fabs(arg0) )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , signed int ,       std::abs(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , signed long ,      std::labs(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , signed long long , std::llabs(arg0) )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , unsigned int ,       arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , unsigned long ,      arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , unsigned long long , arg0 )

}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STL_ABS_HPP_ */
