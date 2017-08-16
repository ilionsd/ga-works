/*
 * assign_if.hpp
 *
 *  Created on: Aug 15, 2017
 *      Author: ilion
 */

#ifndef LIB_UTILITY_ASSIGN_IF_HPP_
#define LIB_UTILITY_ASSIGN_IF_HPP_


#include <utility>
#include <bits/stl_function.h>


namespace utility {

template<typename F>
struct assign_if {
    typedef F predicate_type;

    template<typename... Ts>
    inline constexpr assign_if(Ts&&... args) :
        predicate( std::forward<Ts>(args)... )
    {}

    template<typename T>
    inline constexpr bool operator() (T& a, T& b) const {
        bool eval = predicate(a, b);
        if (eval)
            a = b;
        return eval;
    }

    predicate_type predicate;
};

template<typename T>
using assign_if_less = assign_if<std::less<T>>;
template<typename T>
using assign_if_greater = assign_if<std::greater<T>>;

}   //-- namespace utility --


#endif /* LIB_UTILITY_ASSIGN_IF_HPP_ */
