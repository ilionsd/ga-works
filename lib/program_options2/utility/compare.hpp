/*
 * compare.hpp
 *
 *  Created on: Sep 26, 2017
 *      Author: ilion
 */

#ifndef LIB_PROGRAM_OPTIONS2_UTILITY_COMPARE_HPP_
#define LIB_PROGRAM_OPTIONS2_UTILITY_COMPARE_HPP_


#include <bits/stl_function.h>

#include "../../io/utility/order.hpp"
#include "../description/option.hpp"


#ifndef PROGRAM_OPTIONS2_UTILITY_COMPARE_TEMPLATE_SPEC
#define PROGRAM_OPTIONS2_UTILITY_COMPARE_TEMPLATE_SPEC( NAME , COMPARE_SIGN ) \
template<typename CharT>                                                      \
struct NAME :                                                                 \
        public std::binary_function<                                          \
                    description::basic_option<CharT>,                         \
                    description::basic_option<CharT>,                         \
                    bool> {                                                   \
    typedef CharT char_type;                                                  \
    typedef description::basic_option<char_type> option_type;                 \
    inline                                                                    \
    bool                                                                      \
    operator() (                                                              \
            const option_type& a,                                             \
            const option_type& b) const {                                     \
        return ::io::utility::order(a.names(), b.names()) COMPARE_SIGN 0;     \
    }                                                                         \
};
#endif


namespace program_options2 {
namespace utility {

template<typename CharT> struct     equal_to;
template<typename CharT> struct not_equal_to;
template<typename CharT> struct less;
template<typename CharT> struct less_equal;
template<typename CharT> struct greater;
template<typename CharT> struct greater_equal;

PROGRAM_OPTIONS2_UTILITY_COMPARE_TEMPLATE_SPEC(     equal_to  , == )
PROGRAM_OPTIONS2_UTILITY_COMPARE_TEMPLATE_SPEC( not_equal_to  , != )
PROGRAM_OPTIONS2_UTILITY_COMPARE_TEMPLATE_SPEC( less          , <  )
PROGRAM_OPTIONS2_UTILITY_COMPARE_TEMPLATE_SPEC( less_equal    , <= )
PROGRAM_OPTIONS2_UTILITY_COMPARE_TEMPLATE_SPEC( greater       , >  )
PROGRAM_OPTIONS2_UTILITY_COMPARE_TEMPLATE_SPEC( greater_equal , >= )

}   //-- namespace utility --
}   //-- namespace program_options2 --


#ifdef PROGRAM_OPTIONS2_UTILITY_COMPARE_TEMPLATE_SPEC
#undef PROGRAM_OPTIONS2_UTILITY_COMPARE_TEMPLATE_SPEC
#endif


#endif /* LIB_PROGRAM_OPTIONS2_UTILITY_COMPARE_HPP_ */
