/*
 * root.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: ilion
 */

#ifndef LIB_IO_NAMES_ROOT_HPP_
#define LIB_IO_NAMES_ROOT_HPP_


#include <string>


namespace io {
namespace names {

template<typename CharT>
class root {
public:
    typedef CharT char_type;
    typedef std::basic_string<char_type> string_type;

    inline root() :
            mRoot()
    {}
    inline root(const string_type& root) :
            mRoot(root)
    {}
    inline root(const root<CharT>& other) :
            mRoot(other.mRoot)
    {}

    inline
    string_type&
    value() {
        return mRoot;
    }
    inline
    const string_type&
    value() const {
        return mRoot;
    }

private:
    string_type mRoot;
};

}   //-- namespace names --
}   //-- namespace io --


#endif /* LIB_IO_NAMES_ROOT_HPP_ */
