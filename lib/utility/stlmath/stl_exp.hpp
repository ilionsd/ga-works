/*
 * stl_exp.hpp
 *
 *  Created on: Aug 10, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STL_EXP_HPP_
#define LIB_UTILITY_STLMATH_STL_EXP_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>

#include "function_specialization_helper.hpp"

namespace utility {
namespace stlmath {

template<typename T>
struct exp;

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( exp, float,       std::exp(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( exp, double,      std::exp(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( exp, long double, std::exp(arg0) )


}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STL_EXP_HPP_ */
