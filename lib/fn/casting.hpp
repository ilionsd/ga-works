/*
 * casting.hpp
 *
 *  Created on: Oct 25, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_CASTING_HPP_
#define LIB_FN_CASTING_HPP_


#ifndef FN_DEFINE_CAST_F
#define FN_DEFINE_CAST_F( NAME , CAST ) \
template<typename T>                    \
struct NAME {                           \
    typedef T target_type;              \
    template<typename Val>              \
    inline                              \
    target_type                         \
    operator() (const Val& val) const { \
        return CAST<target_type>(val);  \
    }                                   \
};
#endif


namespace fn {

template<typename T> struct static_cast_f;

FN_DEFINE_CAST_F( static_cast_f , static_cast )

}   //-- namespace fn --


#ifdef FN_DEFINE_CAST_F
#undef FN_DEFINE_CAST_F
#endif


#endif /* LIB_FN_CASTING_HPP_ */
