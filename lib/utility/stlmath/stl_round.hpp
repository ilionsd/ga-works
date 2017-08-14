/*
 * round.hpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STL_ROUND_HPP_
#define LIB_UTILITY_STLMATH_STL_ROUND_HPP_

#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>


#include "function_specialization_helper.hpp"


namespace utility {
namespace stlmath {

template<typename T>
struct round;

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , float ,       std::round(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , double ,      std::round(arg0) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , long double , std::round(arg0) )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , signed int ,       arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , signed long ,      arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , signed long long , arg0 )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , unsigned int ,       arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , unsigned long ,      arg0 )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , unsigned long long , arg0 )

}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STL_ROUND_HPP_ */
