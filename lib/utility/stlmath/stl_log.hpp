/*
 * stllog.hpp
 *
 *  Created on: Aug 4, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STL_LOG_HPP_
#define LIB_UTILITY_STLMATH_STL_LOG_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>

#include "function_specialization_helper.hpp"

namespace utility {
namespace stlmath {

template<typename T>
struct log;

UTILITY_STLMATH_FUNC_BINARY_TEMPLATE_SPEC( log , float ,       std::log(b) / std::log(a) )
UTILITY_STLMATH_FUNC_BINARY_TEMPLATE_SPEC( log , double ,      std::log(b) / std::log(a) )
UTILITY_STLMATH_FUNC_BINARY_TEMPLATE_SPEC( log , long double , std::log(b) / std::log(a) )

}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STL_LOG_HPP_ */
