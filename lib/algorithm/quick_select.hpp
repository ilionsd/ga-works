/*
 * quick_select.hpp
 *
 *  Created on: Aug 2, 2017
 *      Author: ilion
 */

#ifndef LIB_ALGORITHM_QUICK_SELECT_HPP_
#define LIB_ALGORITHM_QUICK_SELECT_HPP_


#include <functional>
#include <random>
#include <utility>


#include "../utility/vector.hpp"


namespace algorithm {

template<typename T>
struct pivot_middle {
    typedef T value_type;

    inline constexpr pivot_middle() noexcept = default;

    inline constexpr value_type operator() (const value_type left, const value_type right) const {
        return left + (right - left) / value_type(2);
    }
};
template<typename T>
struct pivot_random {
    typedef T value_type;

    inline constexpr pivot_random() noexcept :
            gen(std::random_device()())
     {};

    inline constexpr value_type operator() (const value_type left, const value_type right) const {
        return std::uniform_int_distribution<value_type>(left, right)(gen);
    }
    mutable std::mt19937_64 gen;
};

template<typename T>
struct quick_select {
    typedef T container_type;
    typedef typename container_type::size_type  size_type;
    typedef typename container_type::value_type value_type;

    template<typename F = pivot_random<T>>
    constexpr size_type operator() (const container_type& array, const size_type rank, F gen = F()) const {
        size_type left = 0, right = array.size() - 1;
        std::vector<size_type> transpositions = utility::vector::make_arange(array.size() - 1);
        while ( true ) {
            size_type pivot = gen(left, right);
            pivot = partition(array, transpositions, left, right, pivot);
            if (rank == pivot)
                return transpositions[pivot];
            else if (rank < pivot)
                right = pivot - 1;
            else
                left = pivot + 1;
        }
    }

    constexpr size_type partition(
            const container_type& array,
            std::vector<size_type>& transpositions,
            const size_type left,
            const size_type right,
            const size_type pivot) const {
        register value_type pivotValue = array[transpositions[pivot]];
        register size_type stored = left;
        std::swap(transpositions[pivot], transpositions[right]);
        for (size_type k = left + 1; k < right; ++k)
            if (array[transpositions[k]] < pivotValue)
                std::swap(transpositions[stored++], transpositions[k]);
        std::swap(transpositions[stored], transpositions[right]);
        return stored;
    }
};

}   //-- namespace algorithm --


#endif /* LIB_ALGORITHM_QUICK_SELECT_HPP_ */
