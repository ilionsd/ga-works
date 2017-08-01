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

namespace utility {
namespace vector {

template<typename F, typename T>
constexpr auto map(F f, const std::vector<T>& vec) -> std::vector<decltype(f(vec[0]))>{
    typedef decltype(f(vec[0])) ret_type;
    std::vector<ret_type> ret { vec.size() };
    for (std::size_t k = 0; k < vec.size(); ++k)
        ret[k] = f( vec[k] );
    return ret;
}

}   //-- namespace vector --
}   //-- namespace utility --


#endif /* LIB_UTILITY_VECTOR_HPP_ */
