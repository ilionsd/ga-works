/*
 * math_const.hpp
 *
 *  Created on: Aug 10, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_MATH_CONST_HPP_
#define LIB_UTILITY_STLMATH_MATH_CONST_HPP_

#define _USE_MATH_DEFINES
#include <cmath>

namespace utility {
namespace stlmath {

template<typename T>
struct math_const {
#ifdef M_PIl
    static constexpr T pi = T( M_PIl );
#else
    static constexpr T pi = T (M_PI );
#endif

};

}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_MATH_CONST_HPP_ */
