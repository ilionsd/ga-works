/*
 * log.hpp
 *
 *  Created on: Aug 4, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_LOG_HPP_
#define LIB_FN_MATH_LOG_HPP_


#include <cmath>
#include <cstdlib>
#include <bits/stl_function.h>


#ifndef FN_MATH_BINARY_FUNC_TEMPLATE_SPEC
#define FN_MATH_BINARY_FUNC_TEMPLATE_SPEC( NAME , TYPE , REALISATION )            \
template<>                                                                        \
struct NAME<TYPE> : std::binary_function<TYPE, TYPE, TYPE> {                      \
    inline constexpr TYPE operator() (const TYPE arg0, const TYPE arg1) const {   \
        return REALISATION ;                                                      \
    }                                                                             \
};
#endif


namespace fn {
namespace math {

template<typename T>
struct log;

FN_MATH_BINARY_FUNC_TEMPLATE_SPEC( log , float ,       std::log(arg1) / std::log(arg0) )
FN_MATH_BINARY_FUNC_TEMPLATE_SPEC( log , double ,      std::log(arg1) / std::log(arg0) )
FN_MATH_BINARY_FUNC_TEMPLATE_SPEC( log , long double , std::log(arg1) / std::log(arg0) )

}   //-- namespace math --
}   //-- namespace fn --


#ifdef FN_MATH_BINARY_FUNC_TEMPLATE_SPEC
#undef FN_MATH_BINARY_FUNC_TEMPLATE_SPEC
#endif


#endif /* LIB_FN_MATH_LOG_HPP_ */
