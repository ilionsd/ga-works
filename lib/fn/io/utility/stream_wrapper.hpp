/*
 * stream_wrapper.hpp
 *
 *  Created on: Sep 19, 2017
 *      Author: ilion
 */

#ifndef LIB_FN_IO_UTILITY_STREAM_WRAPPER_HPP_
#define LIB_FN_IO_UTILITY_STREAM_WRAPPER_HPP_


#include <utility>


namespace fn {
namespace io {
namespace utility {

template<class S>
class base_wrapper {
public:
    typedef S stream_type;

    template<typename... Ts>
    inline
    base_wrapper(Ts&&... args) :
        mStream(std::forward<Ts>(args)...)
    {}

    inline
    operator stream_type&() {
        return mStream;
    }
    inline
    stream_type&
    get() {
        return mStream;
    }

private:
    stream_type mStream;
};

template<class IS>
class istream_wrapper : public base_wrapper<IS> {
public:
    template<typename T>
    inline
    void
    operator() (T&& val) {
        get() >> val;
    }
};

template<class OS>
class ostream_wrapper : public base_wrapper<OS> {
public:
    template<typename T>
    inline
    void
    operator() (T&& val) {
        get() << val;
    }
};

}   //-- namespace utility --
}   //-- namespace io --
}   //-- namespace fn --


#endif /* LIB_FN_IO_UTILITY_STREAM_WRAPPER_HPP_ */
