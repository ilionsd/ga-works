/*
 * stl_sin.hpp
 *
 *  Created on: Aug 10, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STL_SIN_HPP_
#define LIB_UTILITY_STLMATH_STL_SIN_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>

#include "function_specialization_helper.hpp"

namespace utility {
namespace stlmath {


template<typename T>
struct sin;

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( sin, float,       std::sin(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( sin, double,      std::sin(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( sin, long double, std::sin(arg0) )


}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STL_SIN_HPP_ */
