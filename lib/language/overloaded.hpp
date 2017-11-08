/*
 * overloaded.hpp
 *
 *  Created on: Oct 25, 2017
 *      Author: ilion
 */

#ifndef LIB_LANGUAGE_OVERLOADED_HPP_
#define LIB_LANGUAGE_OVERLOADED_HPP_


namespace language {

template<class... Ts>
struct overloaded :
        Ts... {
    using Ts::operator()...;
};

template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

}   //-- namespace language --


#endif /* LIB_LANGUAGE_OVERLOADED_HPP_ */
