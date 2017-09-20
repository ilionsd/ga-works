/*
 * for_each.hpp
 *
 *  Created on: Sep 17, 2017
 *      Author: ilion
 */

#ifndef LIB_TUPLE_FOR_EACH_HPP_
#define LIB_TUPLE_FOR_EACH_HPP_


#include <utility>

#include "detail/for_each_impl.hpp"


namespace tuple {

template<typename F, typename Tuple>
constexpr
void
for_each(F&& f, Tuple&& t) {
    detail::for_each_impl(
            std::forward<F>( f ),
            std::forward<Tuple>( t ),
            std::make_index_sequence<std::tuple_size<Tuple>::value>() );
};

}   //-- namespace tuple --


#endif /* LIB_TUPLE_FOR_EACH_HPP_ */
