/*
 * vector_fn.hpp
 *
 *  Created on: Sep 7, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_DETAIL_VECTOR_FN_HPP_
#define LIB_FN_MATH_DETAIL_VECTOR_FN_HPP_


#include <valarray>
#include <bits/stl_function.h>


namespace fn {
namespace math {
namespace detail {

template<typename T1, typename T2>
using valarray_t = std::_ValArray<T1, T2>;

template<class ClosureType, typename ValueType>
using expression_t = std::_Expr<ClosureType, ValueType>;

template<typename T1, typename T2>
using constant_t = std::_Constant<T1, T2>;

template<class OperationType, template<class, class> class MetaType, class DomType>
using unary_closure_t = std::_UnClos<OperationType, MetaType, DomType>;

template<class OperationType,
    template<class, class> class MetaType1,
    template<class, class> class MetaType2,
    class DomType1,
    class DomType2>
using binary_closure_t = std::_BinClos<OperationType, MetaType1, MetaType2, DomType1, DomType2>;


template<typename T, template<typename > class F>
struct unary_vector_fn {
    typedef T value_type;
    typedef F<T> fn_type;

    template<class Dom>
    inline constexpr auto operator() (const expression_t<Dom, value_type>& expr) const
    -> expression_t<unary_closure_t<fn_type, expression_t, Dom>, value_type> {
        static_assert(std::is_same<typename Dom::value_type, value_type>::value, "Invalid Dom::value_type");
        typedef unary_closure_t<fn_type, expression_t, Dom> closure;
        return expression_t<closure, value_type>( closure(expr()) );
    }
    inline constexpr auto operator() (const std::valarray<value_type>& vals) const
    -> expression_t<unary_closure_t<fn_type, valarray_t, value_type>, value_type> {
        typedef unary_closure_t<fn_type, valarray_t, value_type> closure;
        return expression_t<closure, value_type>( closure(vals) );
    }
};


template<typename T, template<typename > class F>
struct binary_vector_fn {
    typedef T value_type;
    typedef F<T> fn_type;

    template<class Dom1, class Dom2>
    inline constexpr auto operator() (
            const expression_t<Dom1, value_type>& expr1,
            const expression_t<Dom2, value_type>& expr2 ) const {
        static_assert(std::is_same<typename Dom1::value_type, value_type>::value, "Invalid Dom1::value_type");
        static_assert(std::is_same<typename Dom2::value_type, value_type>::value, "Invalid Dom2::value_type");
        typedef binary_closure_t<fn_type, expression_t, expression_t, Dom1, Dom2> closure;
        return expression_t<closure, value_type>( closure(expr1(), expr2()) );
    }
    template<typename Dom>
    inline constexpr auto operator() (
            const expression_t<Dom, value_type>& expr,
            const std::valarray<value_type>& vals) const {
        static_assert(std::is_same<typename Dom::value_type, value_type>::value, "Invalid Dom::value_type");
        typedef binary_closure_t<fn_type, expression_t, valarray_t, Dom, value_type> closure;
        return expression_t<closure, value_type>( closure(expr(), vals) );
    }
    template<typename Dom>
    inline constexpr auto operator() (
            const std::valarray<value_type>& vals,
            const expression_t<Dom, value_type>& expr) const {
        static_assert(std::is_same<typename Dom::value_type, value_type>::value, "Invalid Dom::value_type");
        typedef binary_closure_t<fn_type, valarray_t, expression_t, value_type, Dom> closure;
        return expression_t<closure, value_type>( closure(vals, expr()) );
    }
    template<class Dom>
    inline constexpr auto operator() (
            const expression_t<Dom, value_type>& expr,
            const value_type val) const {
        static_assert(std::is_same<typename Dom::value_type, value_type>::value, "Invalid Dom::value_type");
        typedef binary_closure_t<fn_type, expression_t, constant_t, Dom, value_type> closure;
        return expression_t<closure, value_type>( closure(expr(), val) );
    }
    template<class Dom>
    inline constexpr auto operator() (
            const value_type val,
            const expression_t<Dom, value_type>& expr) const {
        static_assert(std::is_same<typename Dom::value_type, value_type>::value, "Invalid Dom::value_type");
        typedef binary_closure_t<fn_type, constant_t, expression_t, value_type, Dom> closure;
        return expression_t<closure, value_type>( closure(val, expr()) );
    }
    inline constexpr auto operator() (
            const std::valarray<value_type>& vals1,
            const std::valarray<value_type>& vals2) const {
        typedef binary_closure_t<fn_type, valarray_t, valarray_t, value_type, value_type> closure;
        return expression_t<closure, value_type>( closure(vals1, vals2) );
    }
    inline constexpr auto operator() (
            const std::valarray<value_type>& vals,
            const value_type val) const {
        typedef binary_closure_t<fn_type, valarray_t, constant_t, value_type, value_type> closure;
        return expression_t<closure, value_type>( closure(vals, val) );
    }
    inline constexpr auto operator() (
            const value_type val,
            const std::valarray<value_type>& vals) const {
        typedef binary_closure_t<fn_type, constant_t, valarray_t, value_type, value_type> closure;
        return expression_t<closure, value_type>( closure(val, vals) );
    }
};


}   //-- namespace detail --
}   //-- namespace math --
}   //-- namespace fn --


#endif /* LIB_FN_MATH_DETAIL_VECTOR_FN_HPP_ */
