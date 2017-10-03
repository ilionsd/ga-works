/*
 * validator.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ilion
 */

#ifndef LIB_DOMAIN_ANY_HPP_
#define LIB_DOMAIN_ANY_HPP_


#include <limits>
#include <ostream>
#include <bits/stl_function.h>
#include <functional>


namespace domain {

template<typename T>
struct any : public std::unary_function<T, bool> {
    typedef typename std::unary_function<T, bool>::argument_type argument_type;
    inline constexpr bool operator() (const argument_type) const {
        return true;
    }
};

template<typename T>
std::ostream& operator<< (std::ostream& os, const any<T>&) {
    os << "[ " << std::numeric_limits<T>::lowest() << " ; " << std::numeric_limits<T>::max() << " ]";
    return os;
}

}   //-- namespace domain --


#endif /* LIB_DOMAIN_ANY_HPP_ */
