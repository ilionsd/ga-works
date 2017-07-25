/*
 * tuple.hpp
 *
 *  Created on: Jul 21, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_TUPLE_HPP_
#define LIB_UTILITY_TUPLE_HPP_

#include <tuple>
#include <utility>


namespace utility {

namespace detail {


template<typename F, typename... Ts, std::size_t... I>
constexpr void for_each_impl(const F& func, const std::tuple<Ts...>& tuple, std::index_sequence<I...>) {
    auto l = { ( func(std::get<I>(tuple)), 0 )... };
};


};  //-- namespace detail --


template<typename F, typename... Ts, typename Indices = std::make_index_sequence<sizeof...(Ts)>>
constexpr void for_each(const F& func, const std::tuple<Ts...>& tuple) {
    detail::for_each_impl(func, tuple, Indices{});
};


};  //-- namesapce utility --


#endif /* LIB_UTILITY_TUPLE_HPP_ */
