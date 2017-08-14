/*
 * stllog.hpp
 *
 *  Created on: Aug 4, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STL_LN_HPP_
#define LIB_UTILITY_STLMATH_STL_LN_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>

#include "function_specialization_helper.hpp"

namespace utility {
namespace stlmath {

template<typename T>
struct ln;

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ln , float ,       std::log(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ln , double ,      std::log(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( ln , long double , std::log(arg0) )

}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STL_LN_HPP_ */
