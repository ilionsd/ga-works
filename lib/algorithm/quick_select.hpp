/*
 * quick_select.hpp
 *
 *  Created on: Aug 2, 2017
 *      Author: ilion
 */

#ifndef LIB_ALGORITHM_QUICK_SELECT_HPP_
#define LIB_ALGORITHM_QUICK_SELECT_HPP_


#include <cstddef>
#include <functional>
#include <random>
#include <utility>


#include "../utility/vector.hpp"


namespace algorithm {

template<typename T>
struct pivot_middle {
    typedef T size_type;

    inline constexpr pivot_middle() noexcept = default;

    inline constexpr size_type operator() (const size_type left, const size_type right) const {
        return left + (right - left) / size_type(2);
    }
};
template<typename T>
struct pivot_random {
    typedef T size_type;

    inline constexpr pivot_random() noexcept :
            engine(std::random_device()())
    {}

    inline constexpr size_type operator() (const size_type left, const size_type right) const {
        return std::uniform_int_distribution<size_type>(left, right)(engine);
    }
    mutable std::mt19937_64 engine;
};

template<typename T>
struct quick_select {
    typedef T value_type;
    typedef std::size_t  size_type;

    template<typename V, typename F = pivot_random<size_type>>
    constexpr size_type operator() (const V& vec, const size_type rank, F gen = F()) const {
        size_type left = 0, right = vec.size() - 1;
        std::vector<size_type> transpositions = utility::vector::make_arange(vec.size() - 1);
        while ( true ) {
            size_type pivot = gen(left, right);
            pivot = partition(vec, transpositions, left, right, pivot);
            if (rank == pivot)
                return transpositions[pivot];
            else if (rank < pivot)
                right = pivot - 1;
            else
                left = pivot + 1;
        }
    }

    template<typename V>
    constexpr size_type partition(
            const V& vec,
            std::vector<size_type>& transpositions,
            const size_type left,
            const size_type right,
            const size_type pivot) const {
        value_type pivotValue = vec[transpositions[pivot]];
        size_type stored = left;
        std::swap(transpositions[pivot], transpositions[right]);
        for (size_type k = left; k < right; ++k)
            if (vec[transpositions[k]] < pivotValue)
                std::swap(transpositions[stored++], transpositions[k]);
        std::swap(transpositions[stored], transpositions[right]);
        return stored;
    }
};

}   //-- namespace algorithm --


#endif /* LIB_ALGORITHM_QUICK_SELECT_HPP_ */
