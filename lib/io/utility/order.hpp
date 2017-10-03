/*
 * order.hpp
 *
 *  Created on: Oct 3, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_UTILITY_ORDER_HPP_
#define LIB_IO_UTILITY_ORDER_HPP_


#include "../../ordering/order.hpp"
#include "../names/names.hpp"
#include "../names/path.hpp"
#include "../names/root.hpp"
#include "../names/complex_names.hpp"

namespace io {
namespace utility {

template<typename CharT>
inline
int order(
        const names::basic_root<CharT>& a,
        const names::basic_root<CharT>& b) {
    return ::ordering::order(a.value, b.value);
}

template<typename CharT>
inline
int order(
        const names::basic_path<CharT>& a,
        const names::basic_path<CharT>& b) {
    int cmp = ::ordering::order(a.slices, b.slices);
    return cmp;
}

template<typename CharT>
inline
int order(
        const names::basic_names<CharT>& a,
        const names::basic_names<CharT>& b) {
    int cmp = ::ordering::order(a.name, b.name);
    return cmp;
}

template<typename CharT>
inline
int order(
        const names::basic_complex_names<CharT>& a,
        const names::basic_complex_names<CharT>& b) {
    int cmp = order(a.root(), b.root());
    cmp = cmp ? cmp : order(a.path(), b.path());
    cmp = cmp ? cmp : order(static_cast<const names::basic_names<CharT>&>(a), static_cast<const names::basic_names<CharT>&>(b));
    return cmp;
}

}   //-- namespace utility --
}   //-- namespace io --


#endif /* LIB_IO_UTILITY_ORDER_HPP_ */
