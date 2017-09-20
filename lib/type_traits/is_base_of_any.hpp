/*
 * is_base_of_any.hpp
 *
 *  Created on: Sep 20, 2017
 *      Author: ilion
 */

#ifndef LIB_TYPE_TRAITS_IS_BASE_OF_ANY_HPP_
#define LIB_TYPE_TRAITS_IS_BASE_OF_ANY_HPP_


#include <type_traits>


namespace type_traits {

/*
 * Checks, whatever `Base<...>` is base type of `Derived`
 * http://coliru.stacked-crooked.com/a/eaeac2b9008a97d9
*/
template <template <typename...> class Base, typename Derived>
struct is_base_of_any {
    using U = typename std::remove_cv<Derived>::type;

    template <typename... Args>
    static std::true_type test(Base<Args...>*);

    static std::false_type test(void*);

    using type = decltype(test(std::declval<U*>()));
};

template <template <typename...> class Base, typename Derived>
using is_base_of_any_t = typename is_base_of_any<Base, Derived>::type;

}   //-- namespace type_traits --


#endif /* LIB_TYPE_TRAITS_IS_BASE_OF_ANY_HPP_ */
