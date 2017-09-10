/*
 * include.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ilion
 */

#ifndef LIB_DOMAIN_UNITE_HPP_
#define LIB_DOMAIN_UNITE_HPP_


#include <ostream>

#include "detail/op.hpp"
#include "../../fn/math/logical_yes.hpp"
#include "../../fn/math/logical_not.hpp"
#include "../../fn/math/logical_and.hpp"
#include "../../fn/math/logical_or.hpp"


namespace domain {

template<
    typename T,
    template<typename > class A,
    template<typename > class B>
using unite = detail::op<T, A, B, ::fn::math::logical_yes, ::fn::math::logical_yes, ::fn::math::logical_or>;

template<
    typename T,
    template<typename > class A,
    template<typename > class B>
std::ostream& operator<< (std::ostream& os, const unite<T, A, B>& domain) {
    os << domain.a << " || " << domain.b;
    return os;
}

}   //-- namespace domain --


#endif /* LIB_DOMAIN_UNITE_HPP_ */
