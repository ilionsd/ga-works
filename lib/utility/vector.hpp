/*
 * vector.hpp
 *
 *  Created on: Jul 28, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_VECTOR_HPP_
#define LIB_UTILITY_VECTOR_HPP_

#include <cstddef>
#include <vector>
#include <type_traits>

namespace utility {
namespace vector {

template<typename... Ts>
inline constexpr auto make(const Ts... args) -> std::vector<std::common_type_t<Ts...>> {
    return { args... };
}
template<typename T, typename... Ts>
inline constexpr auto make_of(const Ts... args) -> std::vector<T> {
    return { T(args)... };
}
inline auto make_arange(const std::size_t n) -> std::vector<std::size_t> {
    std::vector<std::size_t> vec ( n + 1 );
    for (std::size_t k = 0; k <= n; ++k)
        vec[k] = k;
    return vec;
}


template<typename F, typename T>
constexpr auto map(F f, const std::vector<T>& vec) -> std::vector<decltype( f( T() ) )> {

    typedef decltype( f( T() ) ) ret_type;
    std::vector<ret_type> ret ( vec.size() );
    for (std::size_t k = 0; k < vec.size(); ++k)
        ret[k] = f( vec[k] );
    return ret;
}

}   //-- namespace vector --
}   //-- namespace utility --


#endif /* LIB_UTILITY_VECTOR_HPP_ */
