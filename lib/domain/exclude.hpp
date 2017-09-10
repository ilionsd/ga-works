/*
 * not.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ilion
 */

#ifndef LIB_DOMAIN_EXCLUDE_HPP_
#define LIB_DOMAIN_EXCLUDE_HPP_


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
using left_exclude = detail::op<T, A, B, ::fn::math::logical_yes, ::fn::math::logical_not, ::fn::math::logical_and>;

template<
    typename T,
    template<typename > class A,
    template<typename > class B>
using right_exclude = detail::op<T, A, B, ::fn::math::logical_not, ::fn::math::logical_yes, ::fn::math::logical_and>;

template<
    typename T,
    template<typename > class A,
    template<typename > class B>
using exclude = left_exclude<T, A, B>;

template<
    typename T,
    template<typename > class A,
    template<typename > class B>
std::ostream& operator<< (std::ostream& os, const left_exclude<T, A, B>& domain) {
    os << domain.a << " \\ " << domain.b;
    return os;
}
template<
    typename T,
    template<typename > class A,
    template<typename > class B>
std::ostream& operator<< (std::ostream& os, const right_exclude<T, A, B>& domain) {
    os << domain.b << " \\ " << domain.a;
    return os;
}

}   //-- namespace domain --


#endif /* LIB_DOMAIN_EXCLUDE_HPP_ */
