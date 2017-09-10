/*
 * vector_fn.hpp
 *
 *  Created on: Aug 17, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_MATH_V_HPP_
#define LIB_FN_MATH_MATH_V_HPP_


#include <valarray>
#include <bits/stl_function.h>
#include <type_traits>


#include "detail/vector_fn.hpp"


#include "abs.hpp"

#include "floor.hpp"
#include "round.hpp"
#include "ceil.hpp"

#include "sin.hpp"
#include "cos.hpp"

#include "square.hpp"
#include "cube.hpp"
#include "power.hpp"
#include "exp.hpp"
#include "sqrt.hpp"

#include "log.hpp"
#include "ln.hpp"
#include "lg.hpp"
#include "log2.hpp"


#ifndef FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF
#define FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( NAME ) \
template<typename T>                                   \
using NAME##_v = detail::unary_vector_fn<T, NAME>;
#endif

#ifndef FN_MATH_BINARY_VECTOR_FUNC_TEMPLATE_DEF
#define FN_MATH_BINARY_VECTOR_FUNC_TEMPLATE_DEF( NAME ) \
template<typename T>                                    \
using NAME##_v = detail::binary_vector_fn<T, NAME>;
#endif


namespace fn {
namespace math {

FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( abs )

FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( floor )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( round )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( ceil )

FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( sin )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( cos )

FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( square )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( cube )
FN_MATH_BINARY_VECTOR_FUNC_TEMPLATE_DEF( power )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( exp )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( sqrt )

FN_MATH_BINARY_VECTOR_FUNC_TEMPLATE_DEF( log )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( ln )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( lg )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( log2 )

}   //-- namespace math --
}   //-- namespace fn --


#ifdef FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF
#undef FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF
#endif

#ifdef FN_MATH_BINARY_VECTOR_FUNC_TEMPLATE_DEF
#undef FN_MATH_BINARY_VECTOR_FUNC_TEMPLATE_DEF
#endif


#endif /* LIB_FN_MATH_MATH_V_HPP_ */
