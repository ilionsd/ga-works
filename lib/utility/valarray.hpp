/*
 * valarray.hpp
 *
 *  Created on: Jul 21, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_VALARRAY_HPP_
#define LIB_UTILITY_VALARRAY_HPP_

#include <cstddef>
#include <valarray>
#include <array>
#include <tuple>
#include <algorithm>
#include <type_traits>

#include "stlmath.hpp"

namespace utility {
namespace valarray {

template<typename... Ts>
constexpr auto make(const Ts... args) -> std::valarray<std::common_type_t<Ts...>> {
    return { args... };
};

template<typename T, typename... Ts>
constexpr auto make_of(const Ts... args) -> std::valarray<T> {
    return { args... };
};

template<typename T, std::size_t N>
constexpr auto from(const std::array<T, N>& arr) -> std::valarray<T> {
    std::valarray<T> valarr ( N );
    for (std::size_t k = 0; k < N; ++k)
        valarr[k] = arr[k];
    return valarr;
}


template<typename F, typename T>
constexpr auto map(F f, const std::valarray<T>& array) {
    typedef decltype(f(array[0])) ret_type;
    std::valarray<ret_type> ret ( array.size() );
    for (std::size_t k = 0; k < array.size(); ++k)
        ret[k] = f(array[k]);
    return ret;
}
template<typename F, typename Expr>
constexpr auto map(F f, const Expr& expr) {
    typedef typename decltype(expr)::value_type value_type;
    typedef decltype( f( value_type() ) ) ret_type;

    std::valarray<ret_type> ret ( expr.size() );
    for (std::size_t k = 0; k < expr.size(); ++k)
        ret[k] = f(expr[k]);
    return ret;
}


template<typename F, typename Expr>
constexpr auto reduce(F f, const Expr& expr) {
    typedef typename Expr::value_type value_type;
    value_type acc = expr[0];
    for (std::size_t k = 1; k < expr.size(); ++k)
        acc = f(acc, expr[k]);
    return acc;
}
template< typename F, typename T>
constexpr auto reduce(F f, const std::valarray<T>& array) -> T {
    T acc = array[0];
    for (std::size_t k = 1; k < array.size(); ++k)
        acc = f(acc, array[k]);
    return acc;
};

template<typename Expr>
constexpr auto round(const Expr& expr) {
    typedef typename Expr::value_type value_type;
    typedef std::_UnClos<::utility::stlmath::round<value_type>, std::_Expr, typename Expr::value_type> closure;
    return std::_Expr<closure, value_type>(expr());
}
template<typename T>
constexpr auto round(const std::valarray<T>& array) {
    typedef T value_type;
    typedef std::_UnClos<::utility::stlmath::round<value_type>, std::_ValArray, value_type> closure;
    return std::_Expr<closure, value_type>(closure(array));
}


template<typename T1, typename Expr>
constexpr auto convert_to(const Expr& expr) -> std::valarray<T1> {
    std::valarray<T1> ret ( expr.size() );
    for (std::size_t k = 0; k < expr.size(); ++k)
        ret[k] = T1 ( expr[k] );
    return ret;
}
template<typename T1, typename T2>
constexpr auto convert_to(const std::valarray<T2>& array) -> std::valarray<T1> {
    std::valarray<T1> ret ( array.size() );
    for (std::size_t k = 0; k < array.size(); ++k)
        ret[k] = T1 ( array[k] );
    return ret;
}


};  //-- namespace valarray --
};  //-- namespace utility --


#endif /* LIB_UTILITY_VALARRAY_HPP_ */
