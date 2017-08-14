/*
 * stl_sqrt.hpp
 *
 *  Created on: Aug 14, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STL_SQRT_HPP_
#define LIB_UTILITY_STLMATH_STL_SQRT_HPP_

#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>

#include "function_specialization_helper.hpp"

namespace utility {
namespace stlmath {

template<typename T>
struct sqrt;

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( sqrt, float,       std::sqrt(arg0); )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( sqrt, double,      std::sqrt(arg0); )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( sqrt, long double, std::sqrt(arg0); )

}
}


#endif /* LIB_UTILITY_STLMATH_STL_SQRT_HPP_ */
