/*
 * argument_cast.hpp
 *
 *  Created on: Oct 25, 2017
 *      Author: ilion
 */

#ifndef LIB_LANGUAGE_ARGUMENT_CAST_HPP_
#define LIB_LANGUAGE_ARGUMENT_CAST_HPP_


namespace language {

template<typename F, typename... ArgumentTs>
struct argument_cast {

    inline
    argument_cast(F fn) :
        fn(fn)
    {}

    template<typename... Ts>
    inline
    auto operator() (Ts... args) const {
        return fn(static_cast<ArgumentTs>(std::forward<Ts>(args))...);
    }
    F fn;
};

}   //-- namespace language --


#endif /* LIB_LANGUAGE_ARGUMENT_CAST_HPP_ */
