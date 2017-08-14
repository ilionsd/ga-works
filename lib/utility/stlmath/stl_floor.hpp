/*
 * stlfloor.hpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STL_FLOOR_HPP_
#define LIB_UTILITY_STLMATH_STL_FLOOR_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>


#include "function_specialization_helper.hpp"


namespace utility {
namespace stlmath {

template<typename T>
struct floor;

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( floor , float ,       std::floor(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( floor , double ,      std::floor(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( floor , long double , std::floor(arg0) )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( floor , signed int ,       arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( floor , signed long ,      arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( floor , signed long long , arg0 )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( floor , unsigned int ,       arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( floor , unsigned long ,      arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( floor , unsigned long long , arg0 )

}   //-- namespace stlmath --
}   //-- namespace utility --

#endif /* LIB_UTILITY_STLMATH_STL_FLOOR_HPP_ */
