/*
 * function.hpp
 *
 *  Created on: Jul 25, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_FUNCTION_HPP_
#define LIB_UTILITY_FUNCTION_HPP_

#include <bits/stl_function.h>

namespace utility {
namespace function {

template<typename T>
struct bit_shift_left : public std::binary_function<T, T, T> {
    inline constexpr T operator() (const T a, const T b) const {
        return a << b;
    };
};

template<typename T>
struct bit_shift_right : public std::binary_function<T, T, T> {
    inline constexpr T operator() (const T a, const T b) const {
        return a >> b;
    };
};

};  //-- namespace function --
};  //-- namespace utility --


#endif /* LIB_UTILITY_FUNCTION_HPP_ */
