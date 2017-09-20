/*
 * for_each_impl.hpp
 *
 *  Created on: Sep 17, 2017
 *      Author: ilion
 */

#ifndef LIB_TUPLE_DETAIL_FOR_EACH_IMPL_HPP_
#define LIB_TUPLE_DETAIL_FOR_EACH_IMPL_HPP_


#include <cstddef>
#include <tuple>
#include <utility>


namespace tuple {
namespace detail {

template<typename F, typename Tuple, std::size_t... I>
constexpr
void
for_each_impl(F&& f, Tuple&& t, std::index_sequence<I...>) {
    auto l = { ( f(std::get<I>(t)), 0 )... };
};

}   //-- namespace detail --
}   //-- namespace tuple --


#endif /* LIB_TUPLE_DETAIL_FOR_EACH_IMPL_HPP_ */
