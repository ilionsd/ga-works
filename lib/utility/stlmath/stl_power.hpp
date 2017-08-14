/*
 * stl_power.hpp
 *
 *  Created on: Aug 10, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STL_POWER_HPP_
#define LIB_UTILITY_STLMATH_STL_POWER_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>

#include "function_specialization_helper.hpp"

namespace utility {
namespace stlmath {

template<typename T>
struct power;

UTILITY_STLMATH_FUNC_BINARY_TEMPLATE_SPEC( power, float,       std::pow(arg0, arg1) )
UTILITY_STLMATH_FUNC_BINARY_TEMPLATE_SPEC( power, double,      std::pow(arg0, arg1) )
UTILITY_STLMATH_FUNC_BINARY_TEMPLATE_SPEC( power, long double, std::pow(arg0, arg1) )



}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STL_POWER_HPP_ */
