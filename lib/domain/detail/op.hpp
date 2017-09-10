/*
 * op.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ilion
 */

#ifndef LIB_DOMAIN_DETAIL_OP_HPP_
#define LIB_DOMAIN_DETAIL_OP_HPP_


#include <bits/stl_function.h>


namespace domain {
namespace detail {

template<
    typename T,
    template<typename > class A,
    template<typename > class B,
    template<typename > class ModA,
    template<typename > class ModB,
    template<typename, typename > class LogicalBinaryOP>
struct op final : public std::unary_function<T, bool> {
    typedef typename std::unary_function<T, bool>::argument_type argument_type;
    typedef A<T> a_type;
    typedef B<T> b_type;
    typedef ModA<bool> mod_a_type;
    typedef ModB<bool> mod_b_type;
    typedef LogicalBinaryOP<bool, bool> op_type;

    inline op(a_type a, b_type b) :
        a(a),
        b(b)
    {}

    inline bool operator() (const argument_type val) const {
        return op_type()( mod_a_type()( a(val) ) , mod_b_type()( b(val) ) );
    }

    a_type a;
    b_type b;
};

}   //-- namespace detail --
}   //-- namespace domain --


#endif /* LIB_DOMAIN_DETAIL_OP_HPP_ */
