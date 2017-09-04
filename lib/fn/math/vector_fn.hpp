/*
 * vector_fn.hpp
 *
 *  Created on: Aug 17, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_MATH_VECTOR_FN_HPP_
#define LIB_FN_MATH_VECTOR_FN_HPP_


#include <valarray>
#include <bits/stl_function.h>
#include <type_traits>


#include "abs.hpp"

#include "floor.hpp"
#include "round.hpp"
#include "ceil.hpp"

#include "sin.hpp"
#include "cos.hpp"

#include "square.hpp"
#include "cube.hpp"
#include "power.hpp"
#include "exp.hpp"
#include "sqrt.hpp"

#include "log.hpp"
#include "ln.hpp"
#include "lg.hpp"
#include "log2.hpp"


namespace fn {
namespace math {


template<typename T1, typename T2>
using valarray = std::_ValArray<T1, T2>;

template<class ClosureType, typename ValueType>
using expression = std::_Expr<ClosureType, ValueType>;

template<typename T1, typename T2>
using constant = std::_Constant<T1, T2>;

template<class OperationType, template<class, class> class MetaType, class DomType>
using unary_closure = std::_UnClos<OperationType, MetaType, DomType>;

template<class OperationType,
    template<class, class> class MetaType1,
    template<class, class> class MetaType2,
    class DomType1,
    class DomType2>
using binary_closure = std::_BinClos<OperationType, MetaType1, MetaType2, DomType1, DomType2>;


template<typename T, template<typename > class F>
struct unary_vector_fn {
    typedef T value_type;
    typedef F<T> fn_type;

    template<class Dom>
    inline constexpr auto operator() (const expression<Dom, value_type>& expr) const
    -> expression<unary_closure<fn_type, expression, Dom>, value_type> {
        static_assert(std::is_same<typename Dom::value_type, value_type>::value, "Invalid Dom::value_type");
        typedef unary_closure<fn_type, expression, Dom> closure;
        return expression<closure, value_type>( closure(expr()) );
    }
    inline constexpr auto operator() (const std::valarray<value_type>& vals) const
    -> expression<unary_closure<fn_type, valarray, value_type>, value_type> {
        typedef unary_closure<fn_type, valarray, value_type> closure;
        return expression<closure, value_type>( closure(vals) );
    }
};

template<typename T, template<typename > class F>
struct binary_vector_fn {
    typedef T value_type;
    typedef F<T> fn_type;

    template<class Dom1, class Dom2>
    inline constexpr auto operator() (
            const expression<Dom1, value_type>& expr1,
            const expression<Dom2, value_type>& expr2 ) const {
        static_assert(std::is_same<typename Dom1::value_type, value_type>::value, "Invalid Dom1::value_type");
        static_assert(std::is_same<typename Dom2::value_type, value_type>::value, "Invalid Dom2::value_type");
        typedef binary_closure<fn_type, expression, expression, Dom1, Dom2> closure;
        return expression<closure, value_type>( closure(expr1(), expr2()) );
    }
    template<typename Dom>
    inline constexpr auto operator() (
            const expression<Dom, value_type>& expr,
            const std::valarray<value_type>& vals) const {
        static_assert(std::is_same<typename Dom::value_type, value_type>::value, "Invalid Dom::value_type");
        typedef binary_closure<fn_type, expression, valarray, Dom, value_type> closure;
        return expression<closure, value_type>( closure(expr(), vals) );
    }
    template<typename Dom>
    inline constexpr auto operator() (
            const std::valarray<value_type>& vals,
            const expression<Dom, value_type>& expr) const {
        static_assert(std::is_same<typename Dom::value_type, value_type>::value, "Invalid Dom::value_type");
        typedef binary_closure<fn_type, valarray, expression, value_type, Dom> closure;
        return expression<closure, value_type>( closure(vals, expr()) );
    }
    template<class Dom>
    inline constexpr auto operator() (
            const expression<Dom, value_type>& expr,
            const value_type val) const {
        static_assert(std::is_same<typename Dom::value_type, value_type>::value, "Invalid Dom::value_type");
        typedef binary_closure<fn_type, expression, constant, Dom, value_type> closure;
        return expression<closure, value_type>( closure(expr(), val) );
    }
    template<class Dom>
    inline constexpr auto operator() (
            const value_type val,
            const expression<Dom, value_type>& expr) const {
        static_assert(std::is_same<typename Dom::value_type, value_type>::value, "Invalid Dom::value_type");
        typedef binary_closure<fn_type, constant, expression, value_type, Dom> closure;
        return expression<closure, value_type>( closure(val, expr()) );
    }
    inline constexpr auto operator() (
            const std::valarray<value_type>& vals1,
            const std::valarray<value_type>& vals2) const {
        typedef binary_closure<fn_type, valarray, valarray, value_type, value_type> closure;
        return expression<closure, value_type>( closure(vals1, vals2) );
    }
    inline constexpr auto operator() (
            const std::valarray<value_type>& vals,
            const value_type val) const {
        typedef binary_closure<fn_type, valarray, constant, value_type, value_type> closure;
        return expression<closure, value_type>( closure(vals, val) );
    }
    inline constexpr auto operator() (
            const value_type val,
            const std::valarray<value_type>& vals) const {
        typedef binary_closure<fn_type, constant, valarray, value_type, value_type> closure;
        return expression<closure, value_type>( closure(val, vals) );
    }

};

#ifndef FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF
#define FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( NAME ) \
template<typename T>                                   \
using NAME##_v = unary_vector_fn<T, NAME>;
#endif

#ifndef FN_MATH_BINARY_VECTOR_FUNC_TEMPLATE_DEF
#define FN_MATH_BINARY_VECTOR_FUNC_TEMPLATE_DEF( NAME ) \
template<typename T>                                    \
using NAME##_v = binary_vector_fn<T, NAME>;
#endif

FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( abs )

FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( floor )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( round )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( ceil )

FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( sin )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( cos )

FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( square )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( cube )
FN_MATH_BINARY_VECTOR_FUNC_TEMPLATE_DEF( power )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( exp )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( sqrt )

FN_MATH_BINARY_VECTOR_FUNC_TEMPLATE_DEF( log )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( ln )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( lg )
FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF( log2 )


}   //-- namespace math --
}   //-- namespace fn --


#ifdef FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF
#undef FN_MATH_UNARY_VECTOR_FUNC_TEMPLATE_DEF
#endif

#ifdef FN_MATH_BINARY_VECTOR_FUNC_TEMPLATE_DEF
#undef FN_MATH_BINARY_VECTOR_FUNC_TEMPLATE_DEF
#endif


#endif /* LIB_FN_MATH_VECTOR_FN_HPP_ */
