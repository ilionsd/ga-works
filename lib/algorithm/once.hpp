/*
 * once.hpp
 *
 *  Created on: Aug 5, 2017
 *      Author: ilion
 */

#ifndef LIB_ALGORITHM_ONCE_HPP_
#define LIB_ALGORITHM_ONCE_HPP_

#include <cstddef>
#include <vector>
#include <random>

namespace algorithm {

class base_once {
public:
    typedef std::vector<bool> used_type;
    typedef used_type::size_type size_type;

    inline constexpr base_once() :
            mGen (std::random_device()()),
            mDist (),
            mUsedNumber (),
            mUsed ()
    {}
    inline constexpr base_once(const size_type size) :
            mGen (std::random_device()()),
            mDist (0, size - 1),
            mUsedNumber (),
            mUsed (size, false)
    {}
    inline constexpr size_type size() const {
        return mUsed.size();
    }
    inline constexpr size_type used_number() const {
        return mUsedNumber;
    }
    inline constexpr bool all_used() const {
        return mUsedNumber == size();
    }
    inline constexpr operator bool() const {
        return !all_used();
    }
    void reset(const size_type size) {
        mUsedNumber = 0;
        mUsed.assign(size, false);
    }
    void refresh() const {
        mUsedNumber = 0;
        mUsed.assign(size(), false);
    }
    inline constexpr void use(const size_type index) const {
        mUsedNumber += !mUsed[index];
        mUsed[index] = true;
    }
    inline constexpr void unuse(const size_type index) const {
        mUsedNumber -= mUsed[index];
        mUsed[index] = false;
    }

protected:
    inline constexpr size_type roll() const {
        size_type index;
        if (used_number() == size())
            refresh();
        do {
            index = mDist(mGen);
        }
        while (mUsed[index]);
        use(index);
        return index;
    }

private:
    mutable std::mt19937_64 mGen;
    mutable std::uniform_int_distribution mDist;
    mutable size_type mUsedNumber;
    mutable std::vector<bool> mUsed;
};

template<typename T = void>
class once : public base_once {
public:
    typedef base_once base_type;
    typedef base_type::size_type size_type;
    typedef T container_type;
    typedef typename container_type::value_type value_type;

    inline constexpr once() noexcept :
            base_type(),
            mValues()
    {}
    inline constexpr once(const container_type& values) noexcept :
            base_type(values.size()),
            mValues (values)
    {}
    inline once<container_type>& operator= (const container_type& values) {
        reset(values.size());
        return (*this);
    }
    inline constexpr value_type operator() () const {
        size_type index = roll();
        return mValues[index];
    }

private:
    container_type mValues;
};

template<>
class once<void> : public base_once {
public:
    typedef base_once base_type;
    typedef base_type::size_type size_type;

    inline constexpr once() noexcept :
            base_type()
    {}
    inline constexpr once(const size_type size) noexcept :
            base_type(size)
    {}
    inline once<void>& operator= (const size_type size) {
        reset(size);
        return (*this);
    }
    inline constexpr size_type operator() () const {
        size_type index = roll();
        return index;
    }
};

template<typename T>
inline once<T> make_once(const T& values) {
    return once<T>(values);
}

}   //-- namespace algorithm --


#endif /* LIB_ALGORITHM_ONCE_HPP_ */
