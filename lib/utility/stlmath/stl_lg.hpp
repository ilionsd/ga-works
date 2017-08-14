/*
 * stllg.hpp
 *
 *  Created on: Aug 4, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STL_LG_HPP_
#define LIB_UTILITY_STLMATH_STL_LG_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>

#include "function_specialization_helper.hpp"

namespace utility {
namespace stlmath {

template<typename T>
struct lg;

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( lg , float ,       std::log10(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( lg , double ,      std::log10(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( lg , long double , std::log10(arg0) )

}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STL_LG_HPP_ */
