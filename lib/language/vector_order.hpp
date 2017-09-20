/*
 * vector_order.hpp
 *
 *  Created on: Sep 13, 2017
 *      Author: ilion
 */

#ifndef LIB_LANGUAGE_VECTOR_ORDER_HPP_
#define LIB_LANGUAGE_VECTOR_ORDER_HPP_


#include <algorithm>
#include <iterator>
#include <tuple>
#include <vector>

#include "../utility/cyclic_shift.hpp"


namespace language {

template<typename T>
class vector_order {
public:
    typedef T value_type;
    typedef std::vector<value_type> vector;
    typedef typename vector::iterator iterator;
    typedef typename vector::const_iterator const_iterator;

    inline
    iterator
    push_back(const value_type& val) {
       mOrder.push_back(val);
       return std::advance(mOrder.begin(), mOrder.size() - 1);
    }
    inline
    iterator
    push_back(value_type&& val) {
       mOrder.push_back(val);
       return std::advance(mOrder.begin(), mOrder.size() - 1);
    }

    std::tuple<iterator, bool>
    checked_push_back(const value_type& val) {
        iterator it; bool found;
        std::tie(it, found) = find(val);
        if (!found)
            it = push_back(val);
        return std::make_tuple(it, !found);
    }
    std::tuple<iterator, bool>
    checked_push_back(value_type&& val) {
        iterator it; bool found;
        std::tie(it, found) = find(val);
        if (!found)
            it = push_back(val);
        return std::make_tuple(it, !found);
    }

    std::size_t
    move(iterator srcIt, iterator dstIt) {
        std::size_t size;
        auto diff = std::distance(srcIt, dstIt);
        if (diff > 0)
            size = ::utility::cyclic_shift_right(srcIt, dstIt);
        else if (diff < 0)
            size = ::utility::cyclic_shift_left(srcIt, dstIt);
        return size;
    }

    inline
    iterator
    insert(iterator it, const value_type& val) {
        return mOrder.insert(it, val);
    }
    inline
    iterator
    insert(iterator it, value_type&& val) {
        return mOrder.insert(it, val);
    }

    inline
    iterator
    erase(const_iterator it) {
        return mOrder.erase(it);
    }
    inline
    iterator
    erase(iterator it) {
        return mOrder.erase(it);
    }

    inline
    typename vector::const_reference
    operator[] (std::size_t index) const {
        return mOrder[index];
    }
    inline
    typename vector::reference
    operator[] (std::size_t index) {
        return mOrder[index];
    }

    inline
    typename vector::const_reference
    at(std::size_t index) const {
        return mOrder.at(index);
    }
    inline
    typename vector::reference
    at(std::size_t index) {
        return mOrder.at(index);
    }

    inline
    typename vector::const_iterator
    find(const value_type& val) const {
        return std::find(cbegin(), cend(), val);
    }
    inline
    std::tuple<typename vector::const_iterator, bool>
    find(const value_type& val) const {
        typename vector::const_iterator it; bool found;
        it = find(val);
        found = it != cend();
        return std::make_tuple(it, found);
    }
    inline
    typename vector::iterator
    find(const value_type& val) {
        return std::find(begin(), end(), val);
    }
    inline
    std::tuple<typename vector::iterator, bool>
    find(const value_type& val) {
        typename vector::iterator it; bool found;
        it = find(val);
        found = it != end();
        return std::make_tuple(it, found);
    }

    inline
    typename vector::const_iterator
    cbegin() const {
        return mOrder.cbegin();
    }
    inline
    typename vector::iterator
    begin() {
        return mOrder.begin();
    }

    inline
    typename vector::const_iterator
    cend() const {
        return mOrder.cend();
    }
    inline
    typename vector::iterator
    end() {
        return mOrder.end();
    }

private:
    vector mOrder;
};

}   //-- namespace language --


#endif /* LIB_LANGUAGE_VECTOR_ORDER_HPP_ */
