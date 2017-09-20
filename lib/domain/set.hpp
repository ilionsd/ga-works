/*
 * set.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ilion
 */

#ifndef LIB_DOMAIN_SET_HPP_
#define LIB_DOMAIN_SET_HPP_


#include <bits/stl_function.h>
#include <unordered_set>

#include "../io/utility/vector_join.hpp"


namespace domain {

template<typename T>
struct set : public std::unary_function<T, bool> {
    typedef typename std::unary_function<T, bool>::argument_type argument_type;

    template<typename... Ts>
    inline set(const Ts&&... args) :
        set(std::forward(args)...)
    {}

    inline bool operator() (const argument_type val) const {
        return (this->set.find(val) != this->set.cend());
    }

    std::unordered_set<argument_type> set;
};

template<typename T>
std::ostream& operator<< (std::ostream& os, const set<T>& domain) {
    os << "{ " << ::io::utility::join(domain.set, ", ") << " }";
    return os;
}

}   //-- namespace domain --


#endif /* LIB_IO_VALIDATOR_SET_HPP_ */
