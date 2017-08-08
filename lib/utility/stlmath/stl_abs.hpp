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

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , float ,       std::fabs(x) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , double ,      std::fabs(x) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , long double , std::fabs(x) )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , signed int ,       std::abs(x) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , signed long ,      std::labs(x) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , signed long long , std::llabs(x) )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , unsigned int ,       x )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , unsigned long ,      x )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( abs , unsigned long long , x )

}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STL_ABS_HPP_ */
