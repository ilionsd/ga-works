/*
 * array.hpp
 *
 *  Created on: Jul 21, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_ARRAY_HPP_
#define LIB_UTILITY_ARRAY_HPP_


#include <cstddef>
#include <array>
#include <type_traits>


namespace utility {
namespace array {


template<typename... Ts>
constexpr auto make(const Ts... args) -> std::array<std::common_type_t<Ts...>, sizeof...(Ts)> {
    return { args... };
};

template<typename T, typename... Ts>
constexpr auto make_of(const Ts... args) -> std::array<T, sizeof...(Ts)> {
    return { T(args)... };
};

template<typename T, std::size_t N>
inline constexpr std::array<T, N> fill(const T val) {
    std::array<T, N> array {};
    array.fill(val);
    return array;
};


template<template<typename > class C, typename T1, typename T2, std::size_t N>
constexpr auto compare(const std::array<T1, N>& v1, const std::array<T2, N>& v2) -> std::array<bool, N> {
    std::array<bool, N> cmp {};
    C<std::common_type_t<T1, T2>> comparator;
    for (std::size_t k = 0; k < N; ++k) {
        cmp[k] = comparator(v1[k], v2[k]);
    }
    return cmp;
};

template<template<typename > class C, typename T1, typename T2, std::size_t N>
constexpr auto compare(const std::array<T1, N>& v1, const T2 v2) -> std::array<bool, N> {
    std::array<bool, N> cmp {};
    C<std::common_type_t<T1, T2>> comparator;
    for (std::size_t k = 0; k < N; ++k) {
        cmp[k] = comparator(v1[k], v2);
    }
    return cmp;
};

template<template<typename > class C, typename T1, typename T2, std::size_t N>
constexpr auto compare(const T1 v1, const std::array<T2, N>& v2) -> std::array<bool, N> {
    std::array<bool, N> cmp {};
    C<std::common_type_t<T1, T2>> comparator;
    for (std::size_t k = 0; k < N; ++k) {
        cmp[k] = comparator(v1, v2[k]);
    }
    return cmp;
};


template<typename F, typename T, std::size_t N>
constexpr auto map(const F& f, const std::array<T, N>& v)
-> std::array<decltype( f( v[0] ) ), N> {
    typedef decltype( f( v[0] ) ) Ret;
    std::array<Ret, N> ret {};
    for (std::size_t k = 0; k < N; ++k)
        ret[k] = f( v[k] );
    return ret;
};


template<typename F, typename T1, typename T2, std::size_t N>
constexpr auto op(const F& f, const std::array<T1, N>& v1, const std::array<T2, N>& v2)
-> std::array<decltype( f( v1[0], v2[0] ) ), N> {
    typedef decltype( f( v1[0], v2[0] ) ) Ret;
    std::array<Ret, N> ret {};
    for (std::size_t k = 0; k < N; ++k)
        ret[k] = f( v1[k], v2[k] );
    return ret;
};

template<typename F, typename T1, typename T2, std::size_t N>
constexpr auto op(const F& f, const std::array<T1, N>& v1, const T2 v2)
-> std::array<decltype( f( v1[0], v2 ) ), N> {
    typedef decltype( f( v1[0], v2 ) ) Ret;
    std::array<Ret, N> ret {};
    for (std::size_t k = 0; k < N; ++k)
        ret[k] = f( v1[k], v2 );
    return ret;
};

template<typename F, typename T1, typename T2, std::size_t N>
constexpr auto op(const F& f, const T1 v1, const std::array<T2, N>& v2)
-> std::array<decltype( f( v1, v2[0] ) ), N> {
    typedef decltype( f( v1, v2[0] ) ) Ret;
    std::array<Ret, N> ret {};
    for (std::size_t k = 0; k < N; ++k)
        ret[k] = f( v1, v2[k] );
    return ret;
};




template<typename T, std::size_t N, typename F>
constexpr auto reduce(const std::array<T, N>& array,const F& f) -> T {
    T a = array[0];
    for (std::size_t k = 1; k < N; ++k)
        a = f(a, array[k]);
    return a;
};


};  //-- namespace array --
};  //-- namespace utility --


#endif /* LIB_UTILITY_ARRAY_HPP_ */
