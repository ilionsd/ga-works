/*
 * math.hpp
 *
 *  Created on: Aug 17, 2017
 *      Author: ilion
 */

#ifndef INCLUDE_FN_MATH_HPP_
#define INCLUDE_FN_MATH_HPP_


#include "../../lib/fn/math/abs.hpp"

#include "../../lib/fn/math/floor.hpp"
#include "../../lib/fn/math/round.hpp"
#include "../../lib/fn/math/ceil.hpp"

#include "../../lib/fn/math/sin.hpp"
#include "../../lib/fn/math/cos.hpp"

#include "../../lib/fn/math/square.hpp"
#include "../../lib/fn/math/cube.hpp"
#include "../../lib/fn/math/power.hpp"
#include "../../lib/fn/math/exp.hpp"
#include "../../lib/fn/math/sqrt.hpp"

#include "../../lib/fn/math/log.hpp"
#include "../../lib/fn/math/ln.hpp"
#include "../../lib/fn/math/lg.hpp"
#include "../../lib/fn/math/log2.hpp"


namespace fn {
namespace math {

template<typename T> struct abs;

template<typename T> struct floor;
template<typename T> struct round;
template<typename T> struct ceil;

template<typename T> struct sin;
template<typename T> struct cos;

template<typename T> struct square;
template<typename T> struct cube;
template<typename T> struct power;
template<typename T> struct exp;
template<typename T> struct sqrt;

template<typename T> struct log;
template<typename T> struct ln;
template<typename T> struct lg;
template<typename T> struct log2;

}   //-- namespace math --
}   //-- namespace fn --


#endif /* INCLUDE_FN_MATH_HPP_ */
