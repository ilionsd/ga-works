/*
 * math.hpp
 *
 *  Created on: Jul 27, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_STLMATH_HPP_
#define LIB_UTILITY_STLMATH_HPP_


#include "stlmath/stl_abs.hpp"
#include "stlmath/stl_ceil.hpp"
#include "stlmath/stl_floor.hpp"
#include "stlmath/stl_ln.hpp"
#include "stlmath/stl_lg.hpp"
#include "stlmath/stl_log.hpp"
#include "stlmath/stl_log2.hpp"
#include "stlmath/stl_round.hpp"


namespace utility {
namespace stlmath {


template<typename T> struct abs;
template<typename T> struct round;
template<typename T> struct floor;
template<typename T> struct ceil;
template<typename T> struct ln;
template<typename T> struct lg;
template<typename T> struct log;
template<typename T> struct log2;


}   //-- namespace stlmath --
}   //-- namespace utility --


#endif /* LIB_UTILITY_STLMATH_HPP_ */
