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

template<bool UseAfteRoll = true>
class once {
public:
    typedef std::vector<bool> used_type;
    typedef used_type::size_type size_type;
    static constexpr bool use_after_roll = UseAfteRoll;

    inline once() :
            mEngine ( std::random_device()() ),
            mDist (),
            mUsedNumber (),
            mUsed ()
    {}
    inline once(const size_type size) :
            mEngine ( std::random_device()() ),
            mDist (0, size - 1),
            mUsedNumber (),
            mUsed (size, false)
    {}
    inline size_type size() const {
        return mUsed.size();
    }
    inline size_type used_number() const {
        return mUsedNumber;
    }
    inline bool all_used() const {
        return mUsedNumber == size();
    }
    inline operator bool() const {
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
    inline void use(const size_type index) const {
        mUsedNumber += !mUsed[index];
        mUsed[index] = true;
    }
    inline void unuse(const size_type index) const {
        mUsedNumber -= mUsed[index];
        mUsed[index] = false;
    }
    inline once<use_after_roll>& operator= (const size_type size) {
        reset(size);
        return (*this);
    }
    inline size_type operator() () const {
        size_type index = roll();
        return index;
    }

protected:
    inline size_type roll() const {
        size_type index;
        if (used_number() == size())
            refresh();
        do {
            index = mDist(mEngine);
        }
        while (mUsed[index]);
        if (use_after_roll) use(index);
        return index;
    }

private:
    mutable std::mt19937_64 mEngine;
    mutable std::uniform_int_distribution<size_type> mDist;
    mutable size_type mUsedNumber;
    mutable std::vector<bool> mUsed;
};

template<bool UseAfterRoll = true>
inline once<UseAfterRoll> make_once(const std::size_t size) {
    return once<UseAfterRoll>(size);
}

}   //-- namespace algorithm --


#endif /* LIB_ALGORITHM_ONCE_HPP_ */
