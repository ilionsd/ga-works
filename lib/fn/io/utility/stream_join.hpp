/*
 * stream_join.hpp
 *
 *  Created on: Sep 19, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_IO_UTILITY_STREAM_JOIN_HPP_
#define LIB_FN_IO_UTILITY_STREAM_JOIN_HPP_


#include <string>
#include "../../../io/separator.hpp"


namespace fn {
namespace io {
namespace utility {

template<typename CharT>
class basic_stream_join {
public:
    typedef CharT char_type;
    typedef basic_stream_join<char_type> self_type;
    typedef std::basic_ostringstream<char_type> stream_type;
    typedef std::basic_string<char_type> string_type;
    typedef ::io::basic_separator<char_type> separator_type;

    inline
    basic_stream_join(separator_type separator = separator_type::space) :
        mStream(),
        mSeparator(separator)
    {}

    template<class T>
    self_type&
    operator<< (const T& val) {
        if (not_first())
            mStream << mSeparator;
        mStream << val;
        return *this;
    }

    inline
    string_type
    str() const {
        return mStream.str();
    }

protected:
    bool not_first() {
        bool t = mNotFirst;
        mNotFirst = true;
        return t;
    }

private:
    bool mNotFirst = false;
    separator_type mSeparator;
    stream_type mStream;
};

using ostream_join  = basic_stream_join<char>;
using wostream_join = basic_stream_join<wchar_t>;

}   //-- namespace utility --
}   //-- namespace io --
}   //-- namespace fn --


#endif /* LIB_FN_IO_UTILITY_STREAM_JOIN_HPP_ */
