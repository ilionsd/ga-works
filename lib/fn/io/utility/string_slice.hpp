/*
 * string_slice.hpp
 *
 *  Created on: Sep 24, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_IO_UTILITY_STRING_SLICE_HPP_
#define LIB_FN_IO_UTILITY_STRING_SLICE_HPP_


#include <string>
#include <vector>


namespace fn {
namespace io {
namespace utility {

template<typename CharT>
struct string_slice {
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;

    std::vector<string_type>
    operator() (const string_type& str, const string_type& separator) const {
        typedef typename string_type::size_type size_type;
        size_type pos = 0;
        std::vector<string_type> slices;
        do {
            size_type next = str.find(separator, pos);
            slices.push_back(str.substr(pos, next - pos));
            pos = next + separator.size();
        }
        while (string_type::npos == pos);
        return slices;
    }
};

}   //-- namespace utility --
}   //-- namespace io --
}   //-- namespace fn --


#endif /* LIB_FN_IO_UTILITY_STRING_SLICE_HPP_ */
