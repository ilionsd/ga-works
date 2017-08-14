/*
 * stl_cos.hpp
 *
 *  Created on: Aug 10, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STL_COS_HPP_
#define LIB_UTILITY_STLMATH_STL_COS_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>

#include "function_specialization_helper.hpp"

namespace utility {
namespace stlmath {


template<typename T>
struct cos;

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( cos, float,       std::cos(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( cos, double,      std::cos(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( cos, long double, std::cos(arg0) )


}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STL_COS_HPP_ */
