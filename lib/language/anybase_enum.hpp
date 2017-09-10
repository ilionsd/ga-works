/*
 * anybase_enum.hpp
 *
 *  Created on: Sep 10, 2017
 *      Author: ilion
 */

#ifndef LIB_LANGUAGE_ANYBASE_ENUM_HPP_
#define LIB_LANGUAGE_ANYBASE_ENUM_HPP_


namespace language {

template<class T, class Derived>
class anybase_enum {
public:
    typedef T underlying_type;
    typedef Derived derived_type;
    typedef anybase_enum<underlying_type, derived_type> self_type;

    anybase_enum() = delete;

    inline
    anybase_enum(const derived_type& other) :
        mVal(other.mVal)
    {}
    inline
    derived_type&
    operator= (const derived_type& other) {
        mVal = other.mVal;
        return static_cast<derived_type>(*this);
    }

    inline
    bool
    operator== (const derived_type& other) {
        return mVal == other.mVal;
    }
    inline
    bool
    operator!= (const derived_type& other) {
        return mVal != other.mVal;
    }

    inline
    const underlying_type&
    value() const {
        return mVal;
    }

protected:
    inline
    anybase_enum(const underlying_type& val) :
        mVal(val)
    {}
    inline
    derived_type&
    operator= (const underlying_type& val) {
        mVal = val;
        return static_cast<derived_type>(*this);
    }

private:
    underlying_type mVal;
};

template<class T>
struct add_value {
    typedef T anybase_enum_type;
    typedef typename anybase_enum_type::underlying_type underlying_type;
    inline
    anybase_enum_type
    operator() (const underlying_type& val) {
        return anybase_enum_type (val);
    }
};

}   //-- namespace language --


#endif /* LIB_LANGUAGE_ANYBASE_ENUM_HPP_ */
