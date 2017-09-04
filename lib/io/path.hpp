/*
 * path.hpp
 *
 *  Created on: Sep 4, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_PATH_HPP_
#define LIB_IO_PATH_HPP_


#include <string>
#include <vector>


#include "join.hpp"


namespace io {

template<typename CharT, CharT Sep>
class basic_path {
public:
    typedef CharT char_type;
    static constexpr char_type separator = Sep;
    typedef basic_path<char_type, separator> self_type;
    typedef std::basic_string<char_type> string_type;

    static constexpr char_type dot = '.';
    static constexpr char_type slash = '/';


    inline basic_path() :
            mPath()
    {}
    inline basic_path(const self_type& path) :
            mPath(path.mPath)
    {}

    string_type build() const {
        return join<std::vector<string_type>>()(mPath, separator);
    }

    inline self_type& add(const char_type* path) {
        return add(string_type(path));
    }
    self_type& add(const string_type& path) {
        typedef typename string_type::size_type size_type;
        size_type pos = 0;
        do {
            size_type next = path.find_first_of(separator, pos);
            mPath.push_back(path.substr(pos, next - pos));
            pos = next + 1;
        }
        while (string_type::npos == pos);
        return *this;
    }
    self_type& add(const self_type& path) {
        mPath.push_back(path.mPath);
        return *this;
    }

private:
    std::vector<string_type> mPath;
};

template<char Sep>
using path = basic_path<char, Sep>;
template<wchar_t Sep>
using wpath = basic_path<wchar_t, Sep>;

}   //-- namespace io --


#endif /* LIB_IO_PATH_HPP_ */
