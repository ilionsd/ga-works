/*
 * valarray.hpp
 *
 *  Created on: Jul 21, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_VALARRAY_HPP_
#define LIB_UTILITY_VALARRAY_HPP_

#include <valarray>
#include <type_traits>

namespace utility {

template<typename... Ts>
auto make_valarray(const Ts... args) -> std::valarray<std::common_type_t<Ts...>> {
    return { args };
};

};  //-- namespace utility --


#endif /* LIB_UTILITY_VALARRAY_HPP_ */
