/*
 * stl_log2.hpp
 *
 *  Created on: Aug 4, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STL_LOG2_HPP_
#define LIB_UTILITY_STLMATH_STL_LOG2_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>

#include "function_specialization_helper.hpp"

namespace utility {
namespace stlmath {

template<typename T>
struct log2;

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( log2 , float ,       std::log2(x) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( log2 , double ,      std::log2(x) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( log2 , long double , std::log2(x) )

}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STL_LOG2_HPP_ */
