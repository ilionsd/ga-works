/*
 * vector_unique.hpp
 *
 *  Created on: Sep 14, 2017
 *      Author: ilion
 */

#ifndef LIB_LANGUAGE_VECTOR_UNIQUE_HPP_
#define LIB_LANGUAGE_VECTOR_UNIQUE_HPP_


#include "vector_order.hpp"


namespace language {

template<class Unique>
class vector_unique {
public:
    typedef Unique unique_provider;
    typedef vector_order<typename Unique::iterator> vector;
    typedef typename unique_provider::value_type value_type;

    std::tuple<typename unique_provider::iterator, bool>
    push_back(const value_type& val) {
        typename unique_provider::iterator uIt; bool inserted;
        std::tie(uIt, inserted) = mUnique.insert(val);
        if (inserted)
            mOrder.push_back(uIt);
        return std::make_tuple(uIt, inserted);
    }
    std::tuple<typename unique_provider::iterator, bool>
    push_back(value_type&& val) {
        typename unique_provider::iterator uIt; bool inserted;
        std::tie(uIt, inserted) = mUnique.insert(val);
        if (inserted)
            mOrder.push_back(uIt);
        return std::make_tuple(uIt, inserted);
    }

    std::tuple<typename unique_provider::iterator, bool>
    insert(typename vector::iterator oIt, const value_type& val) {
        typename unique_provider::iterator uIt; bool inserted;
        std::tie(uIt, inserted) = mUnique.insert(val);
        if (inserted)
            oIt = mOrder.insert(oIt, uIt);
        else {
            typename vector::iterator oItPrev = mOrder.find(uIt);
            if (std::distance(oItPrev, oIt) > 0)
                oIt = std::prev(oIt);
            mOrder.move(oItPrev, oIt);
            *oIt = uIt;
        }
        return std::make_tuple(uIt, inserted);
    }
    std::tuple<typename unique_provider::iterator, bool>
    insert(typename vector::iterator oIt, value_type&& val) {
        typename unique_provider::iterator uIt; bool inserted;
        std::tie(uIt, inserted) = mUnique.insert(val);
        if (inserted)
            oIt = mOrder.insert(oIt, uIt);
        else {
            typename vector::iterator oItPrev = mOrder.find(uIt);
            if (std::distance(oItPrev, oIt) > 0)
                oIt = std::prev(oIt);
            mOrder.move(oItPrev, oIt);
            *oIt = uIt;
        }
        return std::make_tuple(uIt, inserted);
    }

    std::tuple<typename unique_provider::iterator, bool>
    replace(typename vector::iterator oIt, const value_type& val) {
        typename unique_provider::iterator uIt; bool inserted;
        std::tie(uIt, inserted) = mUnique.insert(val);
        if (inserted) {
            mUnique.erase(*oIt);
            *oIt = uIt;
        }
        else if (*oIt != uIt) {
            typename vector::iterator oItPrev = mOrder.find(uIt);
            mUnique.erase(*oIt);
            *oIt = uIt;
            mOrder.erase(oItPrev);
        }
        return std::make_tuple(uIt, inserted);
    }
    std::tuple<typename unique_provider::iterator, bool>
    replace(typename vector::iterator oIt, value_type&& val) {
        typename unique_provider::iterator uIt; bool inserted;
        std::tie(uIt, inserted) = mUnique.insert(val);
        if (inserted) {
            mUnique.erase(*oIt);
            *oIt = uIt;
        }
        else if (*oIt != uIt) {
            typename vector::iterator oItPrev = mOrder.find(uIt);
            mUnique.erase(*oIt);
            *oIt = uIt;
            mOrder.erase(oItPrev);
        }
        return std::make_tuple(uIt, inserted);
    }

private:
    unique_provider mUnique;
    vector mOrder;
};

}


#endif /* LIB_LANGUAGE_VECTOR_UNIQUE_HPP_ */
