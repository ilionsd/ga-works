/*
 * round.hpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_STLROUND_HPP_
#define LIB_UTILITY_STLMATH_STLROUND_HPP_

#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>


#include "function_specialization_helper.hpp"


namespace utility {
namespace stlmath {

template<typename T>
struct round;

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , float ,       std::round(x) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , double ,      std::round(x) )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , long double , std::round(x) )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , signed int ,       x )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , signed long ,      x )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , signed long long , x )

UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , unsigned int ,       x )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , unsigned long ,      x )
UTILITY_STLMATH_FUNC_UNARY_TEMPLATE_SPEC( round , unsigned long long , x )

}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_STLROUND_HPP_ */
