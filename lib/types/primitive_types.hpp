/*
 * integer.hpp
 *
 *  Created on: Jul 28, 2017
 *      Author: ilion
 */

#ifndef LIB_TYPES_PRIMITIVE_TYPES_HPP_
#define LIB_TYPES_PRIMITIVE_TYPES_HPP_


#define PRIMITIVE_TYPES_TEMPLATE_DEFINE( TEMPLATE_NAME) \
template<typename T> \
struct TEMPLATE_NAME { \
    typedef void type; \
};

#define PRIMITIVE_TYPES_TEMPLATE_SPEC( TEMPLATE_NAME , SPEC_TYPE ) \
template<> \
struct TEMPLATE_NAME<SPEC_TYPE> { \
    typedef SPEC_TYPE type; \
};


namespace types {


PRIMITIVE_TYPES_TEMPLATE_DEFINE( integer )
PRIMITIVE_TYPES_TEMPLATE_SPEC( integer , signed char      )
PRIMITIVE_TYPES_TEMPLATE_SPEC( integer , signed short     )
PRIMITIVE_TYPES_TEMPLATE_SPEC( integer , signed int       )
PRIMITIVE_TYPES_TEMPLATE_SPEC( integer , signed long      )
PRIMITIVE_TYPES_TEMPLATE_SPEC( integer , signed long long )
template<typename T>
using integer_t = typename integer<T>::type;


PRIMITIVE_TYPES_TEMPLATE_DEFINE( unsigned_indeger )
PRIMITIVE_TYPES_TEMPLATE_SPEC( unsigned_indeger , unsigned char      )
PRIMITIVE_TYPES_TEMPLATE_SPEC( unsigned_indeger , unsigned short     )
PRIMITIVE_TYPES_TEMPLATE_SPEC( unsigned_indeger , unsigned int       )
PRIMITIVE_TYPES_TEMPLATE_SPEC( unsigned_indeger , unsigned long      )
PRIMITIVE_TYPES_TEMPLATE_SPEC( unsigned_indeger , unsigned long long )
template<typename T>
using unsigned_integer_t = typename unsigned_indeger<T>::type;


PRIMITIVE_TYPES_TEMPLATE_DEFINE( floating_point )
PRIMITIVE_TYPES_TEMPLATE_SPEC(  floating_point, float       )
PRIMITIVE_TYPES_TEMPLATE_SPEC(  floating_point, double      )
PRIMITIVE_TYPES_TEMPLATE_SPEC(  floating_point, long double )
template<typename T>
using floating_point_t = typename floating_point<T>::type;


};


#undef PRIMITIVE_TYPES_TEMPLATE_DEFINE
#undef PRIMITIVE_TYPES_TEMPLATE_SPEC


#endif /* LIB_TYPES_PRIMITIVE_TYPES_HPP_ */
