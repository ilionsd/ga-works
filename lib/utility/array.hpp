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


template<typename... Ts>
constexpr auto make_array(const Ts... args) -> std::array<std::common_type_t<Ts...>, sizeof...(Ts)> {
    return { args... };
};

template<typename T, typename... Ts>
constexpr auto make_array_of(const Ts... args) -> std::array<T, sizeof...(Ts)> {
    return { T(args)... };
};

template<typename T, std::size_t N>
inline constexpr std::array<T, N> array_fill(const T val) {
    std::array<T, N> array {};
    array.fill(val);
    return array;
};


template<template<typename > class C, typename T1, typename T2, std::size_t N>
constexpr auto array_compare(const std::array<T1, N>& v1, const std::array<T2, N>& v2) -> std::array<bool, N> {
    std::array<bool, N> cmp {};
    C<std::common_type_t<T1, T2>> comparator;
    for (std::size_t k = 0; k < N; ++k) {
        cmp[k] = comparator(v1[k], v2[k]);
    }
    return cmp;
};

template<template<typename > class C, typename T1, typename T2, std::size_t N>
constexpr auto array_compare(const std::array<T1, N>& v1, const T2 v2) -> std::array<bool, N> {
    std::array<bool, N> cmp {};
    C<std::common_type_t<T1, T2>> comparator;
    for (std::size_t k = 0; k < N; ++k) {
        cmp[k] = comparator(v1[k], v2);
    }
    return cmp;
};

template<template<typename > class C, typename T1, typename T2, std::size_t N>
constexpr auto array_compare(const T1 v1, const std::array<T2, N>& v2) -> std::array<bool, N> {
    std::array<bool, N> cmp {};
    C<std::common_type_t<T1, T2>> comparator;
    for (std::size_t k = 0; k < N; ++k) {
        cmp[k] = comparator(v1, v2[k]);
    }
    return cmp;
};


template<typename F, typename... Ts, std::size_t N>
constexpr auto array_map(const F& f, const std::array<Ts, N>&... vs) {
    typedef decltype( f( vs[0]... ) ) Ret;
    std::array<Ret, N> ret {};
    for (std::size_t k = 0; k < N; ++k)
        ret[k] = f( vs[k]... );
    return ret;
};


template<typename T, std::size_t N, typename F>
constexpr auto array_reduce(const std::array<T, N>& array,const F& f) -> T {
    T a = array[0];
    for (std::size_t k = 1; k < N; ++k)
        a = f(a, array[k]);
    return a;
};


};  //-- namespace utility --


#endif /* LIB_UTILITY_ARRAY_HPP_ */
