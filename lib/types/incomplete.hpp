/*
 * incomplete.hpp
 *
 *  Created on: Aug 1, 2017
 *      Author: ilion
 */

#ifndef LIB_TYPES_INCOMPLETE_HPP_
#define LIB_TYPES_INCOMPLETE_HPP_


namespace types {

template<template<typename... > class T>
struct incomplete {
    template<typename... Ts>
    using type = T<Ts...>;
};

template<template<typename... > class T>
using incomplete_t = typename incomplete<T>::type;

}   //-- namespace types --


#endif /* LIB_TYPES_INCOMPLETE_HPP_ */
