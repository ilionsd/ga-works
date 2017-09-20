/*
 * unique_vector.hpp
 *
 *  Created on: Sep 12, 2017
 *      Author: ilion
 */

#ifndef LIB_LANGUAGE_VECTOR_SET_HPP_
#define LIB_LANGUAGE_VECTOR_SET_HPP_


#include <algorithm>
#include <cstddef>
#include <cassert>
#include <iterator>
#include <set>
#include <vector>
#include <functional>
#include <tuple>

#include "../utility/cyclic_shift.hpp"


namespace language {

template<typename T, class Set = std::set<T>>
class vector_set {
public:
    typedef T value_type;
    typedef Set set;
    typedef vector_set<value_type, set> self_type;
    typedef typename set::iterator set_iterator;
    typedef typename set::const_iterator const_set_iterator;
    typedef std::vector<set_iterator> vector;
    typedef typename vector::iterator vec_iterator;
    typedef typename vector::const_iterator const_vec_iterator;


    class reference {
    public:
        typedef const value_type& const_ref;
        typedef value_type& ref;

        inline
        reference(self_type& vectorSet, std::size_t index) :
            mVectorSet(vectorSet),
            mIndex(index)
        {}

        inline
        operator const_ref() const {
            return *(mVectorSet.mOrder[mIndex]);
        }

        inline
        reference&
        operator= (const value_type& val) {
            mVectorSet.replace(std::advance(mVectorSet.mOrder.begin(), mIndex), val);
            return *this;
        }

    private:
        std::size_t mIndex;
        self_type& mVectorSet;
    };

    friend reference;

    inline
    vector_set() :
        mOrder(),
        mSet()
    {}

    inline
    const reference
    operator[] (std::size_t k) const {
        return reference(*this, k);
    }
    inline
    reference
    operator[] (std::size_t k) {
        return reference(*this, k);
    }

    std::tuple<set_iterator, bool>
    push_back(const value_type& val) {
        set_iterator sIt; bool inserted;
        std::tie(sIt, inserted) = mSet.insert(val);
        if (inserted)
            mOrder.push_back(sIt);
        return std::make_tuple(sIt, inserted);
    }
    std::tuple<set_iterator, bool>
    push_back(value_type&& val) {
        set_iterator sIt; bool inserted;
        std::tie(sIt, inserted) = mSet.insert(val);
        if (inserted)
            mOrder.push_back(sIt);
        return std::make_tuple(sIt, inserted);
    }

    std::tuple<set_iterator, bool>
    insert(vec_iterator vIt, const value_type& val) {
        set_iterator sIt; bool inserted;
        std::tie(sIt, inserted) = mSet.insert(val);
        if (inserted)
            vIt = mOrder.insert(vIt, sIt);
        else {
            auto vItPrev = mOrder.find(sIt);
            auto diff = std::distance(vItPrev, vIt);
            if (diff > 0) {
                ::utility::cyclic_shift_left(vItPrev, std::prev(vIt));
                *std::prev(vIt) = sIt;
            }
            else if (diff < 0) {
                ::utility::cyclic_shift_right(vIt, vItPrev);
                *vIt = sIt;
            }
        }
        return std::make_tuple(sIt, inserted);
    }
    std::tuple<set_iterator, bool>
    insert(vec_iterator vIt, value_type&& val) {
        set_iterator sIt; bool inserted;
        std::tie(sIt, inserted) = mSet.insert(val);
        if (inserted)
            vIt = mOrder.insert(vIt, sIt);
        else {
            auto vItPrev = mOrder.find(sIt);
            auto diff = std::distance(vItPrev, vIt);
            if (diff > 0) {
                ::utility::cyclic_shift_left(vItPrev, std::prev(vIt));
                *std::prev(vIt) = sIt;
            }
            else if (diff < 0) {
                ::utility::cyclic_shift_right(vIt, vItPrev);
                *vIt = sIt;
            }
        }
        return std::make_tuple(sIt, inserted);
    }

    std::tuple<set_iterator, bool>
    replace(vec_iterator vIt, const value_type& val) {
        set_iterator sIt; bool inserted;
        std::tie(sIt, inserted) = mSet.insert(val);
        if (inserted) {
            mSet.erase(*vIt);
            *vIt = sIt;
        }
        else {
            auto vItPrev = mOrder.find(sIt);
            mSet.erase(*vIt);
            *vIt = sIt;
            mOrder.erase(vItPrev);
        }
        return std::make_tuple(sIt, inserted);
    }
    std::tuple<set_iterator, bool>
    replace(vec_iterator vIt, value_type&& val) {
        set_iterator sIt; bool inserted;
        std::tie(sIt, inserted) = mSet.insert(val);
        if (inserted) {
            mSet.erase(*vIt);
            *vIt = sIt;
        }
        else {
            auto vItPrev = mOrder.find(sIt);
            mSet.erase(*vIt);
            *vIt = sIt;
            mOrder.erase(vItPrev);
        }
        return std::make_tuple(sIt, inserted);
    }

    set_iterator
    erase(vec_iterator vIt) {
        set_iterator sIt;
        sIt = mSet.erase(*vIt);
        vIt = mOrder.erase(vIt);
        return sIt;
    }

protected:
    inline
    const_vec_iterator
    to_iterator(std::size_t index) const {
        return std::advance(mOrder.cbegin(), index);
    }
    inline
    vec_iterator
    to_iterator(std::size_t index) {
        return std::advance(mOrder.begin(), index);
    }

    inline
    std::size_t
    to_index(const_vec_iterator it) const {
        return std::distance(mOrder.cbegin(), it);
    }
    inline
    std::size_t
    to_index(vec_iterator it) {
        return std::distance(mOrder.begin(), it);
    }

private:
    set mSet;
    vector mOrder;
};



}   //-- namespace language --


#endif /* LIB_LANGUAGE_VECTOR_SET_HPP_ */
